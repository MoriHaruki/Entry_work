#pragma once
#include "DxLib.h"
#include "Obstacles.h"
#include "Object/Object.h"

class CGoal2 : public CObstacles
{
public:

	CGoal2();
	~CGoal2();

	void Init() override;
	void Load() override;
	void Delete();
	void Step() override;
	void Draw() override;
	void Fin() override;

	void SetGoal2Flag(bool goal_flag2) { goal_flag_2 = goal_flag2; }
	bool GetGoal2Flag() const { return goal_flag_2; }

	CObstacles* Clone() override;
	void OnCollisionEnter(CObject* another) override;

	bool goal_flag_2;
};
