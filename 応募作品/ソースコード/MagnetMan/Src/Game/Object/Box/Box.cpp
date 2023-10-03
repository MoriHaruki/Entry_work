#include "DxLib.h"
#include "Box.h"
#include "BoxParameter.h"
#include "Input/Input.h"
#include "Math/MyMath.h"
#include "Collision/CollisionManager.h"
#include "Object/Player/PlayerManager.h"
#include "Object/Bullet/Bullet.h"
#include "Object/Bullet/BulletManager.h"

using namespace BOX;

CBox::CBox() : CObject()
{
	handle_ = 0;
	current_state_ = BOX_STATE::NONE;
	next_state_= BOX_STATE::NONE;
	move_state_ = MOVE_STATE::NONE;
	escape_speed_ = 0.0f;
	radian_ = 0.0f;
	collision_ = nullptr;
	move_ = { 0.f };
}

CBox::~CBox()
{
}

void CBox::Delete()
{
	if (collision_)
	{
		collision_->SetState(COLLISION_STATE_NONE);
	}

	MV1DeleteModel(handle_);
	handle_ = 0;
}

void CBox::Step()
{
	//Y軸の当たり判定
	if (pos_.y - BOX_HALF_SIZE < 0.0f)
	{
		pos_.y = BOX_HALF_SIZE;
	}

	pos_ = VecAdd(pos_, move_);
	move_ = { 0.f };
}

void CBox::Draw()
{
	MV1DrawModel(handle_);
}

void CBox::Fin()
{
	if (handle_ != 0)
	{
		Delete();
	}
}

void CBox::OnCollisionEnter(CObject* another)
{
	//プレイヤーと当たっていたら
	if (another->ObjectHasTag(IObject::PLAYER))
	{
		//プレイヤー情報取得
		CPlayer* player = ThePlayerManager->GetPlayer();
		// 押し戻し処理実行
		player->SetPos(Extrude(player->GetPos(), player->GetSize(), pos_, size_));
		player->SetState(PLAYER_STATE::PLAYER_STATE_NORMAL);
	}
}



