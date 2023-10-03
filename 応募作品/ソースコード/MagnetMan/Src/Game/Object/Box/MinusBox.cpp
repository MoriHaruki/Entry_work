#include "DxLib.h"
#include "BoxParameter.h"
#include "Common.h"
#include "Math/MyMath.h"
#include "Collision/CollisionManager.h"
#include "Object/Player/PlayerManager.h"
#include "BoxManager.h"
#include "Sound/SoundManager.h"

using namespace BOX;
CMinusBox::CMinusBox() :CBox()
{
	SetTag(IObject::MINUS_BOX);
	current_state_ = BOX_STATE::MINUS;
	collision_ = nullptr;
}

CMinusBox::~CMinusBox()
{
	Delete();
}

void CMinusBox::Init()
{
}

void CMinusBox::Load()
{
	handle_ = MV1LoadModel("Data/Model/Box/minus_box.x");
}

void CMinusBox::Delete()
{
	MV1DeleteModel(handle_);
	handle_ = 0;
	if (collision_) 
	{
		collision_->SetState(COLLISION_STATE_NONE);	//当たり判定の状態を削除する状態に（CollisionManagerで削除）
	}
}

void CMinusBox::Step()
{
	CBox::Step();

	MV1SetPosition(handle_, pos_);
}

void CMinusBox::OnCollisionEnter(CObject* another)
{
	__super::OnCollisionEnter(another);

	//MinusBulletと当たったら
	if (another->ObjectHasTag(IObject::MINUS_BULLET))
	{
		//MinusBoxにする
		SetNextState(BOX_STATE::NORMAL);
		CSoundManager::PlaySE(SOUND_ID_SE_HIT_BOX);
	}
	//PlusBulletと当たったら
	else if (another->ObjectHasTag(IObject::PLAUS_BULLET))
	{
		//PlusBoxにする
		SetNextState(BOX_STATE::PLUS);
		CSoundManager::PlaySE(SOUND_ID_SE_HIT_BOX);
	}
	
}

void CMinusBox::Draw()
{
	MV1DrawModel(handle_);
}

void CMinusBox::Fin()
{
	if (handle_ != 0)
	{
		Delete();
	}

	CSoundManager::DeleteSound(SOUND_GROUP_PLAY);
}

void CMinusBox::CreateCollision()
{
	//コリジョン設定
	collision_ = static_cast<BoxCollision*>(TheCollisionManager->CreateCollision((int)CollisionShape::COLLISION_SHAPE_BOX,
		(int)CollisionCategory::COLLISION_CATEGORY_BOX));
	collision_->SetOwner(this);
	collision_->SetSize(BOX_W, BOX_H, BOX_D);
	SetSize(Vector3D(BOX_W, BOX_H, BOX_D));
	collision_->SetState(COLLISION_STATE_ACTIVE);
}

CBox* CMinusBox::Clone()
{
	CMinusBox* clone = NEW CMinusBox;
	*clone = *this;
	clone->handle_ = MV1DuplicateModel(handle_);
	clone->CreateCollision();
	return clone;
}