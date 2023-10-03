#pragma once

#include "DxLib.h"
#include "Math/Math.h"

namespace MyLib {
	// 2Dベクトル定義
	class Vector2D {
	public:
		// スタティック関数
		// 変数宣言時の初期化関数
		inline static Vector2D VGet(float init_x, float init_y) { return Vector2D(init_x, init_y); }
		inline static Vector2D VGet(float init) { return Vector2D(init, init); }
		inline static Vector2D VGet(const VECTOR& vec) { return Vector2D(vec.x, vec.y); }

		// ゼロベクトル
		inline static Vector2D ZEROVec() { return Vector2D(0.f, 0.f); }

		/*
			全ての要素を足し合わせる
			引数： vec 足し合わせたいベクトル
			戻り値： 結果
		*/
		inline static float AllElementVec2DAdd(const Vector2D& vec) { return (vec.x + vec.y); }

	public:
		// コンストラクタ
		constexpr Vector2D() noexcept :x(0.f), y(0.f) {}
		explicit constexpr Vector2D(float init) noexcept : x(init), y(init) {}
		constexpr Vector2D(float init_x, float init_y) noexcept : x(init_x), y(init_y) {}
		constexpr Vector2D(const Vector2D& V) noexcept : x(V.x), y(V.y) {}
		constexpr Vector2D(const VECTOR& V) noexcept : x(V.x), y(V.y) {}

	public:
		// オペレーターのオーバーロード宣言
		// 数値設定
		inline Vector2D operator()(float set) { x = set; y = set; return *this; }
		inline Vector2D  operator()(float set_x, float set_y) { x = set_x; y = set_y; return *this; }
		inline Vector2D operator()(const Vector2D& V) { x = V.x; y = V.y; return *this; }

		// ベクトルの加算
		// 引数：	加算するベクトル
		// 戻り値：	加算結果
		inline Vector2D operator+(const Vector2D& V) const { return Vector2D(x + V.x, y + V.y); }

		// ベクトルの加算コピー
		// 引数：	加算するベクトル
		// 戻り値：	加算したベクトルのコピー
		inline Vector2D operator+=(const Vector2D& V) { return *this = *this + V; }

		// 入力された数値を各要素それぞれ加算する
		// 引数：	加算する数値
		// 戻り値：	加算したベクトル
		inline Vector2D operator+(float value) const { return Vector2D(x + value, y + value); }

		// 入力された数値を各要素それぞれ加算する
		// 引数：	加算する数値
		// 戻り値：	加算したベクトルのコピー
		inline Vector2D operator+=(float value) { return *this = *this + value; }

		// ベクトルの減算
		// 引数：	減算するベクトル
		// 戻り値：	減算されたベクトル
		inline Vector2D operator-(const Vector2D& V) const { return Vector2D(x - V.x, y - V.y); }

		// ベクトルの減算
		// 引数：	減算するベクトル
		// 戻り値：	減算されたベクトル
		inline Vector2D operator-=(const Vector2D& V) { return Vector2D(x - V.x, y - V.y); }

		// 入力された数値を各要素それぞれ減算する
		// 引数：	減算する数値
		// 戻り値：	減算されたベクトル
		inline Vector2D operator-(float value) const { return Vector2D(x - value, y - value); }

		// 入力された数値を各要素それぞれ減算する
		// 引数：	減算する数値
		// 戻り値：	減算したベクトルのコピー
		inline Vector2D operator-=(float value) { return *this = *this - value; }

		// ベクトルのスケール倍
		// 引数：	スケール倍する量
		// 戻り値：	スケール倍されたベクトル
		inline Vector2D operator*(const Vector2D& scale) const { return this->Scale(scale); }

		// ベクトルのスケール倍
		// 引数：	スケール倍する量
		// 戻り値：	スケール倍されたベクトル
		inline Vector2D operator*(float scale) const { return this->Scale(scale); }

		// ベクトルのスケール倍
		// 引数：	スケール倍する量
		// 戻り値：	スケール倍されたベクトルのコピー
		inline Vector2D operator*=(const Vector2D& scale) { return *this = *this * scale; }

		// ベクトルのスケール倍
		// 引数：	スケール倍する量
		// 戻り値：	スケール倍されたベクトルのコピー
		inline Vector2D operator*=(float scale) { return *this = *this * scale; }

		// ベクトルの除算
		// 引数：	除算する数値(float型)
		// 戻り値：	除算したベクトル
		inline Vector2D operator/(float value) { return Vector2D(x / value, y / value); }

		// ベクトルの除算
		// 引数：	除算する数値(Vector2D型)
		// 戻り値：	除算したベクトル
		inline Vector2D operator/(const Vector2D& scale) { return Vector2D(x / scale.x, y / scale.y); }

		// ベクトルの除算
		// 引数：	除算する数値(float型)
		// 戻り値：	除算したベクトルのコピー
		inline Vector2D operator/=(float value) { return *this = *this / value; }

		// ベクトルの除算
		// 引数：	除算する数値(Vector2D型)
		// 戻り値：	除算したベクトルのコピー
		inline Vector2D operator/=(const Vector2D& scale) { return *this = *this / scale; }

		// 自身と入力ベクトルとの外積
		// 引数：	入力ベクトル
		// 戻り値：	外積結果
		inline float operator^(const Vector2D& V) { return this->Cross(V); }

		// 自身と入力ベクトルとの内積
		// 引数：	入力ベクトル
		// 戻り値：	内積結果
		inline float operator|(const Vector2D& V) { return this->Dot(V); }

		// ベクトルの反転
		// 戻り値：	反転したベクトル
		inline Vector2D operator-() const { return Vector2D(-x, -y); }

		// ベクトル代入
		// 戻り値：	代入結果
		inline Vector2D operator=(const VECTOR& vec) { x = vec.x; y = vec.y; return *this; }

		// ベクトルの要素が同一か
		inline bool operator==(const Vector2D& vec) const { return (x == vec.x && y == vec.y); }
		inline bool operator!=(const Vector2D& vec) const { return !(*this == vec); }

		//DXライブラリベクトル構造体へのキャスト演算子
		inline operator VECTOR() const { return VECTOR{ (float)x, (float)y, 0.f }; }

	public:
		// ベクトルのスケール倍
		// 引数：　	スケール倍(float型)
		// 戻り値：	スケール倍されたベクトル
		inline Vector2D Scale(float scale) const { return Vector2D(x * scale, y * scale); }

		// ベクトルのスケール倍
		// 引数：　	スケール倍(Vector2D型)
		// 戻り値：	スケール倍されたベクトル
		inline Vector2D Scale(const Vector2D& scale) const { return Vector2D(x * scale.x, y * scale.y); }

		// 自身と入力ベクトルとの外積
		// 引数：	入力ベクトル
		// 戻り値：	外積結果
		inline float Cross(const Vector2D& V) const { return x * V.y - y * V.x; }

		// 自身と入力ベクトルとの内積
		// 引数：	入力ベクトル
		// 戻り値：	内積結果
		inline float Dot(const Vector2D& V) const { return x * V.x + y * V.y; }

		// 自身と入力ベクトルとの間でのベクトル生成
		// 引数：	入力ベクトル
		// 戻り値：	生成結果
		inline Vector2D Create(const Vector2D& V) const { return Vector2D(V.x - x, V.y - y); }

		// 入力ベクトルの原点からの長さ
		// 引数：	原点
		// 戻り値：	ベクトルの長さ
		inline float Long(const Vector2D& V = Vector2D::VGet(0.f, 0.f)) const { return sqrtf((x - V.x) * (x - V.x) + (y - V.y) * (y - V.y)); }

		// ベクトルの長さ(2乗)
		inline float LongSq(const Vector2D& V = Vector2D::VGet(0.f, 0.f)) const { return Square(x - V.x) + Square(y - V.y); }

		// ベクトルの正規化
		// 戻り値：	正規化されたベクトル
		Vector2D Normalize() {
			//インライン化していないのはsize変数の命名被りによるエラー回避の為
			float size = this->Long();
			if (size == 0.0f || size == 1.0f) { return *this; }
			else {
				float inv_size = Inv(size);
				*this *= inv_size;
				return *this;
			}
		}
		/*
			ゼロベクトルかどうか(誤差は無視する)
			引数：	Tolerance	:	寛容誤差
		*/
		inline bool IsNearlyZero(float Tolerance = TOLERANCE) {
			return MyLib::Abs(x) <= Tolerance
				&& MyLib::Abs(y) <= Tolerance;
		}
		/*
			ゼロベクトルかどうか(誤差は無視しない = 完全にゼロベクトル)
		*/
		inline bool IsZero() {
			return x == 0.f && y == 0.f;
		}

	public:
		float x, y;
	};

	/*
		ベクトルのスケーリング
		引数：	Scale	:	スケール倍
				V		:	スケーリングしたいベクトル
		戻り値：演算結果
	*/
	inline Vector2D operator*(float Scale, const Vector2D& V) {
		return V.operator*(Scale);
	}
}

using MyLib::Vector2D;
