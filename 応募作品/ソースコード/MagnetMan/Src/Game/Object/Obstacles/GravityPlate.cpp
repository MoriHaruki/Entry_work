#include "GravityPlate.h"
#include "Collision/CollisionManager.h"
#include "Object/Player/PlayerManager.h"
#include "Math/MyMath.h"
#include "Common.h"


CGravityPlate::CGravityPlate() : CObstacles()
{
	SetTag(IObject::GRAVITY);
	handle_ = 0;
	current_state_ = OBSTACLES_STATE::GRAVITY;
	escape_speed_ = 0.0f;
	collision_ = nullptr;
}

CGravityPlate::~CGravityPlate()
{

}

void CGravityPlate::Init()
{
	current_state_ = OBSTACLES_STATE::GRAVITY;

	//コリジョン設定
	collision_ = static_cast<BoxCollision*>(TheCollisionManager->CreateCollision((int)CollisionShape::COLLISION_SHAPE_BOX,
	(int)CollisionCategory::COLLISION_CATEGORY_OBSTACLES));
	collision_->SetOwner(this);
	collision_->SetSize(GRAVITY_W, GRAVITY_H, GRAVITY_D);
	SetSize(Vector3D(GRAVITY_W, GRAVITY_H, GRAVITY_D));
}

void CGravityPlate::Load()
{
	handle_ = MV1LoadModel("Data/Model/Obstacles/Trampoline.x");
}

void CGravityPlate::Delete()
{
	MV1DeleteModel(handle_);

	handle_ = 0;
}

//ステップ
void CGravityPlate::Step()
{
	//プレイヤーの主にプレイヤーが動作するのでプレイヤーのOnCollisionEnterに記入
}


void CGravityPlate::OnCollisionEnter(CObject* another)
{
	__super::OnCollisionEnter(another);	
}

void CGravityPlate::Draw()
{
	MV1DrawModel(handle_);
}



void CGravityPlate::Fin()
{
	if (handle_ != 0)
	{
		Delete();
	}
}


CObstacles* CGravityPlate::Clone()
{
	CGravityPlate* clone = NEW CGravityPlate;
	*clone = *this;
	clone->Init();
	clone->handle_ = MV1DuplicateModel(handle_);

	return clone;
}