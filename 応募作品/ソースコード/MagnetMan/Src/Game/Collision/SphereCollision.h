#pragma once

#include "Collision.h"

class SphereCollision : public Collision {
public:
	SphereCollision();
	virtual ~SphereCollision();

public:
	void Init();
	void Update();
	virtual void Draw() override;
	void Fin();
	virtual Collision* Clone() override;
	virtual bool CheckCollision(Collision* another) override;
public:
	void SetRadius(float radius) { radius_ = radius; }
	float GetRadius() const { return radius_; }
private:
	float radius_;
};
