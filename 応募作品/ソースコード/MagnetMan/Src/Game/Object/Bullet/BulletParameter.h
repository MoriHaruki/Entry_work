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

// バレットID：使用する画像の確定等に使用する
enum BulletID {
	BULLET_ID_PLAYER_PLUS,
	BULLET_ID_PLAYER_MINUS,
	BULLET_ID_NUM,
};

struct BulletParameter {

	int id;						// ID
	const char FILE_PATH[128];	// 画像ファイルパス
	float size;					// サイズ
	float	bullet_speed;		// バレットの移動速度
	float	bullet_interval;	// バレットの発射間隔
	float	bullet_life;		// バレットの寿命
};


// TODO:データベースに修正
static const BulletParameter BULLET_DATABASE[BULLET_ID_NUM] = {
	// ID							画像ファイルパス			　サイズ   speed   interval		life
	BULLET_ID_PLAYER_PLUS,	"Data/Model/Bullet/PlusBullet.x",		1,		0.6f,	20.0f,		0.4f,
	BULLET_ID_PLAYER_MINUS,	"Data/Model/Bullet/MinusGrayBullet.x",	1,		0.6f,	20.0f,		0.4f,
};

