#pragma once
#include "DxLib.h"
#include "Field/FieldManager.h"

//SHORT
constexpr float SHORT_W = (4.0f);	//����;
constexpr float SHORT_H = (4.0f);	//����;
constexpr float SHORT_D = (4.0f);	//���s��;
constexpr float SHORT_RAD = (2.0f);//���a;
//LONG�֘A
constexpr float LONG_W = (4.0f);	//����;
constexpr float LONG_H = (4.0f);	//����;
constexpr float LONG_D = (4.0f);	//���s��;
constexpr float LONG_RAD = (2.0f);//���a;
//GRAVITY
constexpr float GRAVITY_W = (5.5f);	//����;
constexpr float GRAVITY_H = (0.1f);	//����;
constexpr float GRAVITY_D = (5.5f);	//���s��;
constexpr float GRAVITY_RAD = (1.0f);//���a;
constexpr float GRAVITYCOLLISION_RADIUS = (2.75f);
constexpr float GRAVITY_PLATE_JUMP = 1.6f;	//��������̃W�����v��
//LIFT
constexpr float LIFT_W = (5.0f);	//����;
constexpr float LIFT_H = (0.3f);	//����;
constexpr float LIFT_D = (10.0f);	//���s��;
constexpr float LIFT_RAD = (5.0f);	//���a;
constexpr float LIFTCOLLISION_RADIUS = 1.0f;
constexpr float  LIFT_AMPLITUDE = 0.4f;	//�U�ꕝ
constexpr float	 LIFT_CENTER = 7.f;	//���S�_
//Goal
constexpr float GOAL_W = (9.0f);	//��Q��short�̉���;
constexpr float GOAL_H = (3.0f);	//��Q��short�̍���;
constexpr float GOAL_D = (9.0f);	//��Q��short�̉��s��;
constexpr float GOAL_RAD = (1.0f);//��Q��short�̔��a;
constexpr float GOALCOLLISION_RADIUS = 1.0f;

constexpr int CREATE_OBSTACLES_NUM = 256;//�I�u�W�F�N�g�̐ݒ萔

struct  ObstaclesParameter
{
	int id;
	VECTOR startpos;
};


enum class OBSTACLES_STATE
{
	NONE = -1,
	LONG,
	SHORT,
	GRAVITY,
	LIFT,
	GOAL,
	GOAL2,
	NUM
};

constexpr ObstaclesParameter OBSTACLES_DATABASE[IFIELD_ID::NUM][CREATE_OBSTACLES_NUM] =
{
	{
	static_cast<int>(OBSTACLES_STATE::GOAL2),{216.0f, 27.0f, 0.0f},
	static_cast<int>(OBSTACLES_STATE::GOAL),{3000.0f, 3000.0f, 3000.0f},
	
	static_cast<int>(OBSTACLES_STATE::LIFT),{54.0f, 2.0f, 0.0f},
	static_cast<int>(OBSTACLES_STATE::LIFT),{78.0f, 1.0f, -8.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{-20.0f, 3.0f, 0.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{12.0f, 3.0f, 0.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{22.5f, 12.15f, 0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{22.5f, 12.15f, 4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{22.5f, 12.15f, -4.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{26.5f, 12.15f, 4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{26.5f, 12.15f, 8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{26.5f, 12.15f, 12.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{26.5f, 12.15f, 0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{26.5f, 12.15f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{26.5f, 12.15f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{26.5f, 12.15f, -12.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{76.5f, 20.15f, 4.0f},
	//���S�Ɏ��Δ�
	static_cast<int>(OBSTACLES_STATE::SHORT),{76.5f, 20.15f, 12.0f},


	static_cast<int>(OBSTACLES_STATE::SHORT),{95.5f, 16.15f, 4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{95.5f, 16.15f, 8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{95.5f, 16.15f, 12.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{98.5f, 16.15f, 4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{98.5f, 16.15f, 8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{98.5f, 16.15f, 12.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{100.5f, 16.15f, 4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{100.5f, 16.15f, 8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{100.5f, 16.15f, 12.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{104.5f, 16.15f, 4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{104.5f, 16.15f, 8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{104.5f, 16.15f, 12.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{98.5f, 16.15f,  0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{98.5f, 16.15f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{98.5f, 16.15f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{98.5f, 16.15f, -12.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{102.5f, 16.15f,  0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{102.5f, 16.15f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{102.5f, 16.15f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{102.5f, 16.15f, -12.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{106.5f, 20.15f,  0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{106.5f, 20.15f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{106.5f, 20.15f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{106.5f, 20.15f, -12.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{110.5f, 20.15f,  0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{110.5f, 20.15f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{110.5f, 20.15f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{110.5f, 20.15f, -12.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{114.5f, 21.15f,  0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{114.5f, 21.15f,  -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{114.5f, 21.15f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{114.5f, 21.15f, -12.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{118.5f, 22.15f,  0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{118.5f, 22.15f,  -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{118.5f, 22.15f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{118.5f, 22.15f, -12.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{122.5f, 22.15f,  0.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{122.5f, 22.15f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{122.5f, 22.15f, -12.0f},
	//��
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 18.15f, -16.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 18.15f, -12.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 18.15f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 18.15f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 18.15f, 0.0f},

	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 14.15f, -16.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 14.15f, -12.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 14.15f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 14.15f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 14.15f, 0.0f},

	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 10.15f, -16.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 10.15f, -12.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 10.15f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 10.15f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 10.15f, 0.0f},

	static_cast<int>(OBSTACLES_STATE::LONG), { 122.5f, 6.15f, -16.0f },
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 6.15f, -12.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 6.15f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 6.15f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 6.15f, 0.0f},

	static_cast<int>(OBSTACLES_STATE::LONG), { 122.5f, 2.15f, -16.0f },
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 2.15f, -12.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 2.15f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f,2.15f, -4.0f },
	static_cast<int>(OBSTACLES_STATE::LONG),{122.5f, 2.15f, 0.0f},

	//�����܂�


	static_cast<int>(OBSTACLES_STATE::SHORT),{126.5f, 22.15f,  0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{126.5f, 22.15f,  -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{126.5f, 22.15f,  -8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{126.5f, 22.15f,  -12.0f},


	static_cast<int>(OBSTACLES_STATE::SHORT),{126.5f, 22.15f,  4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{126.5f, 22.15f,  8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{126.5f, 22.15f,  12.0f},


	static_cast<int>(OBSTACLES_STATE::SHORT),{130.5f, 22.15f,  0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{130.5f, 22.15f,  -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{130.5f, 22.15f,  -8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{130.5f, 22.15f,  -12.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{130.5f, 22.15f,  4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{130.5f, 22.15f,  8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{130.5f, 22.15f,  12.0f},


	static_cast<int>(OBSTACLES_STATE::SHORT),{134.5f, 22.15f,  0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{134.5f, 22.15f,  -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{134.5f, 22.15f,  -8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{134.5f, 22.15f,  -12.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{134.5f, 22.15f,  4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{134.5f, 22.15f,  8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{134.5f, 22.15f,  12.0f},


	//��i��
	static_cast<int>(OBSTACLES_STATE::SHORT),{130.5f, 33.15f,  6.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{130.5f, 33.15f,  10.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{126.5f, 33.15f,  6.0f },
	static_cast<int>(OBSTACLES_STATE::SHORT),{126.5f, 33.15f,  10.0f },

	static_cast<int>(OBSTACLES_STATE::SHORT), { 138.5f, 33.15f,  6.0f },
	static_cast<int>(OBSTACLES_STATE::SHORT), { 138.5f, 33.15f,  10.0f },
	static_cast<int>(OBSTACLES_STATE::SHORT), { 142.5f, 33.15f,  6.0f },
	static_cast<int>(OBSTACLES_STATE::SHORT), { 142.5f, 33.15f,  10.0f },

	static_cast<int>(OBSTACLES_STATE::SHORT), { 140.5f, 33.15f,  -6.0f },
	static_cast<int>(OBSTACLES_STATE::SHORT), { 140.5f, 33.15f,  -10.0f },
	static_cast<int>(OBSTACLES_STATE::SHORT), { 144.5f, 33.15f, -6.0f },
	static_cast<int>(OBSTACLES_STATE::SHORT), { 144.5f, 33.15f,  -10.0f },

	static_cast<int>(OBSTACLES_STATE::NONE), {0.0f, 0.0f, 0.0f},
	},

	//�X�e�[�W�Q
	{
	static_cast<int>(OBSTACLES_STATE::GOAL),{346.0f, 55.1f, 0.0f},
	static_cast<int>(OBSTACLES_STATE::GOAL2),{30000.0f, 30000.0f, 0.0f},
	//�K�i�p
	static_cast<int>(OBSTACLES_STATE::SHORT),{22.0f, 3.0f, 0.0f},
	/*static_cast<int>(OBSTACLES_STATE::SHORT),{30.0f, 3.0f, 0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{26.0f, 3.0f, 4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{26.0f, 3.0f, -4.0f},*/
	//�n�܂荶�E
	static_cast<int>(OBSTACLES_STATE::SHORT),{31.0f, 11.0f, 8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{31.0f, 15.0f, 12.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{31.0f, 11.0f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{31.0f, 15.0f, -12.0f},
	
	static_cast<int>(OBSTACLES_STATE::GRAVITY),{57.0f, 15.0f, 0.0f},
	static_cast<int>(OBSTACLES_STATE::GRAVITY),{71.0f, 15.0f, 0.0f},
	
	static_cast<int>(OBSTACLES_STATE::LIFT),{127.0f, 1.5f, 8.0f},
	
	static_cast<int>(OBSTACLES_STATE::SHORT),{122.0f, 17.5f, -5.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{122.0f, 17.5f, -13.0f},
	
	static_cast<int>(OBSTACLES_STATE::SHORT),{140.0f, 13.5f, -13.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{140.0f, 13.5f, -9.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{140.0f, 13.5f, -5.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{144.0f, 13.5f, -13.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{144.0f, 13.5f, -9.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{144.0f, 13.5f, -5.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{148.0f, 13.5f, -13.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{148.0f, 13.5f, -9.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{148.0f, 13.5f, -5.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{152.0f, 13.5f, -13.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{152.0f, 13.5f, -9.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{152.0f, 13.5f, -5.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{148.0f, 21.5f, 13.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{148.0f, 21.5f, 9.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{152.0f, 21.5f, 13.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{152.0f, 21.5f, 9.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{152.0f, 21.5f, 5.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{152.0f, 17.5f, -5.0f},

	static_cast<int>(OBSTACLES_STATE::GRAVITY),{160.0f, 22.5f, 9.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{240.0f, 13.5f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{240.0f, 13.5f, -0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{240.0f, 13.5f, 4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{244.0f, 17.5f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{244.0f, 17.5f, -0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{244.0f, 17.5f, 4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{248.0f, 17.5f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{248.0f, 17.5f, -0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{248.0f, 17.5f, 4.0f},
	
	static_cast<int>(OBSTACLES_STATE::LIFT),{252.0f, 22.0f, 0.0f},
	static_cast<int>(OBSTACLES_STATE::LIFT),{253.0f, 2.0f, 8.5f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{257.0f, 36.0f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{257.0f, 36.0f, 0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{257.0f, 36.0f, 4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{261.0f, 36.0f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{261.0f, 36.0f, 0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{261.0f, 36.0f, 4.0f},

	static_cast<int>(OBSTACLES_STATE::GRAVITY),{282.0f, 36.0f, 6.0f},
	static_cast<int>(OBSTACLES_STATE::GRAVITY),{282.0f, 36.0f, -6.0f},

	static_cast<int>(OBSTACLES_STATE::LIFT),{290.0f, 32.0f, -10.0f},
	static_cast<int>(OBSTACLES_STATE::LIFT),{290.0f, 32.0f, 10.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{296.0f, 50.0f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{296.0f, 50.0f, 0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{296.0f, 50.0f, 4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{300.0f, 50.0f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{300.0f, 50.0f, 0.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{300.0f, 50.0f, 4.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{308.0f, 55.0f, 0.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{314.0f, 54.0f, 8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{314.0f, 54.0f, 12.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{318.0f, 54.0f, 8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{318.0f, 54.0f, 12.0f},

	static_cast<int>(OBSTACLES_STATE::SHORT),{314.0f, 54.0f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{314.0f, 54.0f, -12.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{318.0f, 54.0f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::SHORT),{318.0f, 54.0f, -12.0f},

	static_cast<int>(OBSTACLES_STATE::GRAVITY),{324.0f, 56.0f, 0.0f},

	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 57.0f, 4.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 57.0f, 8.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 57.0f, 12.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 57.0f, 16.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 57.0f, 0.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 57.0f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 57.0f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 57.0f, -12.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 57.0f, -16.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 61.0f, 4.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 61.0f, 8.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 61.0f, 12.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 61.0f, 16.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 61.0f, 0.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 61.0f, -4.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 61.0f, -8.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 61.0f, -12.0f},
	static_cast<int>(OBSTACLES_STATE::LONG),{362.0f, 61.0f, -16.0f},
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 65.0f, 4.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 65.0f, 8.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 65.0f, 12.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 65.0f, 16.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 65.0f, 0.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 65.0f, -4.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 65.0f, -8.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 65.0f, -12.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 65.0f, -16.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 69.0f, 4.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 69.0f, 8.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 69.0f, 12.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 69.0f, 16.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 69.0f, 0.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 69.0f, -4.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 69.0f, -8.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 69.0f, -12.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 69.0f, -16.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 73.0f, 4.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 73.0f, 8.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 73.0f, 12.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 73.0f, 16.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 73.0f, 0.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 73.0f, -4.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 73.0f, -8.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 73.0f, -12.0f },
	static_cast<int>(OBSTACLES_STATE::LONG), { 362.0f, 73.0f, -16.0f },



	static_cast<int>(OBSTACLES_STATE::NONE), {0.0f, 0.0f, 0.0f},
	},
};