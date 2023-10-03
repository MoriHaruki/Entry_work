#include "Bullet.h"
#include "BulletParameter.h"
#include "Object/Player/PlayerManager.h"
#include "Common.h"
#include "Math/MyMath.h"
#include "Collision/CollisionManager.h"
#include "Collision/BoxCollision.h"
#include "BulletParameter.h"

using namespace BULLET;

CBullet::CBullet() :move_()
{
	handle_ = -1;
	move_ = Vector3D::ZEROVec();
	speed_ = 0.0f;
	life_ = 0.0f;
}

CBullet::~CBullet()
{
	Fin();
}

void CBullet::Init()
{
	BulletParameter param = BULLET_DATABASE[id_];
}

void CBullet::Load()
{
	handle_ = MV1LoadModel(BULLET_DATABASE[id_].FILE_PATH);
}

void CBullet::Fire(Vector3D pos, Vector3D rot, float speed, float life)
{
	active_ = true;
	pos_ = pos;
	rot_ = rot;
	speed_ = speed;
	life_ = life;
	
	move_ = Vector3D::ForwardVec();		// 正面ベクトル作成
	move_ = VecRotation(move_, rot_);	// 正面ベクトルを回転値に合わせて回転
	move_ *= -speed_;					// スピードに合わせてスケーリング
	MV1SetPosition(handle_, pos_);
}

void CBullet::Step()
{
	// 寿命処理
	if (life_ < 0.0f)
	{
		active_ = false;
	}
	else
	{
		life_ -= CCommon::GetGameDeltaTime();
	}
}

void CBullet::Update()
{
	MV1SetRotationXYZ(handle_, rot_);
	MV1SetPosition(handle_, pos_);
}

void CBullet::Draw()
{
	MV1DrawModel(handle_);
}

void CBullet::Delete()
{
	MV1DeleteModel(handle_);
}

void CBullet::Fin()
{
	Delete();
}

void CBullet::OnCollisionEnter(CObject* another)
{
}

void CBullet::CreateCollision()
{
	collision_ = static_cast<BoxCollision*>(TheCollisionManager->CreateCollision(COLLISION_SHAPE_BOX, COLLISION_CATEGORY_BULLET));
	collision_->SetOwner(this);
	collision_->SetSize(BULLET_W, BULLET_W, BULLET_W);
}

