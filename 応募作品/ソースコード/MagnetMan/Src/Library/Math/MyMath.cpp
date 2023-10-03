#include "DxLib.h"
#include "MyMath.h"
#include <math.h>

//�����̂̓����蔻��iAABB�j
// v1			�c �Ώ�A��X,Y,Z���W�i���f���̒��S���W�j
// w1, h1, d1	�c �Ώ�A��W,H,D�i�����A�����A���s���j
// v2			�c �Ώ�B��X,Y,Z���W�i���f���̒��S���W�j
// w2, h2, d2	�c �Ώ�B��W,H�i�����A�����A���s���j
bool IsHitRect(VECTOR v1, float w1, float h1, float d1, VECTOR v2, float w2, float h2, float d2)
{
	float w1_half = (w1 / 2);		//�Ώ�A�̉����̔����i���S����[�܂ł̒����j
	float h1_half = (h1 / 2);		//�Ώ�A�̍����̔����i���S����[�܂ł̒����j
	float d1_half = (d1 / 2);		//�Ώ�A�̉��s���̔����i���S����[�܂ł̒����j

	float x1min = v1.x - w1_half;	//�Ώ�A�̍ŏ�X
	float x1max = v1.x + w1_half;	//�Ώ�A�̍ő�X
	float y1min = v1.y - h1_half;	//�Ώ�A�̍ŏ�Y
	float y1max = v1.y + h1_half;	//�Ώ�A�̍ő�Y
	float z1min = v1.z - d1_half;	//�Ώ�A�̍ŏ�Z
	float z1max = v1.z + d1_half;	//�Ώ�A�̍ő�Z

	float w2_half = (w2 / 2);		//�Ώ�B�̉����̔����i���S����[�܂ł̒����j
	float h2_half = (h2 / 2);		//�Ώ�B�̍����̔����i���S����[�܂ł̒����j
	float d2_half = (d2 / 2);		//�Ώ�B�̉��s���̔����i���S����[�܂ł̒����j

	float x2min = v2.x - w2_half;		//�Ώ�B�̍ŏ�X
	float x2max = v2.x + w2_half;		//�Ώ�B�̍ő�X
	float y2min = v2.y - h2_half;		//�Ώ�B�̍ŏ�Y
	float y2max = v2.y + h2_half;		//�Ώ�B�̍ő�Y
	float z2min = v2.z - d2_half;		//�Ώ�B�̍ŏ�Z
	float z2max = v2.z + d2_half;		//�Ώ�B�̍ő�Z

	if (x1min < x2max && x1max > x2min && y1min < y2max && y1max > y2min && z1min < z2max && z1max > z2min)
		return true;

	return false;
}

bool IsHitRect(AABB aabb1, AABB aabb2)
{
	const Vector3D box1_pos(aabb1.pos);
	const Vector3D box2_pos(aabb2.pos);

	const Vector3D box1_half(aabb1.half);
	const Vector3D box2_half(aabb2.half);

	if (box1_pos - box1_half < box2_pos + box2_half &&
		box1_pos + box1_half > box2_pos - box2_half) {
		return true;
	}

	return false;
}

//���Ƌ�
// v1	�c �Ώ�A�̍��W
// r1	�c �Ώ�A�̔��a
// v2	�c �Ώ�B�̍��W
// r2	�c �Ώ�B�̔��a
bool IsHitSphere(VECTOR v1, float r1, VECTOR v2, float r2)
{
	float len_x = (v2.x - v1.x) * (v2.x - v1.x);
	float len_y = (v2.y - v1.y) * (v2.y - v1.y);
	float len_z = (v2.z - v1.z) * (v2.z - v1.z);
	float len_r = (r2 + r1) * (r2 + r1);

	if (len_x + len_y + len_z <= len_r)
	{
		return true;
	}

	return false;
}

void ExtrudePosX(const AABB& aabb1, float move1_x, AABB* aabb2, float* move2_x)
{
	// 2�̃{�b�N�X�̍�
	const float difference_value = aabb1.half.x + aabb2->half.x;

	// �Œ�{�b�N�X���E�ړ� �܂��� �ړ��{�b�N�X�����ړ�
	if (*move2_x < 0.f || move1_x > 0.f) {
		// �����߂�
		aabb2->pos.x = aabb1.pos.x + difference_value;

		// �ړ��x�N�g�����[���ɂ���
		*move2_x = 0.f;
	}
	// �Œ�{�b�N�X�����ړ� �܂��� �ړ��{�b�N�X���E�ړ�
	else if (*move2_x > 0.f || move1_x < 0.f) {
		// �����߂�
		aabb2->pos.x = aabb1.pos.x - difference_value;

		// �ړ��x�N�g�����[���ɂ���
		*move2_x = 0.f;
	}
}

void ExtrudePosY(const AABB& aabb1, float move1_y, AABB* aabb2, float* move2_y)
{
	// 2�̃{�b�N�X�̍�
	const float difference_value = aabb1.half.y + aabb2->half.y;

	// �Œ�{�b�N�X����ړ� �܂��� �ړ��{�b�N�X�����ړ�
	if (*move2_y < 0.f || move1_y > 0.f) {
		// �����߂�
		aabb2->pos.y = aabb1.pos.y + difference_value;

		// �ړ��x�N�g�����[���ɂ���
		*move2_y = 0.f;
	}
	// �Œ�{�b�N�X����ړ� �܂��� �ړ��{�b�N�X�����ړ�
	else if (*move2_y > 0.f || move1_y < 0.f) {
		// �����߂�
		aabb2->pos.y = aabb1.pos.y - difference_value;

		// �ړ��x�N�g�����[���ɂ���
		*move2_y = 0.f;
	}
}

void ExtrudePosZ(const AABB& aabb1, float move1_z, AABB* aabb2, float* move2_z)
{
	// 2�̃{�b�N�X�̍�
	const float difference_value = aabb1.half.z + aabb2->half.z;

	// �Œ�{�b�N�X�����ړ� �܂��� �ړ��{�b�N�X����O�ړ�
	if (*move2_z < 0.f || move1_z > 0.f) {
		// �����߂�
		aabb2->pos.z = aabb1.pos.z + difference_value;

		// �ړ��x�N�g�����[���ɂ���
		*move2_z = 0.f;
	}
	// �Œ�{�b�N�X����O�ړ� �܂��� �ړ��{�b�N�X�����ړ�
	else if (*move2_z > 0.f || move1_z < 0.f) {
		// �����߂�
		aabb2->pos.z = aabb1.pos.z - difference_value;

		// �ړ��x�N�g�����[���ɂ���
		*move2_z = 0.f;
	}
}

void ExtrudePos(const AABB& aabb1, const Vector3D& move1, AABB* aabb2, Vector3D* move2)
{
	// �ړ��x�N�g����ۑ�
	const Vector3D pre_move = *move2;

	// 1�t���[���O�̃{�b�N�X���W���擾
	const Vector3D pre_box_pos = aabb2->pos - pre_move;

	// X���̂ݓ��������Ƃ��̃{�b�N�X���W���擾
	const Vector3D box_only_xaxis_move_pos(pre_box_pos.x + pre_move.x, pre_box_pos.y, pre_box_pos.z);

	// �����蔻������
	if (IsHitRect(aabb1, AABB(box_only_xaxis_move_pos, aabb2->half))) {
		// �����߂�����
		ExtrudePosX(aabb1, move1.x, aabb2, &move2->x);
	}

	// Y���̂ݓ��������Ƃ��̃{�b�N�X���W���擾
	const Vector3D box_only_yaxis_move_pos(aabb2->pos.x, pre_box_pos.y + pre_move.y, pre_box_pos.z);

	// �����蔻������
	if (IsHitRect(aabb1, AABB(box_only_yaxis_move_pos, aabb2->half))) {
		ExtrudePosX(aabb1, move1.y, aabb2, &move2->y);
	}

	// Z���̂ݓ��������Ƃ��̃{�b�N�X���W���擾
	const Vector3D box_only_zaxis_move_pos(aabb2->pos.x, aabb2->pos.y, pre_box_pos.z + pre_move.z);

	// �����蔻������
	if (IsHitRect(aabb1, AABB(box_only_zaxis_move_pos, aabb2->half))) {
		ExtrudePosX(aabb1, move1.z, aabb2, &move2->z);
	}
}

VECTOR operator+(VECTOR vecA, VECTOR vecB)
{
	return VGet(vecA.x + vecB.x, vecA.y + vecB.y, vecA.z + vecB.z);
}

VECTOR operator+(VECTOR vec, float value)
{
	return VGet(vec.x + value, vec.y + value, vec.z + value);
}

VECTOR operator-(VECTOR vecA, VECTOR vecB)
{
	return VGet(vecA.x - vecB.x, vecA.y - vecB.y, vecA.z - vecB.z);
}

VECTOR operator-(VECTOR vec, float value)
{
	return VGet(vec.x - value, vec.y - value, vec.z - value);
}

VECTOR operator*(VECTOR vecA, VECTOR vecB)
{
	return VGet(vecA.x * vecB.x, vecA.y * vecB.y, vecA.z * vecB.z);
}

VECTOR operator*(VECTOR vec, float value)
{
	return VGet(vec.x * value, vec.y * value, vec.z * value);
}

VECTOR operator/(VECTOR vecA, VECTOR vecB)
{
	return VGet(vecA.x / vecB.x, vecA.y / vecB.y, vecA.z / vecA.z);
}

VECTOR operator/(VECTOR vec, float value)
{
	float inv = 1.f / value;

	return VGet(vec.x * inv, vec.y * inv, vec.z * inv);
}

VECTOR VecCreate(VECTOR vecA, VECTOR vecB)
{
	return vecB - vecA;
}

//�t���[�g�Ή��p
template<class T>
static T Abs(const T a) { return (a >= 0.) ? a : -a; }

//�����蔻��
VECTOR Extrude(VECTOR ExtrudePos, VECTOR ExtrudeSize, VECTOR pos, VECTOR size)
{
	VECTOR Dis = VecCreate(ExtrudePos, pos);


	if (!(ExtrudePos.y > pos.y - (size.y * 0.5) && ExtrudePos.y < pos.y + (size.y * 0.5)))
	{
		if (Dis.y < 0.f) {
			Dis.y = pos.y + (ExtrudeSize.y * 0.5f) + (size.y * 0.5f);
		}
		else
		{
			Dis.y = pos.y - (ExtrudeSize.y * 0.5f) - (size.y * 0.5f);
		}
		Dis.x = ExtrudePos.x;
		Dis.z = ExtrudePos.z;

	}

	else if (Abs(Dis.x) > Abs(Dis.z))
	{
		Dis.x = Dis.x < 0 ? pos.x + (ExtrudeSize.x + size.x) * 0.5f : pos.x - (ExtrudeSize.x + size.x) * 0.5f;


		if (Abs(Dis.z) > size.z)
		{
			Dis.z = Dis.z < 0 ? pos.z + (ExtrudeSize.z + size.z) * 0.5f : pos.z - (ExtrudeSize.z + size.z) * 0.5f;
		}

		else
		{
			Dis.z = ExtrudePos.z;
		}
		Dis.y = ExtrudePos.y;

	}

	else if (Abs(Dis.z) > Abs(Dis.x))
	{
		Dis.z = Dis.z < 0 ? pos.z + (ExtrudeSize.z + size.z) * 0.5f : pos.z - (ExtrudeSize.z + size.z) * 0.5f;


		if (Abs(Dis.x) > size.z)
		{
			Dis.x = Dis.x < 0 ? pos.x + (ExtrudeSize.x + size.x) * 0.5f : pos.x - (ExtrudeSize.x + size.x) * 0.5f;
		}

		else
		{
			Dis.x = ExtrudePos.x;
		}
		Dis.y = ExtrudePos.y;
	}


	return Dis;
}


float VecLong(VECTOR PosA, VECTOR PosB)
{
	float result;
	result = sqrtf((PosA.x - PosB.x) * (PosA.x - PosB.x) + (PosA.y - PosB.y) * (PosA.y - PosB.y) + (PosA.z - PosB.z) * (PosA.z - PosB.z));
	return result;
}



VECTOR VecAdd(VECTOR vecA, VECTOR vecB)
{
	VECTOR result;
	result.x = vecA.x + vecB.x;
	result.y = vecA.y + vecB.y;
	result.z = vecA.z + vecB.z;

	return result;
}

VECTOR VecScale(VECTOR vec, float scale)
{
	VECTOR result;
	result.x = vec.x * scale;
	result.y = vec.y * scale;
	result.z = vec.z * scale;

	return result;
}

//�x�N�g������]������
VECTOR VecRotation(VECTOR vec, VECTOR rotation)
{
	VECTOR result = { 0 };
	MATRIX dir = GetldentityMatrix();
	MATRIX rotation_mat = GetRotationMatrix(rotation);

	dir = MatMult(dir, rotation_mat);
	result = MatTransform(rotation_mat, vec);

	return result;
}


MATRIX GetldentityMatrix()
{
	MATRIX result = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				result.m[i][j] = 1;
			}
			else {
				result.m[i][j] = 0;
			}
		}
	}

	return result;
}


//X����]�s��̎擾
MATRIX GetPitchMatrix(float rot)
{
	MATRIX result = GetldentityMatrix();
	result.m[1][1] = cosf(rot);
	result.m[1][2] = -sinf(rot);
	result.m[2][1] = sinf(rot);
	result.m[2][2] = cosf(rot);

	return result;
}

//Y����]�s��̎擾
MATRIX GetYawMatrix(float rot)
{
	MATRIX result = GetldentityMatrix();
	result.m[0][0] = cosf(rot);
	result.m[0][2] = sinf(rot);
	result.m[2][0] = -sinf(rot);
	result.m[2][2] = cosf(rot);

	return result;
}

//Z����]�s��̎擾
MATRIX GetRollMatrix(float rot)
{
	MATRIX result = GetldentityMatrix();
	result.m[0][0] = cosf(rot);
	result.m[0][1] = -sinf(rot);
	result.m[1][0] = sinf(rot);
	result.m[1][1] = cosf(rot);

	return result;
}

MATRIX MatMult(MATRIX matA, MATRIX matB)
{
	MATRIX result = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += (matA.m[i][k] * matB.m[k][j]);
			}
		}
	}

	return result;
}


MATRIX GetRotationMatrix(VECTOR rotation)
{
	// �e���̉�]�s����擾
	MATRIX result = GetldentityMatrix();
	MATRIX pitch = GetPitchMatrix(rotation.x);
	MATRIX yaw = GetYawMatrix(rotation.y);
	MATRIX roll = GetRollMatrix(rotation.z);

	// �s�������
	result = MatMult(result, roll);
	result = MatMult(result, yaw);
	result = MatMult(result, pitch);

	return result;
}


VECTOR MatTransform(MATRIX mat, VECTOR vec)
{
	float work[4] = { 0 };
	float result_buf[4] = { 0 };
	VECTOR result_vec = { 0 };
	work[0] = vec.x;
	work[1] = vec.y;
	work[2] = vec.z;
	work[3] = 1;
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			result_buf[i] += (mat.m[i][k] * work[k]);
		}
	}

	result_vec.x = result_buf[0];
	result_vec.y = result_buf[1];
	result_vec.z = result_buf[2];

	return result_vec;
}

float DegreeToRadian(float rot)
{
	return rot * DX_PI_F / 180.f;
}

// ���W�A���p����Sin�g���擾
float GetSin(float rad)
{
	return sinf(rad);
}

// ���W�A���p����min�`max�͈̔͂�Sin�g���擾
float GetSin(float min, float max, float rad)
{
	float mult = (max - min) / 2.0f;
	return (sinf(rad) + 1.0f) * mult + min;
}
