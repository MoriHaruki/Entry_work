#pragma once
#include "Obstacles.h"
#include "Collision/SphereCollision.h"


class CLong : public CObstacles
{
public:
	CLong();
	~CLong();
	void Init() override;
	void Load() override;
	void Delete();
	void Step() override;
	void Draw() override;
	void Fin() override;
	CObstacles* Clone() override;
	void OnCollisionEnter(CObject* another) override;
private:
	void CreateCollision();

	float pre_offset_;
	float current_offset_;
};
