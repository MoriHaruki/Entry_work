#include "Lift.h"
#include "Collision/CollisionManager.h"
#include "Object/Player/PlayerManager.h"
#include "Input/InputManager.h"
#include "Math/MyMath.h"

CLift::CLift() : CObstacles()
{
	SetTag(IObject::LIFT);
	handle_ = 0;
	current_state_ = OBSTACLES_STATE::LIFT;
	escape_speed_ = 0.0f;
	collision_ = nullptr;
	pre_offset_ = 0.f;
	current_offset_ = 0.f;
}

CLift::~CLift()
{
}

void CLift::Init()
{
	current_state_ = OBSTACLES_STATE::LIFT;
	//�R���W�����ݒ�
	collision_ = static_cast<BoxCollision*>(TheCollisionManager->CreateCollision((int)CollisionShape::COLLISION_SHAPE_BOX,
		(int)CollisionCategory::COLLISION_CATEGORY_OBSTACLES));
	collision_->SetOwner(this);
	collision_->SetSize(LIFT_W, LIFT_H, LIFT_D);
	SetSize(Vector3D(LIFT_W, LIFT_H, LIFT_D));
}

void CLift::Load()
{
	handle_ = MV1LoadModel("Data/Model/Obstacles/Lift.x");
}

void CLift::Delete()
{
	MV1DeleteModel(handle_);
	handle_ = 0;
}

void CLift::Step()
{
	CPlayerManager* player_manager = ThePlayerManager;
	CPlayer* player = player_manager->GetPlayer();
	
	// �O�t���̃I�t�Z�b�g�l��ۑ�
	pre_offset_ = current_offset_;
	current_offset_ = (LIFT_AMPLITUDE / 2) * sin(radian_);
	pos_.y = pos_.y + current_offset_;
	radian_ += 0.025f;
	if (DX_PI * 2.f < radian_) radian_ = 0.f;
}

void CLift::Draw()
{
	MV1DrawModel(handle_);
}

void CLift::Fin()
{
	if (handle_ != 0)
	{
		Delete();
	}
}

CObstacles* CLift::Clone()
{
	CLift* clone = NEW CLift;
	*clone = *this;
	clone->Init();
	clone->handle_ = MV1DuplicateModel(handle_);
	return clone;
}

void CLift::OnCollisionEnter(CObject* another)
{
	// �v���C���[������������
	if (another->ObjectHasTag(IObject::PLAYER)) {
		// �v���C���[���擾
		CPlayer* player = ThePlayerManager->GetPlayer();

		// �����߂��������s
		player->SetPos(Extrude(player->GetPos(), player->GetSize(), pos_, size_));
	}
}
