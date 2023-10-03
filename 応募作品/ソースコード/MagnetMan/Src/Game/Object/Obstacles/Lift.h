#pragma once
#include "DxLib.h"
#include"Obstacles.h"
#include "ObstaclesParameter.h"

class CLift : public CObstacles
{
public:
	CLift();
	~CLift();
	void Init() override;
	void Load() override;
	void Delete();
	void Step() override;
	void Draw() override;
	void Fin() override;
	CObstacles* Clone() override;
	void OnCollisionEnter(CObject* another) override;
	
private:
	float pre_offset_;
	float current_offset_;
};
