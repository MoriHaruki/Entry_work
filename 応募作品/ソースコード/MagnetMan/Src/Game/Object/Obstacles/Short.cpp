#include "Short.h"
#include "Collision/CollisionManager.h"
#include "Object/Player/PlayerManager.h"
#include "Math/MyMath.h"

CShort::CShort() : CObstacles()
{
	SetTag(IObject::SHORT);
	handle_ = 0;
	current_state_ = OBSTACLES_STATE::SHORT;
	escape_speed_ = 0.0f;
	pre_offset_ = 0.0f;
	current_offset_ = 0.0f;
	collision_ = nullptr;
}

CShort::~CShort()
{
}

void CShort::Init()
{
	
}

void CShort::Load()
{
	CObstacles::Load("Data/Model/Obstacles/metal_box.x");
}

void CShort::Delete()
{
	MV1DeleteModel(handle_);
	handle_ = 0;
}

void CShort::Step()
{
}

void CShort::Draw()
{
	MV1DrawModel(handle_);
}

void CShort::Fin()
{
	if (handle_ != 0)
	{
		Delete();
	}
}


void CShort::OnCollisionEnter(CObject* another)
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

void CShort::CreateCollision()
{
	collision_ = static_cast<BoxCollision*>(TheCollisionManager->CreateCollision((int)CollisionShape::COLLISION_SHAPE_BOX,
		(int)CollisionCategory::COLLISION_CATEGORY_OBSTACLES));
	collision_->SetOwner(this);
	collision_->SetSize(SHORT_W, SHORT_H, SHORT_D);
	SetSize(Vector3D(SHORT_W, SHORT_H, SHORT_D));
	collision_->SetState(COLLISION_STATE_ACTIVE);
}



CObstacles* CShort::Clone()
{
	CShort* clone = NEW CShort(*this);
	clone->Init();
	clone->handle_ = MV1DuplicateModel(handle_);
	clone->CreateCollision();
	return clone;
}
