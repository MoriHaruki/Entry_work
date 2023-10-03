#include "DxLib.h"
#include <math.h>
#include "Normalbox.h"
#include "BoxParameter.h"
#include "Input/Input.h"
#include "Math/MyMath.h"
#include <math.h>
#include "Collision/CollisionManager.h"
#include "../Player/PlayerManager.h"
#include "Input/InputManager.h"
#include "Field/Field.h"
#include "../Box/PlusBox.h"
#include "../Box/BoxManager.h"
#include "Sound/SoundManager.h"
using namespace BOX;

CNormalBox::CNormalBox() : CBox()
{
	SetTag(IObject::NORMAL_BOX);
	handle_ = 0;
	current_state_ = BOX_STATE::NORMAL;
	escape_speed_ = 0.0f;
	collision_ = nullptr;
}

CNormalBox::~CNormalBox()
{
	Delete();
}

void CNormalBox::Init()
{
	current_state_ = BOX_STATE::NORMAL;
}

void CNormalBox::Load()
{
	handle_ = MV1LoadModel("Data/Model/Box/normal_box.x");
}

void CNormalBox::Delete()
{
	MV1DeleteModel(handle_);
	handle_ = 0;
	if (collision_) 
	{
		//当たり判定の状態を削除する状態に（CollisionManagerで削除）
		collision_->SetState(COLLISION_STATE_NONE);
	}
}

void CNormalBox::Step()
{
	CBox::Step();

	CPlayerManager* player_manager = ThePlayerManager;
	CPlayer* player = player_manager->GetPlayer();

	//Y軸の当たり判定
	if (pos_.y - BOX_HALF_SIZE < 0.0f)
	{
		pos_.y = BOX_HALF_SIZE;
		current_state_ = BOX_STATE::NORMAL;
	}

	// プレイヤーまでの距離
	const CPlayer* move_player = ThePlayerManager->GetPlayer();
	float player_dist = VecLong(pos_, move_player->GetPos());
	if (player_dist <= BOX::ACTIVE_DIST)
	{
		collision_->SetState(COLLISION_STATE_ACTIVE);
	}

	MV1SetPosition(handle_, pos_);
}


void CNormalBox::OnCollisionEnter(CObject* another)
{
	__super::OnCollisionEnter(another);

	//MinusBulletと当たったら
	if (another->ObjectHasTag(IObject::MINUS_BULLET))
	{
		CSoundManager::PlaySE(SOUND_ID_SE_HIT_BOX);
		SetNextState(BOX_STATE::MINUS);		//MinusBoxにする
	}
	//PlusBulletと当たったら
	else if (another->ObjectHasTag(IObject::PLAUS_BULLET))
	{
		CSoundManager::PlaySE(SOUND_ID_SE_HIT_BOX);
		SetNextState(BOX_STATE::PLUS);		//PlusBoxにする
	}

}

void CNormalBox::Draw()
{
	MV1DrawModel(handle_);
}

void CNormalBox::Fin()
{
	CSoundManager::DeleteSound(SOUND_GROUP_PLAY);
	Delete();
}

void CNormalBox::CreateCollision()
{
	//コリジョン設定
	collision_ = static_cast<BoxCollision*>(TheCollisionManager->CreateCollision((int)CollisionShape::COLLISION_SHAPE_BOX,
		(int)CollisionCategory::COLLISION_CATEGORY_BOX));
	collision_->SetOwner(this);
	collision_->SetSize(BOX_W, BOX_H, BOX_D);
	SetSize(Vector3D(BOX_W, BOX_H, BOX_D));
	collision_->SetState(COLLISION_STATE_ACTIVE);
}

CBox* CNormalBox::Clone()
{
	CNormalBox* clone = NEW CNormalBox;
	*clone = *this;
	clone->handle_ = MV1DuplicateModel(handle_);
	clone->CreateCollision();
	return clone;
}