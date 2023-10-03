#pragma once

#include "DxLib.h"
#include "Primitive/Primitive.h"

bool IsHitRect(VECTOR v1, float w1, float h1, float d1, VECTOR v2, float w2, float h2, float d2);

bool IsHitRect(AABB aabb1, AABB aabb2);

bool IsHitSphere(VECTOR v1, float r1, VECTOR v2, float r2);

/*
	AABBとAABBのX方向の押し戻し処理(片方のAABBを固定する時)
	引数：	aabb1		:	固定ボックス(AABB)
			move1_x		:	固定ボックスの移動ベクトル
			aabb2		:	動いているボックス(AABB)(戻り値)
			move2_x		:	動いているボックスの移動ベクトル(X方向)(戻り値)
*/
void ExtrudePosX(const AABB& aabb1, float move1_x, AABB* aabb2, float* move2_x);

/*
	AABBとAABBのY方向の押し戻し処理(片方のAABBを固定する時)
	引数：	aabb1		:	固定ボックス(AABB)
			move1_y		:	固定ボックスの移動ベクトル
			aabb2		:	動いているボックス(AABB)(戻り値)
			move2_y		:	動いているボックスの移動ベクトル(Y方向)(戻り値)
*/
void ExtrudePosY(const AABB& aabb1, float move1_y, AABB* aabb2, float* move2_y);

/*
	AABBとAABBのZ方向の押し戻し処理(片方のAABBを固定する時)
	引数：	aabb1		:	固定ボックス(AABB)
			move1_z		:	固定ボックスの移動ベクトル
			aabb2		:	動いているボックス(AABB)(戻り値)
			move2_z		:	動いているボックスの移動ベクトル(Z方向)(戻り値)
*/
void ExtrudePosZ(const AABB& aabb1, float move1_z, AABB* aabb2, float* move2_z);

/*
	AABBとAABBの押し戻し処理(片方のAABBを固定する時)
	引数：	aabb1		:	固定ボックス(AABB)
			move1		:	固定ボックスの移動ベクトル
			aabb2		:	動いているボックス(AABB)(戻り値)
			move2		:	動いているボックスの移動ベクトル(Z方向)(戻り値)
*/
void ExtrudePos(const AABB& aabb1, const Vector3D& move1, AABB* aabb2, Vector3D* move2);

VECTOR operator+ (VECTOR vecA, VECTOR vecB);

VECTOR operator+ (VECTOR vec, float value);

//マイナス演算子定義
VECTOR operator- (VECTOR vecA, VECTOR vecB);

VECTOR operator- (VECTOR vec, float value);

VECTOR operator* (VECTOR vecA, VECTOR vecB);

VECTOR operator* (VECTOR vec, float value);

VECTOR operator/ (VECTOR vecA, VECTOR vecB);

VECTOR operator/ (VECTOR vec, float value);

VECTOR VecCreate(VECTOR vecA, VECTOR vecB);

VECTOR Extrude(VECTOR ExtrudePos, VECTOR ExtrudeSize, VECTOR pos, VECTOR size);

VECTOR VecAdd(VECTOR vecA, VECTOR vecB);

VECTOR VecScale(VECTOR vec, float scale);//ベクトルのスカラー倍

VECTOR VecRotation(VECTOR vec, VECTOR rotation);

MATRIX GetldentityMatrix();

MATRIX GetRotationMatrix(VECTOR rotation);

MATRIX GetPitchMatrix(float rot);//X軸回転行列の取得

MATRIX GetYawMatrix(float rot);//Y軸回転行列の取得

MATRIX GetRollMatrix(float rot);//Z軸回転行列の取得

MATRIX MatMult(MATRIX matA, MATRIX matB);//行列の掛け算

VECTOR MatTransform(MATRIX mat, VECTOR vec);//ベクトル×行列

float DegreeToRadian(float rot);//ディグリー角をラジアンに変換

float VecLong(VECTOR PosA, VECTOR PosB);//ベクトルの長さ

float GetSin(float rad);

float GetSin(float min, float max, float rad);
