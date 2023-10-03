#include "DxLib.h"
#include "MyMath.h"
#include <math.h>

//直方体の当たり判定（AABB）
// v1			… 対象AのX,Y,Z座標（モデルの中心座標）
// w1, h1, d1	… 対象AのW,H,D（横幅、高さ、奥行き）
// v2			… 対象BのX,Y,Z座標（モデルの中心座標）
// w2, h2, d2	… 対象BのW,H（横幅、高さ、奥行き）
bool IsHitRect(VECTOR v1, float w1, float h1, float d1, VECTOR v2, float w2, float h2, float d2)
{
	float w1_half = (w1 / 2);		//対象Aの横幅の半分（中心から端までの長さ）
	float h1_half = (h1 / 2);		//対象Aの高さの半分（中心から端までの長さ）
	float d1_half = (d1 / 2);		//対象Aの奥行きの半分（中心から端までの長さ）

	float x1min = v1.x - w1_half;	//対象Aの最小X
	float x1max = v1.x + w1_half;	//対象Aの最大X
	float y1min = v1.y - h1_half;	//対象Aの最小Y
	float y1max = v1.y + h1_half;	//対象Aの最大Y
	float z1min = v1.z - d1_half;	//対象Aの最小Z
	float z1max = v1.z + d1_half;	//対象Aの最大Z

	float w2_half = (w2 / 2);		//対象Bの横幅の半分（中心から端までの長さ）
	float h2_half = (h2 / 2);		//対象Bの高さの半分（中心から端までの長さ）
	float d2_half = (d2 / 2);		//対象Bの奥行きの半分（中心から端までの長さ）

	float x2min = v2.x - w2_half;		//対象Bの最小X
	float x2max = v2.x + w2_half;		//対象Bの最大X
	float y2min = v2.y - h2_half;		//対象Bの最小Y
	float y2max = v2.y + h2_half;		//対象Bの最大Y
	float z2min = v2.z - d2_half;		//対象Bの最小Z
	float z2max = v2.z + d2_half;		//対象Bの最大Z

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

//球と球
// v1	… 対象Aの座標
// r1	… 対象Aの半径
// v2	… 対象Bの座標
// r2	… 対象Bの半径
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
	// 2つのボックスの差
	const float difference_value = aabb1.half.x + aabb2->half.x;

	// 固定ボックスが右移動 または 移動ボックスが左移動
	if (*move2_x < 0.f || move1_x > 0.f) {
		// 押し戻す
		aabb2->pos.x = aabb1.pos.x + difference_value;

		// 移動ベクトルをゼロにする
		*move2_x = 0.f;
	}
	// 固定ボックスが左移動 または 移動ボックスが右移動
	else if (*move2_x > 0.f || move1_x < 0.f) {
		// 押し戻す
		aabb2->pos.x = aabb1.pos.x - difference_value;

		// 移動ベクトルをゼロにする
		*move2_x = 0.f;
	}
}

void ExtrudePosY(const AABB& aabb1, float move1_y, AABB* aabb2, float* move2_y)
{
	// 2つのボックスの差
	const float difference_value = aabb1.half.y + aabb2->half.y;

	// 固定ボックスが上移動 または 移動ボックスが下移動
	if (*move2_y < 0.f || move1_y > 0.f) {
		// 押し戻す
		aabb2->pos.y = aabb1.pos.y + difference_value;

		// 移動ベクトルをゼロにする
		*move2_y = 0.f;
	}
	// 固定ボックスが上移動 または 移動ボックスが下移動
	else if (*move2_y > 0.f || move1_y < 0.f) {
		// 押し戻す
		aabb2->pos.y = aabb1.pos.y - difference_value;

		// 移動ベクトルをゼロにする
		*move2_y = 0.f;
	}
}

void ExtrudePosZ(const AABB& aabb1, float move1_z, AABB* aabb2, float* move2_z)
{
	// 2つのボックスの差
	const float difference_value = aabb1.half.z + aabb2->half.z;

	// 固定ボックスが奥移動 または 移動ボックスが手前移動
	if (*move2_z < 0.f || move1_z > 0.f) {
		// 押し戻す
		aabb2->pos.z = aabb1.pos.z + difference_value;

		// 移動ベクトルをゼロにする
		*move2_z = 0.f;
	}
	// 固定ボックスが手前移動 または 移動ボックスが奥移動
	else if (*move2_z > 0.f || move1_z < 0.f) {
		// 押し戻す
		aabb2->pos.z = aabb1.pos.z - difference_value;

		// 移動ベクトルをゼロにする
		*move2_z = 0.f;
	}
}

void ExtrudePos(const AABB& aabb1, const Vector3D& move1, AABB* aabb2, Vector3D* move2)
{
	// 移動ベクトルを保存
	const Vector3D pre_move = *move2;

	// 1フレーム前のボックス座標を取得
	const Vector3D pre_box_pos = aabb2->pos - pre_move;

	// X軸のみ動かしたときのボックス座標を取得
	const Vector3D box_only_xaxis_move_pos(pre_box_pos.x + pre_move.x, pre_box_pos.y, pre_box_pos.z);

	// 当たり判定を取る
	if (IsHitRect(aabb1, AABB(box_only_xaxis_move_pos, aabb2->half))) {
		// 押し戻し処理
		ExtrudePosX(aabb1, move1.x, aabb2, &move2->x);
	}

	// Y軸のみ動かしたときのボックス座標を取得
	const Vector3D box_only_yaxis_move_pos(aabb2->pos.x, pre_box_pos.y + pre_move.y, pre_box_pos.z);

	// 当たり判定を取る
	if (IsHitRect(aabb1, AABB(box_only_yaxis_move_pos, aabb2->half))) {
		ExtrudePosX(aabb1, move1.y, aabb2, &move2->y);
	}

	// Z軸のみ動かしたときのボックス座標を取得
	const Vector3D box_only_zaxis_move_pos(aabb2->pos.x, aabb2->pos.y, pre_box_pos.z + pre_move.z);

	// 当たり判定を取る
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

//フロート対応用
template<class T>
static T Abs(const T a) { return (a >= 0.) ? a : -a; }

//当たり判定
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

//ベクトルを回転させる
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


//X軸回転行列の取得
MATRIX GetPitchMatrix(float rot)
{
	MATRIX result = GetldentityMatrix();
	result.m[1][1] = cosf(rot);
	result.m[1][2] = -sinf(rot);
	result.m[2][1] = sinf(rot);
	result.m[2][2] = cosf(rot);

	return result;
}

//Y軸回転行列の取得
MATRIX GetYawMatrix(float rot)
{
	MATRIX result = GetldentityMatrix();
	result.m[0][0] = cosf(rot);
	result.m[0][2] = sinf(rot);
	result.m[2][0] = -sinf(rot);
	result.m[2][2] = cosf(rot);

	return result;
}

//Z軸回転行列の取得
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
	// 各軸の回転行列を取得
	MATRIX result = GetldentityMatrix();
	MATRIX pitch = GetPitchMatrix(rotation.x);
	MATRIX yaw = GetYawMatrix(rotation.y);
	MATRIX roll = GetRollMatrix(rotation.z);

	// 行列を合成
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

// ラジアン角からSin波を取得
float GetSin(float rad)
{
	return sinf(rad);
}

// ラジアン角からmin～maxの範囲でSin波を取得
float GetSin(float min, float max, float rad)
{
	float mult = (max - min) / 2.0f;
	return (sinf(rad) + 1.0f) * mult + min;
}
