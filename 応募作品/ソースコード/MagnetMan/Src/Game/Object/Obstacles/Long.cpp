#include "Long.h"
#include "Collision/CollisionManager.h"
#include "Object/Player/PlayerManager.h"
#include "Math/MyMath.h"

CLong::CLong() : CObstacles()
{
	SetTag(IObject::LONG);
	handle_ = 0;
	current_state_ = OBSTACLES_STATE::LONG;
	escape_speed_ = 0.0f;
	pre_offset_ = 0.0f;
	current_offset_ = 0.0f;
	collision_ = nullptr;
}

CLong::~CLong()
{
}

void CLong::Init()
{
}

void CLong::Load()
{
	CObstacles::Load("Data/Model/Obstacles/metal_box.x");
}

void CLong::Delete()
{
	MV1DeleteModel(handle_);
	handle_ = 0;
}

void CLong::Step()
{
}

void CLong::Draw()
{
	MV1DrawModel(handle_);
}

void CLong::Fin()
{
	if (handle_ != 0)
	{
		Delete();
	}
}

void CLong::OnCollisionEnter(CObject* another)
{
	// プレイヤーが当たったら
	if (another->ObjectHasTag(IObject::PLAYER)) 
	{
		// プレイヤー情報取得
		CPlayer* player = ThePlayerManager->GetPlayer();
		// 押し戻し処理実行
		player->SetPos(Extrude(player->GetPos(), player->GetSize(), pos_, size_));
	}
}

void CLong::CreateCollision()
{
	collision_ = static_cast<BoxCollision*>(TheCollisionManager->CreateCollision((int)CollisionShape::COLLISION_SHAPE_BOX,
		(int)CollisionCategory::COLLISION_CATEGORY_OBSTACLES));
	collision_->SetOwner(this);
	collision_->SetSize(LONG_W, LONG_H, LONG_D);
	SetSize(Vector3D(LONG_W, LONG_H, LONG_D));
	collision_->SetState(COLLISION_STATE_ACTIVE);
}


CObstacles* CLong::Clone()
{
	CLong* clone = NEW CLong(*this);
	clone->Init();
	clone->handle_ = MV1DuplicateModel(handle_);
	clone->CreateCollision();
	return clone;
}