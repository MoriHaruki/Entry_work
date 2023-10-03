#include "MinusBullet.h"
#include "BulletParameter.h"
#include "Math/MyMath.h"
#include "Collision/CollisionManager.h"
#include "Object/ObjectParameter.h"
#include "Object/Box/Box.h"
#include "Object/Player/PlayerManager.h"
#include "Common.h"

CMinusBullet::CMinusBullet(int id)
{
	id_ = id;
	SetTag(IObject::MINUS_BULLET);
	collision_ = nullptr;
}

CMinusBullet::~CMinusBullet()
{
}

void CMinusBullet::Init()
{
	CBullet::Init();
}

void CMinusBullet::Step()
{
	CBullet::Step();
	pos_ += move_;
}

void CMinusBullet::Update()
{
	MV1SetRotationXYZ(handle_, rot_);
	MV1SetPosition(handle_, pos_);
}

void CMinusBullet::Delete()
{
	__super::Delete();

	if (collision_) {
		collision_->DeleteRequest();
	}
}


CBullet* CMinusBullet::Clone()
{
	CMinusBullet* clone = NEW CMinusBullet(BULLET_ID_PLAYER_MINUS);
	*clone = *this;
	clone->SetHandle(MV1DuplicateModel(handle_));
	clone->CreateCollision();
	return clone;
}

void CMinusBullet::OnCollisionEnter(CObject* another)
{
	active_ = false; //’e‚ÌÁ‹Ž
	collision_->DeleteRequest();	
}
