#pragma once

#include "Collision/CollisionParameter.h"

namespace BULLET
{
	constexpr float BULLET_W = (1.0f);
	constexpr float BULLET_H = (1.0f);
	constexpr float BULLET_D = (1.0f);
	constexpr float BULLET_HALF = 1.0f*0.5;
	constexpr int BULLET_MAX = 1000;
	const float OPTIMIZE_INTERVAL = 0.0f;
}

// �o���b�gID�F�g�p����摜�̊m�蓙�Ɏg�p����
enum BulletID {
	BULLET_ID_PLAYER_PLUS,
	BULLET_ID_PLAYER_MINUS,
	BULLET_ID_NUM,
};

struct BulletParameter {

	int id;						// ID
	const char FILE_PATH[128];	// �摜�t�@�C���p�X
	float size;					// �T�C�Y
	float	bullet_speed;		// �o���b�g�̈ړ����x
	float	bullet_interval;	// �o���b�g�̔��ˊԊu
	float	bullet_life;		// �o���b�g�̎���
};


// TODO:�f�[�^�x�[�X�ɏC��
static const BulletParameter BULLET_DATABASE[BULLET_ID_NUM] = {
	// ID							�摜�t�@�C���p�X			�@�T�C�Y   speed   interval		life
	BULLET_ID_PLAYER_PLUS,	"Data/Model/Bullet/PlusBullet.x",		1,		0.6f,	20.0f,		0.4f,
	BULLET_ID_PLAYER_MINUS,	"Data/Model/Bullet/MinusGrayBullet.x",	1,		0.6f,	20.0f,		0.4f,
};

