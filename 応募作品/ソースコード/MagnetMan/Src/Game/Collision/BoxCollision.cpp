#include "BoxCollision.h"
#include "CollisionParameter.h"
#include "Math/MyMath.h"

BoxCollision::BoxCollision() : Collision(), size_()
{
	shape_ = COLLISION_SHAPE_BOX;
}

BoxCollision::~BoxCollision()
{
	Fin();
}

void BoxCollision::Init()
{
}

void BoxCollision::Update()
{
	if (owner_) {
		pos_ = owner_->GetPos();
	}
}

void BoxCollision::Draw()
{
#ifdef	_DEBUG
	// �����蔻��̉���
	const Vector3D min = pos_ - (size_ * 0.5f);
	const Vector3D max = pos_ + (size_ * 0.5f);

	DrawCube3D(min, max, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);
#endif
}

void BoxCollision::Fin()
{
}

Collision* BoxCollision::Clone()
{
	Collision* clone = new BoxCollision;
	*clone = *this;
	return clone;
}

bool BoxCollision::CheckCollision(Collision* another)
{
	// ����A�{�b�N�X���m�̓����蔻�肵���Ƃ�Ȃ�
	if (another->GetShape() != COLLISION_SHAPE_BOX) {
		return false;
	}

	BoxCollision* another_box = static_cast<BoxCollision*>(another);
	const Vector3D another_size(another_box->GetSize());

	// ���g�̍��W�̍ŏ��l�ƍő�l
	const AABB myself_aabb(pos_, size_ * 0.5f);
	const AABB another_aabb(another_box->pos_, another_size * 0.5f);

	// �������Ă�����
	if (IsHitRect(myself_aabb, another_aabb)) {
		return true;
	}

	return false;
}
