#pragma once

#include "DxLib.h"
#include <math.h>
#include"../Vector/Vector3D.h"

/*
	for���[�v�ɂ��Ă��Ȃ��̂́A�����ł��������y�����邽��
	�s��̉��Z�̓Q�[�����ł��Ȃ�g���̂ŁA�����͏����ł��y���ق�������
*/

namespace MyLib {
	// �s���`
	class Matrix {
	public:
		/*
			�f�t�H���g�R���X�g���N�^
		*/
		Matrix() 
			: m() 
		{}
		/*
			�����̒l�ɏ���������
			��{�I��0���������K�v�Ȏ��Ɏg�p����
		*/
		Matrix(float init) {
			m[0]  = init; m[1]  = init; m[2]  = init; m[3]  = init;
			m[4]  = init; m[5]  = init; m[6]  = init; m[7]  = init;
			m[8]  = init; m[9]  = init; m[10] = init; m[11] = init;
			m[12] = init; m[13] = init; m[14] = init; m[15] = init;
		}

	public: // �X�^�e�B�b�N�֐�
		/*
			�P�ʍs����擾
		*/
		static Matrix GetIdentityMat() {
			Matrix IdentityMat;
			IdentityMat.m[0]  = 1; IdentityMat.m[1]  = 0; IdentityMat.m[2]  = 0; IdentityMat.m[3]  = 0;
			IdentityMat.m[4]  = 0; IdentityMat.m[5]  = 1; IdentityMat.m[6]  = 0; IdentityMat.m[7]  = 0;
			IdentityMat.m[8]  = 0; IdentityMat.m[9]  = 0; IdentityMat.m[10] = 1; IdentityMat.m[11] = 0;
			IdentityMat.m[12] = 0; IdentityMat.m[13] = 0; IdentityMat.m[14] = 0; IdentityMat.m[15] = 1;
			return IdentityMat;
		}
		/*
			���s�ړ��s����擾
			�����Ftranslate ���s�ړ�����x�N�g��
			�߂�l�F ���s�ړ��s��
		*/
		static Matrix GetTranslateMat(const Vector3D& translate) {
			Matrix translateMat = GetIdentityMat();
			translateMat.m[3] = translate.x; translateMat.m[7] = translate.y; translateMat.m[11] = translate.z;
			return translateMat;
		}
		/*
			�g�k�s����擾
			�����F scale �g�k�l�̃x�N�g��
			�߂�l�F �g�k�s��
		*/
		static Matrix GetScaleMat(const Vector3D& scale) {
			Matrix scaleMat = GetIdentityMat();
			scaleMat.m[0] = scale.x; scaleMat.m[5] = scale.y; scaleMat.m[10] = scale.z;
			return scaleMat;
		}
		/*
			X����]�s����擾
			�����F rotation ��]�l
			�߂�l�F X����]�s��
		*/
		static Matrix GetPitchMat(float rotation) {
			Matrix pitchMat = GetIdentityMat();
			pitchMat.m[5] = cosf(rotation); pitchMat.m[6] = -sinf(rotation); pitchMat.m[9] = sinf(rotation); pitchMat.m[10] = cosf(rotation);
			return pitchMat;
		}
		/*
			Y����]�s����擾
			�����F rotation ��]�l
			�߂�l�F Y����]�s��
		*/
		static Matrix GetYawMat(float rotation) {
			Matrix yawMat = GetIdentityMat();
			yawMat.m[0] = cosf(rotation); yawMat.m[2] = sinf(rotation); yawMat.m[8] = -sinf(rotation); yawMat.m[10] = cosf(rotation);
			return yawMat;
		}
		/*
			Z����]�s����擾
			�����F rotation ��]�l
			�߂�l�F Z����]�s��
		*/
		static Matrix GetRollMat(float rotation) {
			Matrix rollMat = GetIdentityMat();
			rollMat.m[0] = cosf(rotation); rollMat.m[1] = -sinf(rotation); rollMat.m[4] = sinf(rotation); rollMat.m[5] = cosf(rotation);
			return rollMat;
		}
		/*
			��]�s����擾
			�����F rotation ��]�x�N�g��
			�߂�l�F ��]�s��
		*/
		static Matrix GetRotationMat(const Vector3D& rotation) {
			return GetRollMat(rotation.z) * GetYawMat(rotation.y) * GetPitchMat(rotation.x) * GetIdentityMat();
		}

	public:
		// �]�u
		Matrix MatTranspose() {
			Matrix result;
			result.m[0]  = m[0]; result.m[1]  = m[4]; result.m[2]  =  m[8]; result.m[3]  = m[12];
			result.m[4]  = m[1]; result.m[5]  = m[5]; result.m[6]  =  m[9]; result.m[7]  = m[13];
			result.m[8]  = m[2]; result.m[9]  = m[6]; result.m[10] = m[10]; result.m[11] = m[14];
			result.m[12] = m[3]; result.m[13] = m[7]; result.m[14] = m[11]; result.m[15] = m[15];
			return result;
		}

	public: // �I�y���[�^�̃I�[�o�[���[�h
		/*
			�s��̉��Z
			�����F mat ���Z����s��
			�߂�l�F ���Z�����s��
		*/
		Matrix operator+(const Matrix& mat) {
			Matrix add(0.f);
			add.m[0]  = m[0]  + mat.m[0];  add.m[1]  = m[1]  + mat.m[1];  add.m[2]  = m[2]  + mat.m[2];  add.m[3]  = m[3]  + mat.m[3];
			add.m[4]  = m[4]  + mat.m[4];  add.m[5]  = m[5]  + mat.m[5];  add.m[6]  = m[6]  + mat.m[6];  add.m[7]  = m[7]  + mat.m[7];
			add.m[8]  = m[8]  + mat.m[8];  add.m[9]  = m[9]  + mat.m[9];  add.m[10] = m[10] + mat.m[10]; add.m[11] = m[11] + mat.m[11];
			add.m[12] = m[12] + mat.m[12]; add.m[13] = m[13] + mat.m[13]; add.m[14] = m[14] + mat.m[14]; add.m[15] = m[15] + mat.m[15];
			return add;
		}
		/*
			�s��̉��Z
			�����F mat ���Z����s��
			�߂�l�F ���Z�����s��̃R�s�[
		*/
		Matrix operator+=(const Matrix& mat) { return *this = *this + mat; }
		/*
			�s��̌��Z
			�����F mat ���Z����s��
			�߂�l�F ���Z�����s��
		*/
		Matrix operator-(const Matrix& mat) {
			Matrix sub(0.f);
			sub.m[0]  = m[0]  - mat.m[0];  sub.m[1]  = m[1]  - mat.m[1];  sub.m[2]  = m[2]  - mat.m[2];  sub.m[3]  = m[3]  - mat.m[3];
			sub.m[4]  = m[4]  - mat.m[4];  sub.m[5]  = m[5]  - mat.m[5];  sub.m[6]  = m[6]  - mat.m[6];  sub.m[7]  = m[7]  - mat.m[7];
			sub.m[8]  = m[8]  - mat.m[8];  sub.m[9]  = m[9]  - mat.m[9];  sub.m[10] = m[10] - mat.m[10]; sub.m[11] = m[11] - mat.m[11];
			sub.m[12] = m[12] - mat.m[12]; sub.m[13] = m[13] - mat.m[13]; sub.m[14] = m[14] - mat.m[14]; sub.m[15] = m[15] - mat.m[15];
			return sub;
		}
		/*
			�s��̌��Z
			�����F mat ���Z����s��
			�߂�l�F ���Z�����s��̃R�s�[
		*/
		Matrix operator-=(const Matrix& mat) { return *this = *this - mat; }
		/*
			�s��̃X�J���[�{
			�����F scale �X�J���[�l
			�߂�l�F �X�J���[�{�����s��
		*/
		Matrix operator*(float scale) {
			Matrix scaleMat(0.f);
			scaleMat.m[0]  = m[0]  * scale; scaleMat.m[1]  = m[1]  * scale; scaleMat.m[2]  = m[2]  * scale; scaleMat.m[3]  = m[3]  * scale;
			scaleMat.m[4]  = m[4]  * scale; scaleMat.m[5]  = m[5]  * scale; scaleMat.m[6]  = m[6]  * scale; scaleMat.m[7]  = m[7]  * scale;
			scaleMat.m[8]  = m[8]  * scale; scaleMat.m[9]  = m[9]  * scale; scaleMat.m[10] = m[10] * scale; scaleMat.m[11] = m[11] * scale;
			scaleMat.m[12] = m[12] * scale; scaleMat.m[13] = m[13] * scale; scaleMat.m[14] = m[14] * scale; scaleMat.m[15] = m[15] * scale;
			return scaleMat;
		}
		/*
			�s��̃X�J���[�{
			�����F scale �X�J���[�l
			�߂�l�F �X�J���[�{�����s��̃R�s�[
		*/
		Matrix operator*=(float scale) { return *this = *this * scale; }
		/*
			�s��̏�Z
			�����F�@mat �|����s��
			�߂�l�F ��Z���ꂽ�s��
			���[�v�����̍������Ƃ��āA���[�v�A�����[�����O��K�p
		*/
		Matrix operator*(const Matrix& mat) {
			Matrix result((float)0);
			for (int j = 0; j < 4; j++) {
				result.m[j] += m[0] * mat.m[j];
				result.m[j] += m[1] * mat.m[4 + j];
				result.m[j] += m[2] * mat.m[8 + j];
				result.m[j] += m[3] * mat.m[12 + j];

				result.m[4 + j] += m[4] * mat.m[j];
				result.m[4 + j] += m[5] * mat.m[4 + j];
				result.m[4 + j] += m[6] * mat.m[8 + j];
				result.m[4 + j] += m[7] * mat.m[12 + j];

				result.m[8 + j] += m[8] * mat.m[j];
				result.m[8 + j] += m[9] * mat.m[4 + j];
				result.m[8 + j] += m[10] * mat.m[8 + j];
				result.m[8 + j] += m[11] * mat.m[12 + j];

				result.m[12 + j] += m[12] * mat.m[j];
				result.m[12 + j] += m[13] * mat.m[4 + j];
				result.m[12 + j] += m[14] * mat.m[8 + j];
				result.m[12 + j] += m[15] * mat.m[12 + j];
			}

			return result;
		}
		/*
			�s��̏�Z
			����: mat �|����s��
			�߂�l: ��Z�����s��̃R�s�[
		*/
		Matrix operator*=(const Matrix& mat) { return *this = *this * mat; }
		/*
			�s���-���|����
		*/
		inline Matrix operator-() {
			Matrix minus;
			minus.m[0]  = -m[0];  minus.m[1]  = -m[1];  minus.m[2]  = -m[2];  minus.m[3]  = -m[3];
			minus.m[4]  = -m[4];  minus.m[5]  = -m[5];  minus.m[6]  = -m[6];  minus.m[7]  = -m[7];
			minus.m[8]  = -m[8];  minus.m[9]  = -m[9];  minus.m[10] = -m[10]; minus.m[11] = -m[11];
			minus.m[12] = -m[12]; minus.m[13] = -m[13]; minus.m[14] = -m[14]; minus.m[15] = -m[15];
			return minus;
		}

		inline operator MATRIX() {
			MATRIX t_mat{};
			t_mat.m[0][0] = m[0];  t_mat.m[0][1] = m[1];  t_mat.m[0][2] = m[2];  t_mat.m[0][3] = m[3];
			t_mat.m[1][0] = m[4];  t_mat.m[1][1] = m[5];  t_mat.m[0][2] = m[6];  t_mat.m[1][3] = m[7];
			t_mat.m[2][0] = m[8];  t_mat.m[2][1] = m[9];  t_mat.m[2][2] = m[10]; t_mat.m[2][3] = m[11];
			t_mat.m[3][0] = m[12]; t_mat.m[3][1] = m[13]; t_mat.m[3][2] = m[14]; t_mat.m[3][3] = m[15];
			return t_mat;
		}
		operator Vector3D() { return Vector3D(m[3], m[7], m[11]); }

	public:
		float m[16];
	};
}

using MyLib::Matrix;