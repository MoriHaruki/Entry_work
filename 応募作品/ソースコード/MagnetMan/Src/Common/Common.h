#pragma once
#include "Vector/Vector3D.h"
#include <random>
#include <crtdbg.h>

#ifdef _DEBUG
#define NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define NEW new
#endif

//�J�����֘A
constexpr float CAMERA_OFFSET_POS = (10.0f);	//�J�����̃v���C���[����̃I�t�Z�b�g�l;
constexpr float CAMERA_OFFSET_LOOK_X = (1.0f);
constexpr float CAMERA_OFFSET_LOOK_Y = (1.0f);//�J�����̒����_�̃v���C���[���W����̍���;
constexpr float CAMERA_OFFSET_LOOK_Z = (1.0f);
constexpr float CAMERA_HEIGHT = (6.0f);
constexpr float CAMERA_HEIGHT2 = (5.0f);
constexpr float GAME_OVER_POS_Y = -1.0f;

static int GAME_FPS = 60;
class CCommon
{
public:
	static void Init();
	static void Step();
	static float GetGameDeltaFrame();
	static float GetGameDeltaTime();
	static void InitRandom();
	static int  GetRandom(int min_value, int max_value);
	static float GetRandom(float min_value, float max_value, int digit);

public:
	//�ݒ�t���[�����[�g�i60����1�b�j
	static constexpr int FRAME_RATE = 60;
	static constexpr float FRAME_MIN = 1.0f / FRAME_RATE;
	//��ʃT�C�Y
	static constexpr int WINDOW_W = 1280;
	static constexpr int WINDOW_H = 720;
	static constexpr Vector2D WINDOW_CENTER = Vector2D(WINDOW_W * 0.5f, WINDOW_H * 0.5f);
	//���֘A
	static constexpr float BOX_NUM = (5);	//���̐�
	
private:
	static int old_time_;
	static float delta_frame_;
	static std::mt19937 mt_;
};
