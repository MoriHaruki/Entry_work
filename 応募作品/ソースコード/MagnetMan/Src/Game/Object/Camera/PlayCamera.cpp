#include "PlayCamera.h"
#include <math.h>
#include "Math/MyMath.h"
#include "Object/Player/Player.h"
#include "Object/Player/PlayerManager.h"
#include "Field/Field.h"
#include "Input/InputManager.h"
#include "Input/GameInputParameter.h"


CPlayCamera::CPlayCamera()
{
}

CPlayCamera::~CPlayCamera()
{
}

void CPlayCamera::Init()
{
}

void CPlayCamera::Init(Vector3D pos, Vector3D look)
{
	pos_ = pos;
	look_ = look;
}

void CPlayCamera::Step()
{
	CPlayer* player = ThePlayerManager->GetPlayer();
	pos_(player->GetPos());
	look_(pos_);
	const Vector3D player_rot = player->GetRot();

	//カメラの視点をプレイヤーの後ろにする
	{
		Vector3D player_dir;
		//プレイヤーの向きを求める
		player_dir.x = sinf(player_rot.y);
		player_dir.z = cosf(player_rot.y);
		Vector3D offset_vec;
		//プレイヤーの移動ベクトルの逆方向のベクトルを求め、
		//ずらす量を乗算する
		offset_vec(player_dir * CAMERA_OFFSET_POS);
		//プレイヤー座標にずらす量を加算し、
		//カメラの座標を求める
		pos_ += Vector3D(offset_vec.x, offset_vec.y, offset_vec.z);
	}
	//カメラの注視点をプレイヤーの上にする
	look_.y += CAMERA_OFFSET_LOOK_Y;
	//カメラの高さ
	pos_.y += CAMERA_HEIGHT;

	
}

void CPlayCamera::Update()
{
	SetCameraPositionAndTarget_UpVecY(pos_, look_);
}

void CPlayCamera::Fin()
{
}

//ニアクリップ・ファークリップの設定
void CPlayCamera::SetNearFar(float near_val, float far_val)
{
	SetCameraNearFar(near_val, far_val);
}

void CPlayCamera::CalcForward()
{
	Vector3D forward;
	forward.x = sinf(rot_.y);
	forward.z = cosf(rot_.y);
	forward_(forward);
}
