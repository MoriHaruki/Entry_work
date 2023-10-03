#pragma once
#include "Vector/Vector3D.h"

class CDebugCamera
{
public:
	CDebugCamera();
	~CDebugCamera();

	void Init(Vector3D pos, Vector3D look);
	void Step();
	void Update();
	void Draw();
	void Fin();
	void SetNearFar(float near_val, float far_val);

private:

	Vector3D pos_;
	Vector3D look_;

};