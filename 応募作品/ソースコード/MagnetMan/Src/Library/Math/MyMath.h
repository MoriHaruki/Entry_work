#pragma once

#include "DxLib.h"
#include "Primitive/Primitive.h"

bool IsHitRect(VECTOR v1, float w1, float h1, float d1, VECTOR v2, float w2, float h2, float d2);

bool IsHitRect(AABB aabb1, AABB aabb2);

bool IsHitSphere(VECTOR v1, float r1, VECTOR v2, float r2);

/*
	AABB��AABB��X�����̉����߂�����(�Е���AABB���Œ肷�鎞)
	�����F	aabb1		:	�Œ�{�b�N�X(AABB)
			move1_x		:	�Œ�{�b�N�X�̈ړ��x�N�g��
			aabb2		:	�����Ă���{�b�N�X(AABB)(�߂�l)
			move2_x		:	�����Ă���{�b�N�X�̈ړ��x�N�g��(X����)(�߂�l)
*/
void ExtrudePosX(const AABB& aabb1, float move1_x, AABB* aabb2, float* move2_x);

/*
	AABB��AABB��Y�����̉����߂�����(�Е���AABB���Œ肷�鎞)
	�����F	aabb1		:	�Œ�{�b�N�X(AABB)
			move1_y		:	�Œ�{�b�N�X�̈ړ��x�N�g��
			aabb2		:	�����Ă���{�b�N�X(AABB)(�߂�l)
			move2_y		:	�����Ă���{�b�N�X�̈ړ��x�N�g��(Y����)(�߂�l)
*/
void ExtrudePosY(const AABB& aabb1, float move1_y, AABB* aabb2, float* move2_y);

/*
	AABB��AABB��Z�����̉����߂�����(�Е���AABB���Œ肷�鎞)
	�����F	aabb1		:	�Œ�{�b�N�X(AABB)
			move1_z		:	�Œ�{�b�N�X�̈ړ��x�N�g��
			aabb2		:	�����Ă���{�b�N�X(AABB)(�߂�l)
			move2_z		:	�����Ă���{�b�N�X�̈ړ��x�N�g��(Z����)(�߂�l)
*/
void ExtrudePosZ(const AABB& aabb1, float move1_z, AABB* aabb2, float* move2_z);

/*
	AABB��AABB�̉����߂�����(�Е���AABB���Œ肷�鎞)
	�����F	aabb1		:	�Œ�{�b�N�X(AABB)
			move1		:	�Œ�{�b�N�X�̈ړ��x�N�g��
			aabb2		:	�����Ă���{�b�N�X(AABB)(�߂�l)
			move2		:	�����Ă���{�b�N�X�̈ړ��x�N�g��(Z����)(�߂�l)
*/
void ExtrudePos(const AABB& aabb1, const Vector3D& move1, AABB* aabb2, Vector3D* move2);

VECTOR operator+ (VECTOR vecA, VECTOR vecB);

VECTOR operator+ (VECTOR vec, float value);

//�}�C�i�X���Z�q��`
VECTOR operator- (VECTOR vecA, VECTOR vecB);

VECTOR operator- (VECTOR vec, float value);

VECTOR operator* (VECTOR vecA, VECTOR vecB);

VECTOR operator* (VECTOR vec, float value);

VECTOR operator/ (VECTOR vecA, VECTOR vecB);

VECTOR operator/ (VECTOR vec, float value);

VECTOR VecCreate(VECTOR vecA, VECTOR vecB);

VECTOR Extrude(VECTOR ExtrudePos, VECTOR ExtrudeSize, VECTOR pos, VECTOR size);

VECTOR VecAdd(VECTOR vecA, VECTOR vecB);

VECTOR VecScale(VECTOR vec, float scale);//�x�N�g���̃X�J���[�{

VECTOR VecRotation(VECTOR vec, VECTOR rotation);

MATRIX GetldentityMatrix();

MATRIX GetRotationMatrix(VECTOR rotation);

MATRIX GetPitchMatrix(float rot);//X����]�s��̎擾

MATRIX GetYawMatrix(float rot);//Y����]�s��̎擾

MATRIX GetRollMatrix(float rot);//Z����]�s��̎擾

MATRIX MatMult(MATRIX matA, MATRIX matB);//�s��̊|���Z

VECTOR MatTransform(MATRIX mat, VECTOR vec);//�x�N�g���~�s��

float DegreeToRadian(float rot);//�f�B�O���[�p�����W�A���ɕϊ�

float VecLong(VECTOR PosA, VECTOR PosB);//�x�N�g���̒���

float GetSin(float rad);

float GetSin(float min, float max, float rad);
