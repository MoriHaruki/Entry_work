#pragma once
#include "DxLib.h"
#include "Obstacles.h"
#include "Object/Object.h"

class CGoal : public CObstacles
{
public:

	CGoal();
	~CGoal();

	void Init() override;
	void Load() override;
	void Delete();
	void Step() override;
	void Draw() override;
	void Fin() override;
	
	void SetGoalFlag(bool goal_flag) { goal_flag_ = goal_flag; }
	bool GetGoalFlag() const { return goal_flag_; }

	CObstacles* Clone() override;
	void OnCollisionEnter(CObject* another) override;

	bool goal_flag_;
};
