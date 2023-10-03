#pragma once

#include "Bullet.h"
#include "Collision/BoxCollision.h"

class CMinusBullet :public CBullet
{
public:
	CMinusBullet(int id);
	~CMinusBullet();

public:
	void Init() override;
	void Step() override;
	void Update() override;
	void Delete() override;
	CBullet* Clone() override;
	void OnCollisionEnter(CObject* another) override;

};