#pragma once

#include "Vector2D.h"
#include <math.h>

namespace MyLib {
	// 3Dベクトル定義
	class Vector3D {
	public:
		// コンストラクタ
		constexpr Vector3D() noexcept : x(0), y(0), z(0) {}
		explicit constexpr Vector3D(float init) noexcept : x(init), y(init), z(init) {}
		constexpr Vector3D(float init_x, float init_y, float init_z) noexcept : x(init_x), y(init_y), z(init_z) {}
		constexpr Vector3D(const Vector3D& init) noexcept : x(init.x), y(init.y), z(init.z) {}
		constexpr Vector3D(const VECTOR& init) noexcept : x(init.x), y(init.y), z(init.z) {}

		// セット関数
		inline Vector3D SetX(float num) { x = num; return *this; }
		inline Vector3D SetY(float num) { y = num; return *this; }
		inline Vector3D SetZ(float num) { z = num; return *this; }

	public:
		// (0, 0, 0)
		inline static const Vector3D ZEROVec() { return Vector3D(0.f, 0.f, 0.f); }
		// (1, 1, 1)
		inline static const Vector3D OneVec() { return Vector3D(1.f, 1.f, 1.f); }
		// (0, 1, 0)
		inline static const Vector3D UpVec() { return Vector3D(0.f, 1.f, 0.f); }
		// (0, -1, 0)
		inline static const Vector3D DownVec() { return Vector3D(0.f, -1.f, 0.f); }
		// (0, 0, 1)
		inline static const Vector3D ForwardVec() { return Vector3D(0.f, 0.f, 1.f); }
		// (0, 0, -1)
		inline static const Vector3D BackwardVec() { return Vector3D(0.f, 0.f, -1.f); }
		// (1, 0, 0)
		inline static const Vector3D RightVec() { return Vector3D(1.f, 0.f, 0.f); }
		// (-1, 0, 0)
		inline static const Vector3D LeftVec() { return Vector3D(-1.f, 0.f, 0.f); }
		// (1, 0, 0)
		inline static const Vector3D XAxisVec() { return Vector3D(1.f, 0.f, 0.f); }
		// (0, 1, 0)
		inline static const Vector3D YAxisVec() { return Vector3D(0.f, 1.f, 0.f); }
		// (0, 0, 1)
		inline static const Vector3D ZAxisVec() { return Vector3D(0.f, 0.f, 1.f); }

	public:
		// スタティック関数
		inline static Vector3D VGet(float init_x, float init_y, float init_z) { return Vector3D(init_x, init_y, init_z); }
		inline static Vector3D VGet(float init) { return Vector3D(init, init, init); }
		inline static Vector3D VGet(const VECTOR& vec) { return vec; }

		/*
			全ての要素を足し合わせる
			引数： 足し合わせたいベクトル
			戻り値： 足し合わせた結果
		*/
		inline static float AllElementVecAdd(const Vector3D& vec) { return vec.x + vec.y + vec.z; }

	public:
		// オペレーターのオーバーロード

		// 数値設定
		inline Vector3D operator() (float set) { x = set; y = set; z = set; return *this; }
		inline Vector3D operator() (float set_x, float set_y, float set_z) { x = set_x; y = set_y; z = set_z; return *this; }
		inline Vector3D operator() (const Vector3D& vec) { x = vec.x; y = vec.y; z = vec.z; return *this; }
		inline Vector3D operator() (const VECTOR& vec) { x = vec.x; y = vec.y; z = vec.z; return *this; }
		/*
			ベクトルを加算
			引数： 加算するベクトル
			戻り値： 加算したベクトル
		*/
		inline Vector3D operator+(const Vector3D& vec) const { return Vector3D(x + vec.x, y + vec.y, z + vec.z); }
		/*
			ベクトルを加算
			引数： 加算するベクトル
			戻り値： 加算したベクトルのコピー
		*/
		inline Vector3D operator+=(const Vector3D& vec) { return *this = *this + vec; }
		/*
			入力された数値を各要素に加算する
			引数: 加算する数値
			戻り値: 加算したベクトル
		*/
		inline Vector3D operator+(float scale) const { return Vector3D(x + scale, y + scale, z + scale); }
		/*
			入力された数値を各要素に加算する
			引数: 加算する数値
			戻り値: 加算したベクトル
		*/
		inline Vector3D operator+=(float scale) { return *this = *this + scale; }
		/*
			ベクトルの減算
			引数: 減算するベクトル
			戻り値: 減算したベクトル
		*/
		inline Vector3D operator-(const Vector3D& vec) const
		{
			return Vector3D(x - vec.x, y - vec.y, z - vec.z);
		}
		/*
			ベクトルの減算
			引数: 減算するベクトル
			戻り値: 減算したベクトルのコピー
		*/
		inline Vector3D operator-=(const Vector3D& vec) { return *this = *this - vec; }
		/*
			入力された数値を各要素に減算する
			引数: 減算する数値
			戻り値: 減算したベクトル
		*/
		inline Vector3D operator-(float scale) const
		{
			return Vector3D(x - scale, y - scale, z - scale);
		}
		/*
			入力された数値を各要素に減算する
			引数: 減算する数値
			戻り値: 減算したベクトルのコピー
		*/
		inline Vector3D operator-=(float scale) { return *this = *this - scale; }
		/*
			ベクトルのスケーリング
			引数: vec スケーリングするベクトル
			戻り値: スケーリングしたベクトル
		*/
		inline Vector3D operator*(const Vector3D& vec) const
		{
			return Vector3D(x * vec.x, y * vec.y, z * vec.x);
		}
		/*
			ベクトルのスケーリング
			引数: scale スケーリングする値
			戻り値: スケーリングしたベクトル
		*/
		inline Vector3D operator*(float scale) const {
			return Vector3D(x * scale, y * scale, z * scale);
		}
		/*
			ベクトルのスケーリング
			引数: vec スケーリングするベクトル
			戻り値: スケーリングしたベクトルのコピー
		*/
		inline Vector3D operator*=(const Vector3D vec) { return *this = *this * vec; }
		/*
			ベクトルのスケーリング
			引数: scale スケーリングするベクトル
			戻り値: スケーリングしたベクトルのコピー
		*/
		inline Vector3D operator*=(float scale) { return *this = *this * scale; }
		/*
			ベクトルのスケーリング(除算)
			引数: vec 除算する数値(ベクトル)
			戻り値: スケーリングしたベクトル
		*/
		inline Vector3D operator/(const Vector3D& vec)
		{
			return Vector3D(x / vec.x, y / vec.y, z / vec.z);
		}
		/*
			ベクトルのスケーリング(除算)
			引数: scale 除算する数値(ベクトル)
			戻り値: スケーリングしたベクトル
		*/
		inline Vector3D operator/(float scale)
		{
			float calc_scale = 1.f / scale;
			return Vector3D(x * calc_scale, y * calc_scale, z * calc_scale);
		}
		/*
			ベクトルのスケーリング(除算)
			引数: vec 除算する数値(ベクトル)
			戻り値: スケーリングしたベクトルのコピー
		*/
		inline Vector3D operator/=(const Vector3D& vec) { return *this = *this / vec; }
		/*
			ベクトルのスケーリング(除算)
			引数: scale 除算する数値(ベクトル)
			戻り値: スケーリングしたベクトルのコピー
		*/
		inline Vector3D operator/=(float scale) { return *this = *this / scale; }
		/*
			自身と入力ベクトルとの外積
			引数: vec 入力ベクトル
			戻り値: 外積
		*/
		inline Vector3D operator^(const Vector3D& vec) const
		{
			return Vector3D(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
		}
		/*
			自身と入力ベクトルとの外積
			引数: vec 入力ベクトル
			戻り値: 外積のコピー
		*/
		inline Vector3D operator^=(const Vector3D& vec) { return *this = *this ^ vec; }
		/*
			自身と入力ベクトルとの内積
			引数: vec 入力ベクトル
			戻り値: 内積
		*/
		inline float operator|(const Vector3D& vec) const { return x * vec.x + y * vec.y + z * vec.z; }
		/*
			ベクトルの反転
			戻り値： 反転したベクトル
		*/
		inline Vector3D operator-() const { return Vector3D(-x, -y, -z); }

		inline Vector3D operator=(const VECTOR& vec) { return this->operator()(vec.x, vec.y, vec.z); }
		// ベクトルの要素が同じか
		inline bool operator==(const Vector3D& vec) const { return x == vec.x && y == vec.y && z == vec.z; }
		inline bool operator!=(const Vector3D& vec) const { return x != vec.x || y != vec.y || z != vec.z; }

		// ベクトルの比較演算
		inline bool operator>=(const Vector3D& vec) const { return x >= vec.x && y >= vec.y && z >= vec.z; }
		inline bool operator> (const Vector3D& vec) const { return x >  vec.x && y >  vec.y && z >  vec.z; }
		inline bool operator>=(float  value)		const { return x >= value && y >= value && z >= value; }
		inline bool operator> (float  value)		const { return x >  value && y >  value && z >  value; }

		inline bool operator<=(const Vector3D& vec) const { return x <= vec.x && y <= vec.y && z <= vec.z; }
		inline bool operator< (const Vector3D& vec) const { return x <  vec.x && y <  vec.y && z <  vec.z; }
		inline bool operator<=(float  value)		const { return x <= value && y <= value && z <= value; }
		inline bool operator< (float  value)		const { return x <  value && y <  value && z <  value; }

	public:
		// 自身と入力ベクトルとの間でのベクトル生成
		// 引数：	入力ベクトル
		// 戻り値：	生成結果
		inline Vector3D Create(const Vector3D& vec) const { return vec - *this; }

		// ベクトルの正規化
		// 戻り値：	正規化されたベクトル
		Vector3D Normalize() {
			//インライン化していないのはsize変数の命名被りによるエラー回避の為
			float size = this->Long();
			if (size == 0.f || size == 1.f) {
				return *this;
			}
			else {
				float inv_size = Inv(size);
				*this *= inv_size;
				return *this;
			}
		}

		// 入力ベクトルを減算したベクトルの長さを返す
		// 引数：	減算するベクトル
		// 戻り値：	ベクトルの長さ
		inline float Long(const Vector3D& vec = Vector3D::VGet(0.f, 0.f, 0.f)) const {
			return sqrtf(((x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y) + (z - vec.z) * (z - vec.z)));
		}

		// 入力ベクトルを減算したベクトルの長さの２乗を返す
		// 引数：	減算するベクトル
		// 戻り値：	ベクトルの長さの２乗
		inline float LongSq(const Vector3D& vec = Vector3D::VGet(0.0f, 0.0f, 0.0f)) const {
			return (x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y) + (z - vec.z) * (z - vec.z);
		}
		/*
			２つのベクトル同士の外積を計算
			引数：	A	:	1つ目のベクトル
					B	:	2つ目のベクトル
			戻り値：	外積結果ベクトル
		*/
		inline Vector3D CrossProduct(const Vector3D& A, const Vector3D& B) {
			return A ^ B;
		};
		/*
			２つのベクトル同士の内積を計算
			引数：	A	:	1つ目のベクトル
					B	:	2つ目のベクトル
			戻り値：	内積結果ベクトル
		*/
		inline float DotProduct(const Vector3D& A, const Vector3D& B) {
			return A | B;
		}
		/*
			イコール関数
			引数：	V			:	比較したいベクトル
					Tolerance	:	寛容誤差
		*/
		inline bool Equals(const Vector3D& V, float Tolerance = TOLERANCE) {
			return MyLib::Abs(x - V.x) <= Tolerance
				&& MyLib::Abs(y - V.y) <= Tolerance
				&& MyLib::Abs(z - V.z) <= Tolerance;
		}
		/*
			全ての要素がイコールかどうか
			引数：	Tolerance	:	寛容誤差
		*/
		inline bool AllComponentsEqual(float Tolerance = TOLERANCE) {
			return MyLib::Abs(x - y) <= Tolerance
				&& MyLib::Abs(y - z) <= Tolerance
				&& MyLib::Abs(z - x) <= Tolerance;
		}
		/*
			ゼロベクトルかどうか(誤差は無視する)
			引数：	Tolerance	:	寛容誤差
		*/
		inline bool IsNearlyZero(float Tolerance = TOLERANCE) {
			return MyLib::Abs(x) <= Tolerance
				&& MyLib::Abs(y) <= Tolerance
				&& MyLib::Abs(z) <= Tolerance;
		}
		/*
			ゼロベクトルかどうか(誤差は無視しない = 完全にゼロベクトル)
		*/
		inline bool IsZero() {
			return x == 0.f && y == 0.f && z == 0.f;
		}
		/*
			垂直関係にあるベクトルかどうか
		*/
		inline bool IsVertical(const Vector3D& vec) {
			float d = *this | vec;
			return MyLib::Abs(d) < TOLERANCE;		// 誤差範囲内なら垂直と判定
		}
		/*
			平行関係にあるベクトルかどうか
		*/
		inline bool IsParallel(const Vector3D& vec) {
			float d = (*this ^ vec).LongSq();
			return MyLib::Abs(d) < TOLERANCE;		// 誤差範囲内なら平行と判定
		}
		/*
			鋭角関係かどうか
		*/
		inline bool IsSharpAngle(const Vector3D& vec) {
			return (*this | vec) >= 0.f;
		}

		// DXライブラリベクトル構造体へのキャスト演算子
		inline operator VECTOR() const { return VECTOR{ x, y, z }; }

		// Vector2D型へのキャスト演算子
		inline operator Vector2D() const { return Vector2D(x, y); }

	public:
		float x, y, z;
	};

	/*
		ベクトルのスケーリング
		引数：	Scale	:	スケール倍
				V		:	スケール倍したいベクトル
		戻り値：　スケール倍されたベクトル
	*/
	inline Vector3D operator*(float Scale, const Vector3D& V) {
		return V.operator*(Scale);
	}
}

using MyLib::Vector3D;
