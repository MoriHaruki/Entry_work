#include "BoxManager.h"
#include "Common.h"
#include "Normalbox.h"
#include "MinusBox.h"
#include "PlusBox.h"
#include "Math/MyMath.h"
#include "Box.h"
#include "Sound/SoundManager.h"

using namespace BOX;


namespace {
	//�^�C�g��S�V�[���̗��Ń��[�h�������A�v���C�V�[���ֈړ�����Ƃ��Ɏ��ԒZ�k������
	class Prototypeinstance 
	{
	public:
		//�R���X�g���N�^
		Prototypeinstance() 
		{
			proto = nullptr;
		}
		//�f�X�g���N�^
		~Prototypeinstance() {
			if (proto)
			{
				for (auto box : *proto)
				{
					box->Delete();
				}

				for (auto itr = proto->begin(); itr != proto->end();)
				{
					CBox* box = (*itr);
					delete box;
					box = nullptr;
					itr = proto->erase(itr);
				}
			}
		}

		void SetProtoTypes(std::vector<CBox*>* ptr)
		{
			proto = ptr;
		}

		std::vector<CBox*>* proto;
	};

	Prototypeinstance prototypeinstance;
}

CBoxManager::CBoxManager()
{
}

CBoxManager::~CBoxManager()
{
	Fin();
}

void CBoxManager::CreatePrototypes()
{
	//���񃍁[�h�����̂ŃL�����Z������
	if (prototype_box_.size() != 0)
		return;

	prototypeinstance.SetProtoTypes(&prototype_box_);

	for (int box_index = 0; box_index < static_cast<int>(BOX_STATE::NUM); ++box_index)
	{
		prototype_box_.emplace_back(CreatePrototype(box_index));
	}
	for (auto box : prototype_box_)
	{
		box->Load();
	}
}

//������
void CBoxManager::Init()
{
	SetBox();
}

void CBoxManager::SetBox()
{
	//�p�����[�^�[���擾
	const BoxParameter* param = BOX_DATABASE[TheFieldManager->GetID()];

	for (int index = 0; index < CREATE_BOX_NUM; index++)
	{
		if (param[index].id == static_cast<int>(BOX_STATE::NONE))
		{
			break;
		}
		auto* Box = CreateBOX(param[index].id);
		Box->SetPos(param[index].startpos);
	}
}

CBox* CBoxManager::CreateBOX(int id)
{
	CBox* box = nullptr;
	box = prototype_box_[id]->Clone();
	boxs_.emplace_back(box);
	return box;
}


void CBoxManager::Load()
{
}

//�X�e�b�v
void CBoxManager::Step()
{
	CBoxManager::StepChenckChengeBox();

	for (auto box : boxs_)
	{
		box->Step();
	}

	StepCheckAttractBoxs();
	BoxCollision();
}

void CBoxManager::StepAttract()
{
}

//�`��
void CBoxManager::Draw()
{
	for (auto box : boxs_)
	{
		box->Draw();
	}

#ifdef _DEBUG
	DrawFormatString(10, 500, 0xff00ff, "box_size�F%d", boxs_.size());
#endif
}

//����
void CBoxManager::Delete()
{
	for (auto box : boxs_)
	{
		box->Delete();
	}
}

//�㏈��
void CBoxManager::Fin()
{
	CBoxManager::Delete();

	for (auto itr = boxs_.begin(); itr != boxs_.end();)
	{
		CBox* box = (*itr);
		delete box;
		box = nullptr;
		itr = boxs_.erase(itr);
	}

	CSoundManager::DeleteSound(SOUND_GROUP_PLAY);
}

//��ɔ��̎�ނ�ύX�����邩�m�F����
void CBoxManager::StepChenckChengeBox()
{
	for (auto itr = boxs_.begin(); itr != boxs_.end();)
	{
		CBox* box = (*itr);
		//���̎�ނɕύX������ΐ؂�ւ���
		if(box->GetNextState() != BOX_STATE::NONE)
		{
			//���W�Ǝ��̔��̎�ނ��擾���Đ؂�ւ����̔���j������
			VECTOR pos = box->GetPos();
			BOX_STATE state = box->GetNextState();
			box->Delete();
			delete box;
			box = nullptr;
			itr = boxs_.erase(itr);
			//�V������������
			CBox* create_box = prototype_box_[static_cast<int> (state)]->Clone();
			create_box->SetPos(pos);
			boxs_.push_back(create_box);
			break;
		}
		else
		{
			itr++;
		}
	}
}

void CBoxManager::StepCheckAttractBoxs()
{
	
	//���̈����񂹏���
	for (auto minus_box : boxs_)
	{
		if (minus_box->GetCurrenState() != BOX_STATE::MINUS) continue;
		for (auto plus_box : boxs_)
		{
			if (plus_box->GetCurrenState() != BOX_STATE::PLUS) continue;
			float dist = VecLong(minus_box->GetPos(), plus_box->GetPos());//�����m�̋�����}��
			if (dist <= ACTIVE_DIST && dist > STOP_MOVE && plus_box->GetMoveState() != MOVE_STATE::STOP)//�ݒ肵���͈͓��ɔ�������Έ����񂹊J�n
			{
				CSoundManager::PlaySE(SOUND_ID_SE_START_ATTRACT);//�T�E���h�Đ�
				VECTOR calc = VecCreate(plus_box->GetPos(),minus_box->GetPos());
				calc = calc * (CCommon::FRAME_MIN / BOX_MOVE_MIN);	//�ݒ肵�����ԂŐݒ肵���ꏊ�Ɉړ�����
				plus_box->SetMove(calc);
			}
		}
	}
}

//�{�b�N�X�����蔻��
void CBoxManager::BoxCollision()
{
	//�}�C�i�X�A�v���X
	for (auto minus_box : boxs_)
	{
		if (minus_box->GetCurrenState() != BOX_STATE::MINUS) continue;
		for (auto plus_box : boxs_)
		{
			if (plus_box->GetCurrenState() != BOX_STATE::PLUS) continue;
			if (IsHitRect(minus_box->GetPos(), BOX_W, BOX_H, BOX_D, plus_box->GetPos(), BOX_W, BOX_H, BOX_D))
			{
				plus_box->SetPos(Extrude(minus_box->GetPos(), VGet(BOX_W, BOX_H, BOX_D),
					plus_box->GetPos(), VGet(BOX_W, BOX_H, BOX_D)));
				VECTOR move = { 0.0f };
				plus_box->SetMove(move);
				plus_box->SetMoveState(MOVE_STATE::STOP);
			}
		}
	}
}

//�N���G�C�g
CBox* CBoxManager::CreatePrototype(int id)
{
	switch (id)
	{
	case static_cast<int>(BOX_STATE::NORMAL):

		return NEW CNormalBox;

	case static_cast<int>(BOX_STATE::MINUS):

		return NEW CMinusBox;

	case static_cast<int>(BOX_STATE::PLUS) :

		return NEW CPlusBox;
	}
	
	return nullptr;
}
