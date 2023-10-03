#pragma once

#include "Vector/Vector3D.h"

//プレイヤー関連
constexpr float PLAY_W = 1.0f;//プレイヤーの横幅
constexpr float PLAY_H = 2.5f;	//プレイヤーの高さ
constexpr float PLAY_D = 1.0f;	//プレイヤーの奥行き
constexpr Vector3D PLAYER_SIZE = Vector3D(PLAY_W, PLAY_H, PLAY_D);
constexpr float PLAY_F =2.0f;	//プレイヤーの横幅半分
constexpr float PLAY_HP = 100.0f;//プレイヤーHP
constexpr float ADD_GRAVITY = -0.05f;
constexpr float MAX_GRAVITY = -0.6f;
constexpr float JUMP_VALUE = 0.8f;		//ジャンプの移動量
constexpr float PLAYER_RAD = 1.0f;	//プレイヤーの半径;
constexpr float PLAYER_ROT = 4.0f;	//プレイヤーの回転角度;
constexpr float START_PLAYER_ROT =-90.0f;

//constexpr Vector3D DEFAULT_POS = Vector3D(5.5f, 2.1f, 0.0f);
constexpr Vector3D DEFAULT_POS1 = Vector3D(-60.0f, 3.0f, 0.0f);
constexpr Vector3D DEFAULT_POS2 = Vector3D(-3.0f, 5.0f, 0.0f);
