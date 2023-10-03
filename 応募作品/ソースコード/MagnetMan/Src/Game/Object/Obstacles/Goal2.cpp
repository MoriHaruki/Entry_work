#include "Goal2.h"
#include "Collision/CollisionManager.h"
#include "Object/Player/PlayerManager.h"
#include "Math/MyMath.h"

CGoal2::CGoal2() : CObstacles()
{
	SetTag(IObject::GOAL2);
	handle_ = 0;
	goal_flag_2 = false;
	current_state_ = OBSTACLES_STATE::GOAL2;
	collision_ = nullptr;
}

CGoal2::~CGoal2()
{
}

void CGoal2::Init()
{
	current_state_ = OBSTACLES_STATE::GOAL2;
	//コリジョン設定
	collision_ = static_cast<BoxCollision*>(TheCollisionManager->CreateCollision((int)CollisionShape::COLLISION_SHAPE_BOX,
		(int)CollisionCategory::COLLISION_CATEGORY_OBSTACLES));
	collision_->SetOwner(this);
	collision_->SetSize(GOAL_W, GOAL_H, GOAL_D);
}

void CGoal2::Load()
{
	handle_ = MV1LoadModel("Data/Model/Goal/Goal.x");
}

void CGoal2::Delete()
{
	MV1DeleteModel(handle_);
	handle_ = 0;
}

void CGoal2::Step()
{
	CPlayerManager* player_manager = ThePlayerManager;
	CPlayer* player = player_manager->GetPlayer();

	//ゴールとプレイヤー当たり判定
	if (IsHitRect(player->GetPos(), PLAY_W, PLAY_H, PLAY_D, pos_, GOAL_W, GOAL_H, GOAL_D))
	{
		//goalフラグ
		goal_flag_2 = true;
	}
	else
	{
		goal_flag_2 = false;
	}
}

void CGoal2::Draw()
{
	MV1DrawModel(handle_);
}

void CGoal2::Fin()
{
	if (handle_ != 0)
	{
		Delete();
	}
}

CObstacles* CGoal2::Clone()
{
	CGoal2* clone = NEW CGoal2;
	*clone = *this;
	clone->Init();
	clone->handle_ = MV1DuplicateModel(handle_);
	return clone;
}

void CGoal2::OnCollisionEnter(CObject* another)
{
}