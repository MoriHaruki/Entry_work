#include "DebugCamera.h"
#define CAMERA_SPD 0.1f

CDebugCamera::CDebugCamera() : pos_(), look_()
{
}

CDebugCamera::~CDebugCamera()
{

}

void CDebugCamera::Init(Vector3D pos, Vector3D look)
{
	pos_ = pos;
	look_ = look;
}

void CDebugCamera::Step()
{
	
	if (CheckHitKey(KEY_INPUT_W) == 1)
	{
		look_.y += CAMERA_SPD;
	}
		 
	if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		look_.y -= CAMERA_SPD;
	}

	if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		look_.x += CAMERA_SPD;
	}

	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		look_.x -= CAMERA_SPD;
	}
}

void CDebugCamera::Update()
{
	SetCameraPositionAndTarget_UpVecY(pos_, look_);
}

void CDebugCamera::Draw()
{
	 DrawSphere3D(look_, 1.0f, 10, GetColor(255, 255, 255), GetColor(255, 255, 255),false);
	 DrawString(10, 104, " <デバックカメラ>", GetColor(255, 255, 128));
	 DrawFormatString(530, 26, GetColor(255, 255, 255), "Pos  = (%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);
	 DrawFormatString(530, 42, GetColor(255, 255, 255), "Look = (%.2f, %.2f, %.2f)", look_.x, look_.y, look_.z);
}

void CDebugCamera::Fin()
{
}

void CDebugCamera::SetNearFar(float near_val, float far_val)
{
}
