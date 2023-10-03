#include "Collision.h"
#include "Math/MyMath.h"

Collision::Collision()
{
	shape_ = 0;
	state_ = 0;
	owner_ = nullptr;
}

Collision::~Collision()
{
	Fin();
}

void Collision::Init()
{
}

void Collision::Step()
{
	if (owner_) {
		pos_ = owner_->GetPos();
	}
}

void Collision::Update()
{
}

void Collision::Draw()
{
}

void Collision::Fin()
{
}
