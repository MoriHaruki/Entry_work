#include <math.h>
#include "DxLib.h"
#include "Input/InputManager.h"
#include"Collision/CollisionManager.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneParameter.h"
#include "Fade/Fade.h"
//���������[�N���m�p
#ifdef _DEBUG
#include <crtdbg.h>
#endif

//�V�X�e�������擾
SYSTEM_INFO GetSystemInfo() {
	SYSTEM_INFO SystemInfo = { 0 };
	::GetSystemInfo(&SystemInfo);
	return SystemInfo;
}

namespace FRAME_RATE
{
	//�t���[�����[�g�֘A
	int g_nCurrentTime = 0;			//���݂̎���
	int g_nLastFrameTime = 0;		//�O��̃t���[�����s���̎���
	int g_nFrameCnt = 0;			//�t���[���J�E���g�p
	int g_nUpdateFrameRateTime = 0;	//�t���[�����[�g���X�V��������
	float g_fFrameRate = 0.f;		//�t���[�����[�g�i�\���p�j
	int SoundHundle = 0;
}

void CalcFrameRate();			//�t���[�����[�g�v�Z
void DrawFrameRate();			//�t���[�����[�g�\���i�f�o�b�O�p�j
using namespace FRAME_RATE;
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(true);	//�E�B���h�E�̏�Ԃ�ݒ肷��
	//�E�B���h�E�̐ݒ�
	SetWindowStyleMode(8);
	SetWindowSizeChangeEnableFlag(TRUE);
	SetWindowSizeExtendRate(0.75f);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);		//NEW�ɂ�郁�������[�N���m�J�n
	//DX���C�u�����̏�����
	if(DxLib_Init() == -1)												
	{
		return -1;
	}
	SetUseASyncLoadFlag(true);
	SetASyncLoadThreadNum(GetSystemInfo().dwNumberOfProcessors);
	SetGraphMode(CCommon::WINDOW_W, CCommon::WINDOW_H, 32);				//�E�B���h�E�T�C�Y��ύX
	SetDrawScreen(DX_SCREEN_BACK);										//�`�悷��X�N���[����ݒ�
	SetTransColor(0, 127, 127);											//���ߐF��ݒ�

	//�L�[���͏�����
	TheGameInputManager->Init();
	TheGameInputManager->GetInputMouse()->LiberationMousePointer();
	//�t�F�[�h�@�\��������
	CFade::Init();

	//�V�[���}�l�[�W���N���X�����Ə�����
	CSceneManager* scene_manager = TheSceneManager;
	scene_manager->StartFirstScene(SCENE_ID_TITLE);

	//�Q�[�����C�����[�v
	while(ProcessMessage() != -1)
	{
		Sleep(1);													//�V�X�e���ɏ�����Ԃ�
		g_nCurrentTime = GetNowCount();								//���݂̎������擾
		// ���݂̎������A�O��̃t���[�������
		// 1/60�b�o�߂��Ă����珈�������s����
		if(g_nCurrentTime - g_nLastFrameTime >= 1000 / CCommon::FRAME_RATE)
		{
			g_nLastFrameTime = g_nCurrentTime;						//�t���[�����s���̎��Ԃ��X�V
			g_nFrameCnt++;											//�t���[�������J�E���g
			if(TheGameInputManager->IsPush("ESC"))					//�G�X�P�[�v�L�[�������ꂽ��I��
			{
				break;
			}
			ClearDrawScreen();										//��ʂɕ\�����ꂽ���̂�������
			CCommon::Step();											//�C���v�b�g�X�e�b�v
			TheGameInputManager->Step();
			CFade::Step();											//�t�F�[�h�ʏ�
			PlaySoundMem(SoundHundle, DX_PLAYTYPE_BACK, true);		//BGM
			CalcFrameRate();										//�t���[�����[�g�v�Z
			DrawFrameRate();										//�t���[�����[�g�\���i�f�o�b�O�p�j
			scene_manager->Loop();									//�V�[���̍X�V
			TheCollisionManager->Draw();
			CFade::Draw();											//�t�F�[�h�`��
			ScreenFlip();											//�t���b�v�֐��i���[�v�̏I���ɂP�x�����s���j

		}
	}

	TheGameInputManager->Fin();
	GameInputInstance::Delete();
	CFade::Fin();													//�t�F�[�h�@�\�̌㏈��
	TheSceneManager->Fin();
	SceneManagerInstance::Delete();
	DeleteSoundMem(SoundHundle);									//���ʉ��j��
	InitGraph();													//�g�p�������ׂẲ摜��j��
	DxLib_End();													//DX���C�u�����̌㏈��
	return 0;
}
//�t���[�����[�g�v�Z
void CalcFrameRate()
{
	int nDifTime = g_nCurrentTime - g_nUpdateFrameRateTime;			//�O��̃t���[�����[�g�X�V����̌o�ߎ��Ԃ����߂�
	if(nDifTime > 1000)												//�O��̃t���[�����[�g�X�V����P�b�ȏ�o�߂��Ă�����t���[�����[�g���X�V����
	{
		float fFrameCnt = (float)(g_nFrameCnt * 1000);				//�t���[���񐔂��~���b�ɍ��킹��B�@�����܂ŏo�������̂�float�ɃL���X�g
		g_fFrameRate = fFrameCnt / nDifTime;						//�t���[�����[�g�����߂�B�@���z�ǂ���Ȃ� 60000 / 1000 �� 60 �ƂȂ�
		g_nFrameCnt = 0;											//�t���[���J�E���g���N���A
		g_nUpdateFrameRateTime = g_nCurrentTime;					//�t���[�����[�g�X�V���Ԃ��X�V
	}
}
//�t���[�����[�g�\���i�f�o�b�O�p�j
void DrawFrameRate()
{
#ifdef DEBUG
	DrawFormatString(180, 100, GetColor(255, 30, 30), "FPS[%.2f]", g_fFrameRate);
#endif

	
}