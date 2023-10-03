#pragma once

#include "DxLib.h"
#include "Math/Math.h"

namespace MyLib {
	// 2D�x�N�g����`
	class Vector2D {
	public:
		// �X�^�e�B�b�N�֐�
		// �ϐ��錾���̏������֐�
		inline static Vector2D VGet(float init_x, float init_y) { return Vector2D(init_x, init_y); }
		inline static Vector2D VGet(float init) { return Vector2D(init, init); }
		inline static Vector2D VGet(const VECTOR& vec) { return Vector2D(vec.x, vec.y); }

		// �[���x�N�g��
		inline static Vector2D ZEROVec() { return Vector2D(0.f, 0.f); }

		/*
			�S�Ă̗v�f�𑫂����킹��
			�����F vec �������킹�����x�N�g��
			�߂�l�F ����
		*/
		inline static float AllElementVec2DAdd(const Vector2D& vec) { return (vec.x + vec.y); }

	public:
		// �R���X�g���N�^
		constexpr Vector2D() noexcept :x(0.f), y(0.f) {}
		explicit constexpr Vector2D(float init) noexcept : x(init), y(init) {}
		constexpr Vector2D(float init_x, float init_y) noexcept : x(init_x), y(init_y) {}
		constexpr Vector2D(const Vector2D& V) noexcept : x(V.x), y(V.y) {}
		constexpr Vector2D(const VECTOR& V) noexcept : x(V.x), y(V.y) {}

	public:
		// �I�y���[�^�[�̃I�[�o�[���[�h�錾
		// ���l�ݒ�
		inline Vector2D operator()(float set) { x = set; y = set; return *this; }
		inline Vector2D  operator()(float set_x, float set_y) { x = set_x; y = set_y; return *this; }
		inline Vector2D operator()(const Vector2D& V) { x = V.x; y = V.y; return *this; }

		// �x�N�g���̉��Z
		// �����F	���Z����x�N�g��
		// �߂�l�F	���Z����
		inline Vector2D operator+(const Vector2D& V) const { return Vector2D(x + V.x, y + V.y); }

		// �x�N�g���̉��Z�R�s�[
		// �����F	���Z����x�N�g��
		// �߂�l�F	���Z�����x�N�g���̃R�s�[
		inline Vector2D operator+=(const Vector2D& V) { return *this = *this + V; }

		// ���͂��ꂽ���l���e�v�f���ꂼ����Z����
		// �����F	���Z���鐔�l
		// �߂�l�F	���Z�����x�N�g��
		inline Vector2D operator+(float value) const { return Vector2D(x + value, y + value); }

		// ���͂��ꂽ���l���e�v�f���ꂼ����Z����
		// �����F	���Z���鐔�l
		// �߂�l�F	���Z�����x�N�g���̃R�s�[
		inline Vector2D operator+=(float value) { return *this = *this + value; }

		// �x�N�g���̌��Z
		// �����F	���Z����x�N�g��
		// �߂�l�F	���Z���ꂽ�x�N�g��
		inline Vector2D operator-(const Vector2D& V) const { return Vector2D(x - V.x, y - V.y); }

		// �x�N�g���̌��Z
		// �����F	���Z����x�N�g��
		// �߂�l�F	���Z���ꂽ�x�N�g��
		inline Vector2D operator-=(const Vector2D& V) { return Vector2D(x - V.x, y - V.y); }

		// ���͂��ꂽ���l���e�v�f���ꂼ�ꌸ�Z����
		// �����F	���Z���鐔�l
		// �߂�l�F	���Z���ꂽ�x�N�g��
		inline Vector2D operator-(float value) const { return Vector2D(x - value, y - value); }

		// ���͂��ꂽ���l���e�v�f���ꂼ�ꌸ�Z����
		// �����F	���Z���鐔�l
		// �߂�l�F	���Z�����x�N�g���̃R�s�[
		inline Vector2D operator-=(float value) { return *this = *this - value; }

		// �x�N�g���̃X�P�[���{
		// �����F	�X�P�[���{�����
		// �߂�l�F	�X�P�[���{���ꂽ�x�N�g��
		inline Vector2D operator*(const Vector2D& scale) const { return this->Scale(scale); }

		// �x�N�g���̃X�P�[���{
		// �����F	�X�P�[���{�����
		// �߂�l�F	�X�P�[���{���ꂽ�x�N�g��
		inline Vector2D operator*(float scale) const { return this->Scale(scale); }

		// �x�N�g���̃X�P�[���{
		// �����F	�X�P�[���{�����
		// �߂�l�F	�X�P�[���{���ꂽ�x�N�g���̃R�s�[
		inline Vector2D operator*=(const Vector2D& scale) { return *this = *this * scale; }

		// �x�N�g���̃X�P�[���{
		// �����F	�X�P�[���{�����
		// �߂�l�F	�X�P�[���{���ꂽ�x�N�g���̃R�s�[
		inline Vector2D operator*=(float scale) { return *this = *this * scale; }

		// �x�N�g���̏��Z
		// �����F	���Z���鐔�l(float�^)
		// �߂�l�F	���Z�����x�N�g��
		inline Vector2D operator/(float value) { return Vector2D(x / value, y / value); }

		// �x�N�g���̏��Z
		// �����F	���Z���鐔�l(Vector2D�^)
		// �߂�l�F	���Z�����x�N�g��
		inline Vector2D operator/(const Vector2D& scale) { return Vector2D(x / scale.x, y / scale.y); }

		// �x�N�g���̏��Z
		// �����F	���Z���鐔�l(float�^)
		// �߂�l�F	���Z�����x�N�g���̃R�s�[
		inline Vector2D operator/=(float value) { return *this = *this / value; }

		// �x�N�g���̏��Z
		// �����F	���Z���鐔�l(Vector2D�^)
		// �߂�l�F	���Z�����x�N�g���̃R�s�[
		inline Vector2D operator/=(const Vector2D& scale) { return *this = *this / scale; }

		// ���g�Ɠ��̓x�N�g���Ƃ̊O��
		// �����F	���̓x�N�g��
		// �߂�l�F	�O�ό���
		inline float operator^(const Vector2D& V) { return this->Cross(V); }

		// ���g�Ɠ��̓x�N�g���Ƃ̓���
		// �����F	���̓x�N�g��
		// �߂�l�F	���ό���
		inline float operator|(const Vector2D& V) { return this->Dot(V); }

		// �x�N�g���̔��]
		// �߂�l�F	���]�����x�N�g��
		inline Vector2D operator-() const { return Vector2D(-x, -y); }

		// �x�N�g�����
		// �߂�l�F	�������
		inline Vector2D operator=(const VECTOR& vec) { x = vec.x; y = vec.y; return *this; }

		// �x�N�g���̗v�f�����ꂩ
		inline bool operator==(const Vector2D& vec) const { return (x == vec.x && y == vec.y); }
		inline bool operator!=(const Vector2D& vec) const { return !(*this == vec); }

		//DX���C�u�����x�N�g���\���̂ւ̃L���X�g���Z�q
		inline operator VECTOR() const { return VECTOR{ (float)x, (float)y, 0.f }; }

	public:
		// �x�N�g���̃X�P�[���{
		// �����F�@	�X�P�[���{(float�^)
		// �߂�l�F	�X�P�[���{���ꂽ�x�N�g��
		inline Vector2D Scale(float scale) const { return Vector2D(x * scale, y * scale); }

		// �x�N�g���̃X�P�[���{
		// �����F�@	�X�P�[���{(Vector2D�^)
		// �߂�l�F	�X�P�[���{���ꂽ�x�N�g��
		inline Vector2D Scale(const Vector2D& scale) const { return Vector2D(x * scale.x, y * scale.y); }

		// ���g�Ɠ��̓x�N�g���Ƃ̊O��
		// �����F	���̓x�N�g��
		// �߂�l�F	�O�ό���
		inline float Cross(const Vector2D& V) const { return x * V.y - y * V.x; }

		// ���g�Ɠ��̓x�N�g���Ƃ̓���
		// �����F	���̓x�N�g��
		// �߂�l�F	���ό���
		inline float Dot(const Vector2D& V) const { return x * V.x + y * V.y; }

		// ���g�Ɠ��̓x�N�g���Ƃ̊Ԃł̃x�N�g������
		// �����F	���̓x�N�g��
		// �߂�l�F	��������
		inline Vector2D Create(const Vector2D& V) const { return Vector2D(V.x - x, V.y - y); }

		// ���̓x�N�g���̌��_����̒���
		// �����F	���_
		// �߂�l�F	�x�N�g���̒���
		inline float Long(const Vector2D& V = Vector2D::VGet(0.f, 0.f)) const { return sqrtf((x - V.x) * (x - V.x) + (y - V.y) * (y - V.y)); }

		// �x�N�g���̒���(2��)
		inline float LongSq(const Vector2D& V = Vector2D::VGet(0.f, 0.f)) const { return Square(x - V.x) + Square(y - V.y); }

		// �x�N�g���̐��K��
		// �߂�l�F	���K�����ꂽ�x�N�g��
		Vector2D Normalize() {
			//�C�����C�������Ă��Ȃ��̂�size�ϐ��̖������ɂ��G���[����̈�
			float size = this->Long();
			if (size == 0.0f || size == 1.0f) { return *this; }
			else {
				float inv_size = Inv(size);
				*this *= inv_size;
				return *this;
			}
		}
		/*
			�[���x�N�g�����ǂ���(�덷�͖�������)
			�����F	Tolerance	:	���e�덷
		*/
		inline bool IsNearlyZero(float Tolerance = TOLERANCE) {
			return MyLib::Abs(x) <= Tolerance
				&& MyLib::Abs(y) <= Tolerance;
		}
		/*
			�[���x�N�g�����ǂ���(�덷�͖������Ȃ� = ���S�Ƀ[���x�N�g��)
		*/
		inline bool IsZero() {
			return x == 0.f && y == 0.f;
		}

	public:
		float x, y;
	};

	/*
		�x�N�g���̃X�P�[�����O
		�����F	Scale	:	�X�P�[���{
				V		:	�X�P�[�����O�������x�N�g��
		�߂�l�F���Z����
	*/
	inline Vector2D operator*(float Scale, const Vector2D& V) {
		return V.operator*(Scale);
	}
}

using MyLib::Vector2D;
