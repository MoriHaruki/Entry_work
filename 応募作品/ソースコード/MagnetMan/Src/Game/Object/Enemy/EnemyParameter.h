#pragma once
#include "DxLib.h"

//プレイヤー関連
namespace ENEMY
{
	constexpr float ENEMY_W = (2.0f);	//プレイヤーの横幅;
	constexpr float ENEMY_H = (2.0f);	//プレイヤーの高さ;
	constexpr float ENEMY_D = (2.0f);	//プレイヤーの奥行き;
	constexpr float ENEMY_RAD = (1.0f);	//プレイヤーの半径;
	constexpr float ENEMY_JUMP_VAL = (0.2f);	//ジャンプ量;
	constexpr float ENEMY_JUMP_TIME = (0.8f);	//ジャンプの時間;
	constexpr float ENEMY_BPOS = (-20.0f);
	constexpr float GRAVITY = (0.15f);
	constexpr float COLLISION_RADIUS = 1.0f;
	constexpr float ESCAPE_ACCEL = 0.01f;
	constexpr float ESCAPE_TIME = 120.0f;
	constexpr int E_MAX_NUM = 2;
}

// ゲーム中のエネミーパラメータ
struct EnemyInfo {
	int id;
	float active_dist;
	float range;
	float speed;
	float stop;
	
};

constexpr EnemyInfo INIT_ENEMY_INFO
{
	//  id　　　 active_dist	rangeセンサー範囲　　　speed 速度　　 　stop　　
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




