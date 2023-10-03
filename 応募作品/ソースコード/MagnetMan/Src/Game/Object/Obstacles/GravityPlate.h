#pragma once
#include "Obstacles.h"
#include "Object/Object.h"

class CGravityPlate : public CObstacles
{
public:

	CGravityPlate();
	~CGravityPlate();

	void Init() override;
	void Load() override;
	void Delete();
	void Step() override;
	void Draw() override;
	void Fin() override;

	CObstacles* Clone() override;
	void OnCollisionEnter(CObject* another) override;
};
