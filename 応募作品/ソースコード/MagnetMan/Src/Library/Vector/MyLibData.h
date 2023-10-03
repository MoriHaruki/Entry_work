#pragma once

#include "Vector/Vector3D.h"
#include "Matrix/Matrix.h"

namespace MyLib 
{
	/*
		Vector2D����Vector3D�ւ̃L���X�g�p�֐�
	*/
	inline Vector3D Vector2DCastToVector3D(const Vector2D& V) {
		return Vector3D(V.x, V.y, 0.f);
	}
	/*
		�s���3D�x�N�g���̊|���Z�̉��Z�q�̃I�[�o�[���[�h
		�����F	matrix		�s��
				vector_3d	3D�x�N�g��
		�߂�l�F���Z���ʁi3D�x�N�g���j
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
		�s���3D�x�N�g���̊|���Z�̉��Z�q�̃I�[�o�[���[�h
		�����F	matrix		�s��
				vector_3d	3D�x�N�g��
		�߂�l�F���Z���ʁi3D�x�N�g���j
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
		���͂��ꂽ�x�N�g���̊p�x�����߂�
		���ʕ���(Y��������)����ǂ̂��炢�p�x������̂����v�Z����
		�����F	vec		:	�X�������߂����x�N�g��
		�߂�l�F�x�N�g���̌X��(float)
		�g�����Ƃ��ẮA�߂�l�̊p�x�����[��]�s��ɑ�����āA�O���x�N�g���Ƃ̍s��ς�����
	*/
	inline float CalcVecAngle(const Vector2D& vec) {
		float result = 0.f;
		result = Atan2(vec.y, vec.x);
		// ���ʕ����Ƃ̊p�x�����߂邽�߂ɁA��/�Q����������ɔ��]������
		result -= PI * 0.5f;
		result = -result;
		return result;
	}
	/*
		�O���x�N�g������ړ��x�N�g���Ԃ̊p�x�����߂�
		�����F	forward	:	�O���x�N�g��
				move	:	�ړ��x�N�g��
				axix	:	�O���x�N�g���ƈړ��x�N�g���̖@���x�N�g��(�߂�l)
							���N�H�[�^�j�I���ŉ�]������Ƃ��ɂ��̒l����]���ɂȂ�
		�߂�l�F�p�x(���W�A���P��)
	*/
	inline float CalcForwardToMoveAngle(const Vector3D& forward, const Vector3D& move, Vector3D* axis) {
		float forward_long = forward.Long();
		Vector3D target = (forward + move).Normalize();
		target *= forward_long;
		// ��]�������߂�
		*axis = forward ^ target;
		axis->Normalize();

		float forward_longsq = forward.LongSq();
		float move_longsq = move.LongSq();
		// �]���藝����
		return Acos((2.f * forward_longsq - move_longsq) / (2.f * (forward | target)));
	}
	
}

	

