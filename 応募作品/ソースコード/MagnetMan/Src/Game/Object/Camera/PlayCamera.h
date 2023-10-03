#pragma once

#include "Dxlib.h"

#include "../Common/Common.h"
#include "../Player/Player.h"

class CPlayCamera:public CObject
{
public:
	CPlayCamera();
	~CPlayCamera();
	void Init();
	void Init(Vector3D pos, Vector3D look);
	void Step();
	void Update();
	void Fin();
	void SetNearFar(float near_val, float far_val);
	Vector3D GetPos() const { return pos_; }
	Vector3D GetFocus() const { return look_; }	// íçéãì_éÊìæ
	void SetPos(Vector3D pos) { pos_(pos); }

private:
	void CalcForward();

private:
	Vector3D pos_;
	Vector3D look_;
	Vector3D forward_;
};