#include "Goal.h"
#include "Collision/CollisionManager.h"
#include "Object/Player/PlayerManager.h"
#include "Math/MyMath.h"

CGoal::CGoal() : CObstacles()
{
	SetTag(IObject::GOAL);
	handle_ = 0;
	goal_flag_ = false;
	current_state_ = OBSTACLES_STATE::GOAL;
	collision_ = nullptr;
}

CGoal::~CGoal()
{
}

void CGoal::Init()
{
	current_state_ = OBSTACLES_STATE::GOAL;
	//コリジョン設定
	collision_ = static_cast<BoxCollision*>(TheCollisionManager->CreateCollision((int)CollisionShape::COLLISION_SHAPE_BOX,
		(int)CollisionCategory::COLLISION_CATEGORY_OBSTACLES));
	collision_->SetOwner(this);
	collision_->SetSize(GOAL_W, GOAL_H, GOAL_D);
}

void CGoal::Load()
{
	handle_ = MV1LoadModel("Data/Model/Goal/Goal.x");
}

void CGoal::Delete()
{
	MV1DeleteModel(handle_);
	handle_ = 0;
}

void CGoal::Step()
{
	CPlayerManager* player_manager = ThePlayerManager;
	CPlayer* player = player_manager->GetPlayer();

	//ゴールとプレイヤー当たり判定
	if (IsHitRect(player->GetPos(), PLAY_W, PLAY_H, PLAY_D, pos_, GOAL_W, GOAL_H, GOAL_D))
	{
		//goalフラグ
		goal_flag_ = true;
	}
	else
	{
		goal_flag_ = false;
	}
}

void CGoal::Draw()
{
	MV1DrawModel(handle_);
}

void CGoal::Fin()
{
	if (handle_ != 0)
	{
		Delete();
	}
}

CObstacles* CGoal::Clone()
{
	CGoal* clone = NEW CGoal;
	*clone = *this;
	clone->Init();
	clone->handle_ = MV1DuplicateModel(handle_);
	return clone;
}

void CGoal::OnCollisionEnter(CObject* another)
{
}
