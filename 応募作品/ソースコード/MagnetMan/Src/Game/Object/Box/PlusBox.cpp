#include "DxLib.h"
#include "PlusBox.h"
#include "BoxParameter.h"
#include "Common.h"
#include "Input/Input.h"
#include "Input/InputManager.h"
#include "Math/MyMath.h"
#include "Collision/CollisionManager.h"
#include "Object/Player/PlayerManager.h"
#include "MinusBox.h"
#include "Sound/SoundManager.h"
using namespace BOX;
CPlusBox::CPlusBox()
{
	SetTag(IObject::PLUS_BOX);
	current_state_ = BOX_STATE::PLUS;
	collision_ = nullptr;
}

CPlusBox::~CPlusBox()
{
	Delete();
}

void CPlusBox::Init()
{
}

void CPlusBox::Load()
{
	handle_ = MV1LoadModel("Data/Model/Box/plus_box.x");
}

void CPlusBox::Delete()
{
	MV1DeleteModel(handle_);
	handle_ = 0;
	if (collision_) {
		//当たり判定の状態を削除する状態に（CollisionManagerで削除）
		collision_->SetState(COLLISION_STATE_NONE);
	}
}

void CPlusBox::Step()
{
	CBox::Step();

	//Y軸の当たり判定
	if (pos_- BOX_HALF_SIZE < 0.0f)
	{
		pos_.y = BOX_HALF_SIZE;
	}
	MV1SetPosition(handle_, pos_);
	CBox::Step();
}


void CPlusBox::OnCollisionEnter(CObject* another)
{
	__super::OnCollisionEnter(another);

	//MinusBulletと当たったら
	if (another->ObjectHasTag(IObject::MINUS_BULLET))
	{
		//ヒットSE再生
		CSoundManager::PlaySE(SOUND_ID_SE_HIT_BOX);
		//MinusBoxにする
		SetNextState(BOX_STATE::MINUS);
	}
	//PlusBulletと当たったら
	else if (another->ObjectHasTag(IObject::PLAUS_BULLET))
	{
		//ヒットSE再生
		CSoundManager::PlaySE(SOUND_ID_SE_HIT_BOX);
		//PlusBoxにする
		SetNextState(BOX_STATE::NORMAL);
	}
}

void CPlusBox::CreateCollision()
{
	//コリジョン設定
	collision_ = static_cast<BoxCollision*>(TheCollisionManager->CreateCollision((int)CollisionShape::COLLISION_SHAPE_BOX,
		(int)CollisionCategory::COLLISION_CATEGORY_BOX));
	collision_->SetOwner(this);
	collision_->SetSize(BOX_W, BOX_H, BOX_D);
	SetSize(Vector3D(BOX_W, BOX_H, BOX_D));
	collision_->SetState(COLLISION_STATE_ACTIVE);
}

void CPlusBox::Draw()
{
	MV1DrawModel(handle_);
}

void CPlusBox::Fin()
{
	if (handle_ != 0)
	{
		Delete();
	}
	CSoundManager::DeleteSound(SOUND_GROUP_PLAY);
}

CBox* CPlusBox::Clone()
{
	CPlusBox* clone = NEW CPlusBox;
	*clone = *this;
	clone->handle_ = MV1DuplicateModel(handle_);
	clone->CreateCollision();
	return clone;
}