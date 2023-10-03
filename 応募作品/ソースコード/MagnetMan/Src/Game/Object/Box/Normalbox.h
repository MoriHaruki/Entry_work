#pragma once
#include "DxLib.h"
#include "Box.h"
#include "Object/Object.h"
#include "BoxParameter.h"
#include "Collision/SphereCollision.h"

class CNormalBox : public CBox
{

public:
	CNormalBox();
	~CNormalBox();
	void Init() override;
	void Load() override;
	void Delete() ;
	void Step() override;
	void Draw() override;
	void Fin() override;
	CBox* Clone() override;
	void OnCollisionEnter(CObject* another) override;

private:
	void CreateCollision();
}; 
