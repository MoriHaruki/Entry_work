#pragma once
#include "DxLib.h"

//�v���C���[�֘A
namespace ENEMY
{
	constexpr float ENEMY_W = (2.0f);	//�v���C���[�̉���;
	constexpr float ENEMY_H = (2.0f);	//�v���C���[�̍���;
	constexpr float ENEMY_D = (2.0f);	//�v���C���[�̉��s��;
	constexpr float ENEMY_RAD = (1.0f);	//�v���C���[�̔��a;
	constexpr float ENEMY_JUMP_VAL = (0.2f);	//�W�����v��;
	constexpr float ENEMY_JUMP_TIME = (0.8f);	//�W�����v�̎���;
	constexpr float ENEMY_BPOS = (-20.0f);
	constexpr float GRAVITY = (0.15f);
	constexpr float COLLISION_RADIUS = 1.0f;
	constexpr float ESCAPE_ACCEL = 0.01f;
	constexpr float ESCAPE_TIME = 120.0f;
	constexpr int E_MAX_NUM = 2;
}

// �Q�[�����̃G�l�~�[�p�����[�^
struct EnemyInfo {
	int id;
	float active_dist;
	float range;
	float speed;
	float stop;
	
};

constexpr EnemyInfo INIT_ENEMY_INFO
{
	//  id�@�@�@ active_dist	range�Z���T�[�͈́@�@�@speed ���x�@�@ �@stop�@�@
	0,		       20.f,	  		 2.0f,			 0.1f,	        0.00f,	
};

struct  EnemyParameter
{
	VECTOR startpos;
};

constexpr EnemyParameter ENEMY_DATABASE[ENEMY::E_MAX_NUM] =
{
	{{-21.0f, 100.0f ,-32.0f}},
	{{14.f,14.f,14.f}},
};




