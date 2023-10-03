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

	//�J�����̎��_���v���C���[�̌��ɂ���
	{
		Vector3D player_dir;
		//�v���C���[�̌��������߂�
		player_dir.x = sinf(player_rot.y);
		player_dir.z = cosf(player_rot.y);
		Vector3D offset_vec;
		//�v���C���[�̈ړ��x�N�g���̋t�����̃x�N�g�������߁A
		//���炷�ʂ���Z����
		offset_vec(player_dir * CAMERA_OFFSET_POS);
		//�v���C���[���W�ɂ��炷�ʂ����Z���A
		//�J�����̍��W�����߂�
		pos_ += Vector3D(offset_vec.x, offset_vec.y, offset_vec.z);
	}
	//�J�����̒����_���v���C���[�̏�ɂ���
	look_.y += CAMERA_OFFSET_LOOK_Y;
	//�J�����̍���
	pos_.y += CAMERA_HEIGHT;

	
}

void CPlayCamera::Update()
{
	SetCameraPositionAndTarget_UpVecY(pos_, look_);
}

void CPlayCamera::Fin()
{
}

//�j�A�N���b�v�E�t�@�[�N���b�v�̐ݒ�
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
