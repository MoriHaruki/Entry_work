#pragma once

#include "Vector2D.h"
#include <math.h>

namespace MyLib {
	// 3D�x�N�g����`
	class Vector3D {
	public:
		// �R���X�g���N�^
		constexpr Vector3D() noexcept : x(0), y(0), z(0) {}
		explicit constexpr Vector3D(float init) noexcept : x(init), y(init), z(init) {}
		constexpr Vector3D(float init_x, float init_y, float init_z) noexcept : x(init_x), y(init_y), z(init_z) {}
		constexpr Vector3D(const Vector3D& init) noexcept : x(init.x), y(init.y), z(init.z) {}
		constexpr Vector3D(const VECTOR& init) noexcept : x(init.x), y(init.y), z(init.z) {}

		// �Z�b�g�֐�
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
		// �X�^�e�B�b�N�֐�
		inline static Vector3D VGet(float init_x, float init_y, float init_z) { return Vector3D(init_x, init_y, init_z); }
		inline static Vector3D VGet(float init) { return Vector3D(init, init, init); }
		inline static Vector3D VGet(const VECTOR& vec) { return vec; }

		/*
			�S�Ă̗v�f�𑫂����킹��
			�����F �������킹�����x�N�g��
			�߂�l�F �������킹������
		*/
		inline static float AllElementVecAdd(const Vector3D& vec) { return vec.x + vec.y + vec.z; }

	public:
		// �I�y���[�^�[�̃I�[�o�[���[�h

		// ���l�ݒ�
		inline Vector3D operator() (float set) { x = set; y = set; z = set; return *this; }
		inline Vector3D operator() (float set_x, float set_y, float set_z) { x = set_x; y = set_y; z = set_z; return *this; }
		inline Vector3D operator() (const Vector3D& vec) { x = vec.x; y = vec.y; z = vec.z; return *this; }
		inline Vector3D operator() (const VECTOR& vec) { x = vec.x; y = vec.y; z = vec.z; return *this; }
		/*
			�x�N�g�������Z
			�����F ���Z����x�N�g��
			�߂�l�F ���Z�����x�N�g��
		*/
		inline Vector3D operator+(const Vector3D& vec) const { return Vector3D(x + vec.x, y + vec.y, z + vec.z); }
		/*
			�x�N�g�������Z
			�����F ���Z����x�N�g��
			�߂�l�F ���Z�����x�N�g���̃R�s�[
		*/
		inline Vector3D operator+=(const Vector3D& vec) { return *this = *this + vec; }
		/*
			���͂��ꂽ���l���e�v�f�ɉ��Z����
			����: ���Z���鐔�l
			�߂�l: ���Z�����x�N�g��
		*/
		inline Vector3D operator+(float scale) const { return Vector3D(x + scale, y + scale, z + scale); }
		/*
			���͂��ꂽ���l���e�v�f�ɉ��Z����
			����: ���Z���鐔�l
			�߂�l: ���Z�����x�N�g��
		*/
		inline Vector3D operator+=(float scale) { return *this = *this + scale; }
		/*
			�x�N�g���̌��Z
			����: ���Z����x�N�g��
			�߂�l: ���Z�����x�N�g��
		*/
		inline Vector3D operator-(const Vector3D& vec) const
		{
			return Vector3D(x - vec.x, y - vec.y, z - vec.z);
		}
		/*
			�x�N�g���̌��Z
			����: ���Z����x�N�g��
			�߂�l: ���Z�����x�N�g���̃R�s�[
		*/
		inline Vector3D operator-=(const Vector3D& vec) { return *this = *this - vec; }
		/*
			���͂��ꂽ���l���e�v�f�Ɍ��Z����
			����: ���Z���鐔�l
			�߂�l: ���Z�����x�N�g��
		*/
		inline Vector3D operator-(float scale) const
		{
			return Vector3D(x - scale, y - scale, z - scale);
		}
		/*
			���͂��ꂽ���l���e�v�f�Ɍ��Z����
			����: ���Z���鐔�l
			�߂�l: ���Z�����x�N�g���̃R�s�[
		*/
		inline Vector3D operator-=(float scale) { return *this = *this - scale; }
		/*
			�x�N�g���̃X�P�[�����O
			����: vec �X�P�[�����O����x�N�g��
			�߂�l: �X�P�[�����O�����x�N�g��
		*/
		inline Vector3D operator*(const Vector3D& vec) const
		{
			return Vector3D(x * vec.x, y * vec.y, z * vec.x);
		}
		/*
			�x�N�g���̃X�P�[�����O
			����: scale �X�P�[�����O����l
			�߂�l: �X�P�[�����O�����x�N�g��
		*/
		inline Vector3D operator*(float scale) const {
			return Vector3D(x * scale, y * scale, z * scale);
		}
		/*
			�x�N�g���̃X�P�[�����O
			����: vec �X�P�[�����O����x�N�g��
			�߂�l: �X�P�[�����O�����x�N�g���̃R�s�[
		*/
		inline Vector3D operator*=(const Vector3D vec) { return *this = *this * vec; }
		/*
			�x�N�g���̃X�P�[�����O
			����: scale �X�P�[�����O����x�N�g��
			�߂�l: �X�P�[�����O�����x�N�g���̃R�s�[
		*/
		inline Vector3D operator*=(float scale) { return *this = *this * scale; }
		/*
			�x�N�g���̃X�P�[�����O(���Z)
			����: vec ���Z���鐔�l(�x�N�g��)
			�߂�l: �X�P�[�����O�����x�N�g��
		*/
		inline Vector3D operator/(const Vector3D& vec)
		{
			return Vector3D(x / vec.x, y / vec.y, z / vec.z);
		}
		/*
			�x�N�g���̃X�P�[�����O(���Z)
			����: scale ���Z���鐔�l(�x�N�g��)
			�߂�l: �X�P�[�����O�����x�N�g��
		*/
		inline Vector3D operator/(float scale)
		{
			float calc_scale = 1.f / scale;
			return Vector3D(x * calc_scale, y * calc_scale, z * calc_scale);
		}
		/*
			�x�N�g���̃X�P�[�����O(���Z)
			����: vec ���Z���鐔�l(�x�N�g��)
			�߂�l: �X�P�[�����O�����x�N�g���̃R�s�[
		*/
		inline Vector3D operator/=(const Vector3D& vec) { return *this = *this / vec; }
		/*
			�x�N�g���̃X�P�[�����O(���Z)
			����: scale ���Z���鐔�l(�x�N�g��)
			�߂�l: �X�P�[�����O�����x�N�g���̃R�s�[
		*/
		inline Vector3D operator/=(float scale) { return *this = *this / scale; }
		/*
			���g�Ɠ��̓x�N�g���Ƃ̊O��
			����: vec ���̓x�N�g��
			�߂�l: �O��
		*/
		inline Vector3D operator^(const Vector3D& vec) const
		{
			return Vector3D(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
		}
		/*
			���g�Ɠ��̓x�N�g���Ƃ̊O��
			����: vec ���̓x�N�g��
			�߂�l: �O�ς̃R�s�[
		*/
		inline Vector3D operator^=(const Vector3D& vec) { return *this = *this ^ vec; }
		/*
			���g�Ɠ��̓x�N�g���Ƃ̓���
			����: vec ���̓x�N�g��
			�߂�l: ����
		*/
		inline float operator|(const Vector3D& vec) const { return x * vec.x + y * vec.y + z * vec.z; }
		/*
			�x�N�g���̔��]
			�߂�l�F ���]�����x�N�g��
		*/
		inline Vector3D operator-() const { return Vector3D(-x, -y, -z); }

		inline Vector3D operator=(const VECTOR& vec) { return this->operator()(vec.x, vec.y, vec.z); }
		// �x�N�g���̗v�f��������
		inline bool operator==(const Vector3D& vec) const { return x == vec.x && y == vec.y && z == vec.z; }
		inline bool operator!=(const Vector3D& vec) const { return x != vec.x || y != vec.y || z != vec.z; }

		// �x�N�g���̔�r���Z
		inline bool operator>=(const Vector3D& vec) const { return x >= vec.x && y >= vec.y && z >= vec.z; }
		inline bool operator> (const Vector3D& vec) const { return x >  vec.x && y >  vec.y && z >  vec.z; }
		inline bool operator>=(float  value)		const { return x >= value && y >= value && z >= value; }
		inline bool operator> (float  value)		const { return x >  value && y >  value && z >  value; }

		inline bool operator<=(const Vector3D& vec) const { return x <= vec.x && y <= vec.y && z <= vec.z; }
		inline bool operator< (const Vector3D& vec) const { return x <  vec.x && y <  vec.y && z <  vec.z; }
		inline bool operator<=(float  value)		const { return x <= value && y <= value && z <= value; }
		inline bool operator< (float  value)		const { return x <  value && y <  value && z <  value; }

	public:
		// ���g�Ɠ��̓x�N�g���Ƃ̊Ԃł̃x�N�g������
		// �����F	���̓x�N�g��
		// �߂�l�F	��������
		inline Vector3D Create(const Vector3D& vec) const { return vec - *this; }

		// �x�N�g���̐��K��
		// �߂�l�F	���K�����ꂽ�x�N�g��
		Vector3D Normalize() {
			//�C�����C�������Ă��Ȃ��̂�size�ϐ��̖������ɂ��G���[����̈�
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

		// ���̓x�N�g�������Z�����x�N�g���̒�����Ԃ�
		// �����F	���Z����x�N�g��
		// �߂�l�F	�x�N�g���̒���
		inline float Long(const Vector3D& vec = Vector3D::VGet(0.f, 0.f, 0.f)) const {
			return sqrtf(((x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y) + (z - vec.z) * (z - vec.z)));
		}

		// ���̓x�N�g�������Z�����x�N�g���̒����̂Q���Ԃ�
		// �����F	���Z����x�N�g��
		// �߂�l�F	�x�N�g���̒����̂Q��
		inline float LongSq(const Vector3D& vec = Vector3D::VGet(0.0f, 0.0f, 0.0f)) const {
			return (x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y) + (z - vec.z) * (z - vec.z);
		}
		/*
			�Q�̃x�N�g�����m�̊O�ς��v�Z
			�����F	A	:	1�ڂ̃x�N�g��
					B	:	2�ڂ̃x�N�g��
			�߂�l�F	�O�ό��ʃx�N�g��
		*/
		inline Vector3D CrossProduct(const Vector3D& A, const Vector3D& B) {
			return A ^ B;
		};
		/*
			�Q�̃x�N�g�����m�̓��ς��v�Z
			�����F	A	:	1�ڂ̃x�N�g��
					B	:	2�ڂ̃x�N�g��
			�߂�l�F	���ό��ʃx�N�g��
		*/
		inline float DotProduct(const Vector3D& A, const Vector3D& B) {
			return A | B;
		}
		/*
			�C�R�[���֐�
			�����F	V			:	��r�������x�N�g��
					Tolerance	:	���e�덷
		*/
		inline bool Equals(const Vector3D& V, float Tolerance = TOLERANCE) {
			return MyLib::Abs(x - V.x) <= Tolerance
				&& MyLib::Abs(y - V.y) <= Tolerance
				&& MyLib::Abs(z - V.z) <= Tolerance;
		}
		/*
			�S�Ă̗v�f���C�R�[�����ǂ���
			�����F	Tolerance	:	���e�덷
		*/
		inline bool AllComponentsEqual(float Tolerance = TOLERANCE) {
			return MyLib::Abs(x - y) <= Tolerance
				&& MyLib::Abs(y - z) <= Tolerance
				&& MyLib::Abs(z - x) <= Tolerance;
		}
		/*
			�[���x�N�g�����ǂ���(�덷�͖�������)
			�����F	Tolerance	:	���e�덷
		*/
		inline bool IsNearlyZero(float Tolerance = TOLERANCE) {
			return MyLib::Abs(x) <= Tolerance
				&& MyLib::Abs(y) <= Tolerance
				&& MyLib::Abs(z) <= Tolerance;
		}
		/*
			�[���x�N�g�����ǂ���(�덷�͖������Ȃ� = ���S�Ƀ[���x�N�g��)
		*/
		inline bool IsZero() {
			return x == 0.f && y == 0.f && z == 0.f;
		}
		/*
			�����֌W�ɂ���x�N�g�����ǂ���
		*/
		inline bool IsVertical(const Vector3D& vec) {
			float d = *this | vec;
			return MyLib::Abs(d) < TOLERANCE;		// �덷�͈͓��Ȃ琂���Ɣ���
		}
		/*
			���s�֌W�ɂ���x�N�g�����ǂ���
		*/
		inline bool IsParallel(const Vector3D& vec) {
			float d = (*this ^ vec).LongSq();
			return MyLib::Abs(d) < TOLERANCE;		// �덷�͈͓��Ȃ畽�s�Ɣ���
		}
		/*
			�s�p�֌W���ǂ���
		*/
		inline bool IsSharpAngle(const Vector3D& vec) {
			return (*this | vec) >= 0.f;
		}

		// DX���C�u�����x�N�g���\���̂ւ̃L���X�g���Z�q
		inline operator VECTOR() const { return VECTOR{ x, y, z }; }

		// Vector2D�^�ւ̃L���X�g���Z�q
		inline operator Vector2D() const { return Vector2D(x, y); }

	public:
		float x, y, z;
	};

	/*
		�x�N�g���̃X�P�[�����O
		�����F	Scale	:	�X�P�[���{
				V		:	�X�P�[���{�������x�N�g��
		�߂�l�F�@�X�P�[���{���ꂽ�x�N�g��
	*/
	inline Vector3D operator*(float Scale, const Vector3D& V) {
		return V.operator*(Scale);
	}
}

using MyLib::Vector3D;
