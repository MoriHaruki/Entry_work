#pragma once
#include "Object/Object.h"
#include "ObstaclesParameter.h"
#include "Collision/BoxCollision.h"

class CObstacles : public CObject
{
public:
	CObstacles();
	~CObstacles();
	void Delete();
	virtual void Init() = 0;
	virtual void Load() = 0;
	void Load(int handle);
	void Load(const char* path);
	virtual void Step() = 0;
	virtual void Draw() = 0;
	virtual void Fin() = 0;
	virtual CObstacles* Clone() = 0;
	OBSTACLES_STATE GetCurrenState()const { return current_state_; }
	OBSTACLES_STATE GetNextState() const { return next_state_; }
	void SetNextState(OBSTACLES_STATE state) { next_state_ = state; };
	int GetHandle() const { return handle_; }
	void OnCollisionEnter(CObject* another) override;

	int handle_;
	OBSTACLES_STATE current_state_;
	BoxCollision* collision_;
	float escape_speed_;
	float radian_;

private:
	OBSTACLES_STATE next_state_;
};