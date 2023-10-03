#pragma once

#include <math.h>

#define PI (3.1415926535897932384626433832795f)

namespace MyLib {
	/* ���e�덷 */
	static inline constexpr float TOLERANCE = 0.0001f;

	/* ��Βl�擾 */
	template<class T>
	static inline T Abs(const T value) { return (value >= (T)0) ? value : -value; }

	/* �덷�����e����C�R�[���֐� */
	template <class T>
	static constexpr inline bool IsNearlyEqual(T A, T B, float Tolerance = TOLERANCE) { return Abs(A - B) <= Tolerance; }
	
	/* �덷�����e����[������֐� */
	template <class T>
	static constexpr inline bool IsNearlyZero(T A, float Tolerance = TOLERANCE) { return Abs(A) <= Tolerance; }
	
	/* �Q�̐��l�̍ő�l */
	template <class T>
	static constexpr inline T Max(T A, T B) { return (A >= B) ? A : B; }
	
	/* �R�̐��l�̍ő�l */
	template <class T>
	static constexpr inline T Max3(T A, T B, T C) {
		return Max(Max(A, B), C);
	}
	
	/* �Q�̐��l�̍ŏ��l */
	template <class T>
	static constexpr inline T Min(T A, T B) { return (A <= B) ? A : B; }
	
	/* �R�̐��l�̍ŏ��l */
	template <class T>
	static constexpr inline T Min3(T A, T B, T C) {
		return Min(Min(A, B), C);
	}

	/* �X���b�v�֐� */
	template <class T>
	static constexpr inline void Swap(T* A, T* B) {
		T temp = *A;
		*A = *B;
		*B = temp;
	}
	
	/* 
		�N�����v�֐� 
		�����F	value		:	�߂�l
				max			:	�ő�l
				min			:	�ŏ��l
	*/
	template<class T>
	static inline void Clamp(T* value, T max, T min) {
		if (max < *value) { *value = max; }
		else if (min > *value) { *value = min; }
	}

	/* �Q��̒l���擾 */
	template<class T>
	static inline  T Square(T value) { return value * value; }

	/* Sin�g���擾 */
	static inline float Sin(float rad) { return sinf(rad); }

	/*
		���߂�ꂽ�͈͂ł�Sin�g���擾
		�����F	min		:	�ŏ��l
				max		:	�ő�l
				rad		:	�p�x
	*/
	static inline float DefinedRangeSin(float min, float max, float rad) {
		float mult = (max - min) / 2.f;
		return (Sin(rad) + 1.f) * mult + min;
	}

	/* �tSin�g���擾 */
	static inline float Asin(float rad) { return asinf((rad < -1.f) ? -1.f : ((rad < 1.f) ? rad : 1.f)); }

	/* �o�Ȑ�Sin�g���擾 */
	static inline float Sinh(float rad) { return sinhf(rad); }

	/* Cos�g���擾 */
	static inline float Cos(float rad) { return cosf(rad); }

	/* �o�Ȑ�Cos�g���擾 */
	static inline float Acos(float rad) { return acosf((rad < -1.f) ? -1.f : ((rad < 1.f) ? rad : 1.f)); }

	/* Tan�g���擾 */
	static inline float Tan(float rad) { return tanf(rad); }

	/* �tTan�g���擾 */
	static inline float Atan(float rad) { return atanf(rad); }

	/* �t����Ԃ� */
	static inline float Inv(float value) { return 1.f / value; }

	/* �������̒l��Ԃ� */
	static inline float Sqrt(float value) { return sqrtf(value); }

	/* �������̋t���̒l��Ԃ� */
	static inline float InvSqrt(float value) { return 1.f / sqrtf(value); }

	/* A��B��̒l��Ԃ�(float�^) */
	static inline float Pow(float A, float B) { return powf(A, B); }

	/* A��B��̒l��Ԃ�(int�^) */
	static inline int Pow(int A, int B) {
		float result = powf(static_cast<float>(A), static_cast<float>(B));

		return static_cast<int>(result);
	}

	/* �A�[�N�^���W�F���g�֐� */
	static inline float Atan2(float y, float x) {
		const float absX = Abs(x);
		const float absY = Abs(y);
		const bool yAbsBigger = (absY > absX);
		float t0 = yAbsBigger ? absY : absX;	/* Max(absY, absX) */
		float t1 = yAbsBigger ? absX : absY;	/* Min(absY, absX) */

		if (t0 == 0.f) { return 0.f; }

		float t3 = t1 / t0;
		float t4 = t3 * t3;

		static const float c[7] = {
			+7.2128853633444123e-03f,
			-3.5059680836411644e-02f,
			+8.1675882859940430e-02f,
			-1.3374657325451267e-01f,
			+1.9856563505717162e-01f,
			-3.3324998579202170e-01f,
			+1.0f
		};

		t0 = c[0];
		t0 = t0 * t4 + c[1];
		t0 = t0 * t4 + c[2];
		t0 = t0 * t4 + c[3];
		t0 = t0 * t4 + c[4];
		t0 = t0 * t4 + c[5];
		t0 = t0 * t4 + c[6];
		t3 = t0 * t3;

		t3 = yAbsBigger ? (0.5f * PI) - t3 : t3;
		t3 = (x < 0.0f) ? PI - t3 : t3;
		t3 = (y < 0.0f) ? -t3 : t3;

		return t3;
	}

	/*
		�]���藝����p�x���擾����
		�����F	a	:	���߂�p�x�̑Εӂ̒���
				b	:	���߂�p�x���͂��ޕ�1
				c	:	���߂�p�x���͂��ޕ�2
		�߂�l�F�p�x
	*/
	static inline float LawOfCosines(float a, float b, float c) {
		float A = Square(b) + Square(c) - Square(a);
		float B = 2.f * b * c;
		return Acos(A / B);
	}

	/* �^����ꂽ���W�A���p�� +/- �΂͈̔͊O�������ꍇ�A�͈͓��ɖ߂� */
	static inline float UnwindRadians(float A) {
		while (A > PI) {
			A -= (PI * 2.f);
		}
		while (A < -PI) {
			A += (PI * 2.f);
		}

		return A;
	}

	/* ��]�l��0 �` 2�΂̒l�ɂ��� */
	static inline void RadianNormalize(float* rad) {
		float result = *rad;
		if (result < 0.0f) {
			while (result < 0.0f) {
				result += PI * 2.f;
			}
		}
		else if (result > PI * 2.f) {
			while (result <= PI * 2.f) {
				result -= PI * 2.f;
			}
		}
	}

	/* �^����ꂽ�f�B�O���[�p��+/- 180�x�͈̔͊O�������ꍇ�A�͈͓��ɖ߂� */
	static inline float UnwindDegrees(float A) {
		while (A > 180.f) {
			A -= 360.f;
		}
		while (A < -180.f) {
			A += 360.f;
		}
		return A;
	}
}