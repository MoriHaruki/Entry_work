#pragma once

#include "Vector/Vector3D.h"
#include "Matrix/Matrix.h"

namespace MyLib 
{
	/*
		Vector2DからVector3Dへのキャスト用関数
	*/
	inline Vector3D Vector2DCastToVector3D(const Vector2D& V) {
		return Vector3D(V.x, V.y, 0.f);
	}
	/*
		行列と3Dベクトルの掛け算の演算子のオーバーロード
		引数：	matrix		行列
				vector_3d	3Dベクトル
		戻り値：演算結果（3Dベクトル）
	*/
	inline Vector3D operator*(const Matrix& Mat, const Vector3D& V) {
		float work[4] = { V.x, V.y, V.z, 1.0f };
		float result_buf[3] = { 0.0f };
		result_buf[0] += (Mat.m[0] * work[0]);
		result_buf[0] += (Mat.m[1] * work[1]);
		result_buf[0] += (Mat.m[2] * work[2]);
		result_buf[0] += (Mat.m[3] * work[3]);

		result_buf[1] += (Mat.m[4] * work[0]);
		result_buf[1] += (Mat.m[5] * work[1]);
		result_buf[1] += (Mat.m[6] * work[2]);
		result_buf[1] += (Mat.m[7] * work[3]);

		result_buf[2] += (Mat.m[8] * work[0]);
		result_buf[2] += (Mat.m[9] * work[1]);
		result_buf[2] += (Mat.m[10] * work[2]);
		result_buf[2] += (Mat.m[11] * work[3]);

		return Vector3D(result_buf[0], result_buf[1], result_buf[2]);
	}
	/*
		行列と3Dベクトルの掛け算の演算子のオーバーロード
		引数：	matrix		行列
				vector_3d	3Dベクトル
		戻り値：演算結果（3Dベクトル）
	*/
	inline Vector3D operator*(const Vector3D& V, const Matrix& Mat) {
		float work[4] = { V.x, V.y, V.z, 1.0f };
		float result_buf[3] = { 0.0f };
		result_buf[0] += (Mat.m[0] * work[0]);
		result_buf[0] += (Mat.m[1] * work[1]);
		result_buf[0] += (Mat.m[2] * work[2]);
		result_buf[0] += (Mat.m[3] * work[3]);

		result_buf[1] += (Mat.m[4] * work[0]);
		result_buf[1] += (Mat.m[5] * work[1]);
		result_buf[1] += (Mat.m[6] * work[2]);
		result_buf[1] += (Mat.m[7] * work[3]);

		result_buf[2] += (Mat.m[8] * work[0]);
		result_buf[2] += (Mat.m[9] * work[1]);
		result_buf[2] += (Mat.m[10] * work[2]);
		result_buf[2] += (Mat.m[11] * work[3]);

		return Vector3D(result_buf[0], result_buf[1], result_buf[2]);
	}
	/*
		入力されたベクトルの角度を求める
		正面方向(Y軸正方向)からどのくらい角度があるのかを計算する
		引数：	vec		:	傾きを求めたいベクトル
		戻り値：ベクトルの傾き(float)
		使い方としては、戻り値の角度をヨー回転行列に代入して、前方ベクトルとの行列積をする
	*/
	inline float CalcVecAngle(const Vector2D& vec) {
		float result = 0.f;
		result = Atan2(vec.y, vec.x);
		// 正面方向との角度を求めるために、π/２を引いた後に反転させる
		result -= PI * 0.5f;
		result = -result;
		return result;
	}
	/*
		前方ベクトルから移動ベクトル間の角度を求める
		引数：	forward	:	前方ベクトル
				move	:	移動ベクトル
				axix	:	前方ベクトルと移動ベクトルの法線ベクトル(戻り値)
							↑クォータニオンで回転させるときにこの値が回転軸になる
		戻り値：角度(ラジアン単位)
	*/
	inline float CalcForwardToMoveAngle(const Vector3D& forward, const Vector3D& move, Vector3D* axis) {
		float forward_long = forward.Long();
		Vector3D target = (forward + move).Normalize();
		target *= forward_long;
		// 回転軸を求める
		*axis = forward ^ target;
		axis->Normalize();

		float forward_longsq = forward.LongSq();
		float move_longsq = move.LongSq();
		// 余弦定理から
		return Acos((2.f * forward_longsq - move_longsq) / (2.f * (forward | target)));
	}
	
}

	

