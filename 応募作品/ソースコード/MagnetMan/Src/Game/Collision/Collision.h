#pragma once

#include "CollisionParameter.h"
#include "Object/Object.h"

class Collision {
public:
	Collision();
	~Collision();

public:
	virtual void Init();
	virtual void Step();
	virtual void Update();
	virtual void Draw();
	virtual void Fin();
	virtual Collision* Clone() = 0;
	virtual bool CheckCollision(Collision* another) = 0;

public:

	void SetOwner(CObject* owner) { owner_ = owner; }
	void SetState(int state) { state_ = state; }
	void SetPos(Vector3D pos) { pos_(pos); }
	CObject* GetOwner() const { return owner_; }
	int GetState() const { return state_; }
	int GetShape() const { return shape_; }
	Vector3D GetPos() const { return pos_; }
	void DeleteRequest() { state_ = COLLISION_STATE_NONE; }
	bool IsNone() const { return state_ == COLLISION_STATE_NONE; }
	bool IsCheck() const { return state_ == COLLISION_STATE_ACTIVE; }

protected:
	int shape_;
	int state_;
	CObject* owner_;
	Vector3D pos_;
};
