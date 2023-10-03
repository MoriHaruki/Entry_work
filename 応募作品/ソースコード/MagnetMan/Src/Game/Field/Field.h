#pragma once

#include <DxLib.h>
#include "Vector/Vector3D.h"
#include "Field/FieldParameterh.h"

class CField {
private:
	int	handle_;
	bool hit_flg_;
	Vector3D pos_;
public:
	CField();
	~CField();
	void Init();
	void Step();
	void LoadData();
	bool	HitCheck(Vector3D center, float radius, Vector3D* result);
	Vector3D	HitCheck(Vector3D start, Vector3D end);
	void Draw();
	void Fin();
};