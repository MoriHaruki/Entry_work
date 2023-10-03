#include "MinusBullet.h"
#include "BulletParameter.h"
#include "Math/MyMath.h"
#include "Collision/CollisionManager.h"
#include "Object/ObjectParameter.h"
#include "Object/Box/Box.h"
#include "Object/Player/PlayerManager.h"
#include "PlusBullet.h"
#include "Common.h"

CPlusBullet::CPlusBullet(int id)
{
	id_ = id;
	collision_ = nullptr;
	SetTag(IObject::PLAUS_BULLET);
}

CPlusBullet::~CPlusBullet()
{
}

void CPlusBullet::Init()
{
	CBullet::Init();
}

void CPlusBullet::Step()
{
	CBullet::Step();
	pos_ += move_;
}

void CPlusBullet::Update()
{
	MV1SetRotationXYZ(handle_, rot_);
	MV1SetPosition(handle_, pos_);
}

void CPlusBullet::Delete()
{
	__super::Delete();

	if (collision_)
	{
		collision_->DeleteRequest();
	}
}

CBullet* CPlusBullet::Clone()
{
	CPlusBullet* clone = NEW CPlusBullet(BULLET_ID_PLAYER_PLUS);
	*clone = *this;
	clone->SetHandle(MV1DuplicateModel(handle_));
	clone->CreateCollision();
	return clone;
}

void CPlusBullet::OnCollisionEnter(CObject* another)
{
	active_ = false; //’e‚ÌÁ‹Ž
	collision_->DeleteRequest();
}
