#pragma once
#include "DxLib.h"
#include "Box.h"
#include "Object/Object.h"
#include "BoxParameter.h"
#include "Collision/BoxCollision.h"

class CMinusBox : public CBox
{

public:
	CMinusBox();
	~CMinusBox();
	void Init() override;
	void Load() override;
	void Delete();
	void Step() override;
	void Draw() override;
	void Fin() override;
	CBox* Clone() override;
	void OnCollisionEnter(CObject* another) override;
	
private:
	void CreateCollision();
};