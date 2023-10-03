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
	// 当たり判定の可視化
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
	// 現状、ボックス同士の当たり判定しかとらない
	if (another->GetShape() != COLLISION_SHAPE_BOX) {
		return false;
	}

	BoxCollision* another_box = static_cast<BoxCollision*>(another);
	const Vector3D another_size(another_box->GetSize());

	// 自身の座標の最小値と最大値
	const AABB myself_aabb(pos_, size_ * 0.5f);
	const AABB another_aabb(another_box->pos_, another_size * 0.5f);

	// 当たっていたら
	if (IsHitRect(myself_aabb, another_aabb)) {
		return true;
	}

	return false;
}
