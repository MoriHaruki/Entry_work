#pragma once

#include "Bullet.h"
#include "Collision/BoxCollision.h"

class CPlusBullet :public CBullet
{
public:
	CPlusBullet(int id);
	~CPlusBullet();

public:
	void Init() override;
	void Step() override;
	void Update()override;
	void Delete() override;
	CBullet* Clone() override;
	void OnCollisionEnter(CObject* another) override;
};

