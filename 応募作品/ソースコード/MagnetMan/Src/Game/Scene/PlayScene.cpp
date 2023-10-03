#include "PlayScene.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneParameter.h"
#include "Object/Camera/CameraManager.h"
#include "Object/Bullet/BulletManager.h"
#include "Object/Player/PlayerManager.h"
#include "Object/Box/BoxManager.h"
#include "Object/Enemy/EnemyManager.h"
#include "Collision/CollisionManager.h"
#include "Sound/SoundManager.h"
#include "Sky/SkyManager.h"
#include "Field/FieldManager.h"
#include "Object/Obstacles/ObstaclesManager.h"
#include "Input/InputManager.h"
#include "Fade/Fade.h"

using namespace GAME_INPUT::ACTION;
constexpr Vector3D POS(-100.0f, 25.0f, -0.0f);


CPlay::CPlay() : CScene()
{
}

CPlay::~CPlay()
{
}

void CPlay::Init()
{
	InitCollision();
	InitBullet();
	InitEnemy();
	InitStage();
	InitBox();
	InitObstacles();
	InitCamera();
	InitEffect();
	InitSky();
	InitPlayer();
}

void CPlay::Load()
{
	LoadBullet();
	LoadBox();
	LoadObstacles();
	LoadEffect();
	LoadSound();
	LoadSky();
	LoadField();
	LoadPlayer();
}

void CPlay::OnLoadEnd()
{
	// BGM�Đ�
	CSoundManager::PlayBGM(SOUND_ID_BGM_PLAY_SCENE);

	// �t�F�[�h�C��
	CFade::FadeIn();
	state_ = SCENE_STATE_FADEIN;
}

void CPlay::Step()
{
	CGoal* goal = static_cast<CGoal*>(TheObstaclesManager->GetObstacles(OBSTACLES_STATE::GOAL));
	CGoal2* goal2 = static_cast<CGoal2*>(TheObstaclesManager->GetObstacles(OBSTACLES_STATE::GOAL2));
	CScene::Step();
	TheEnemyManager->Step();
	ThePlayerManager->Step();
	TheBoxManager->Step();
	TheObstaclesManager->Step();
	TheSkyManager->Step();
	TheFieldManager->Step();
	TheBulletManager->Step();
	TheCollisionManager->Step();
	TheCameraManager->Step();

	//�X�e�[�W�P����
	if (TheFieldManager->GetID() == IFIELD_ID::Field01)
	{
		CPlayerManager* player_manager = ThePlayerManager;
		CPlayer* player = player_manager->GetPlayer();
		//START�{�^���ňړ�
		if (CFade::IsFadeEnd() && TheGameInputManager->IsPush(ACTION_NAME[IInputActionKind::RESTART]))
		{
			CPlayerManager* player_manager = ThePlayerManager;
			CPlayer* player = player_manager->GetPlayer();
			CSoundManager::DeleteSound(SOUND_GROUP_PLAY);
			CFade::FadeOut();
			CFade::FadeIn();
			player->SetPos(DEFAULT_POS1);
			TheFieldManager->ChangeField(IFIELD_ID::Field01);
			CSoundManager::Load(SOUND_GROUP_PLAY);
			CSoundManager::PlayBGM(SOUND_ID_BGM_PLAY_SCENE);
		}
		//������x��������
		if (player->GetPos().y <= GAME_OVER_POS_Y && CFade::IsFadeEnd())
		{
			ChangeScene(SCENE_ID_GAMEOVER);	//�V�[���J��
		}
	}

	//�X�e�[�W�Q�̏���
	if (TheFieldManager->GetID() == IFIELD_ID::Field02)
	{
		CPlayerManager* player_manager = ThePlayerManager;
		CPlayer* player = player_manager->GetPlayer();
		//START�{�^��
		if (CFade::IsFadeEnd() && TheGameInputManager->IsPush(ACTION_NAME[IInputActionKind::RESTART]))
		{
			CPlayerManager* player_manager = ThePlayerManager;
			CPlayer* player = player_manager->GetPlayer();
			CSoundManager::DeleteSound(SOUND_GROUP_PLAY);
			CFade::FadeOut();
			CFade::FadeIn();
			player->SetPos(DEFAULT_POS2);
			TheFieldManager->ChangeField(IFIELD_ID::Field02);
			CSoundManager::Load(SOUND_GROUP_PLAY);
			CSoundManager::PlayBGM(SOUND_ID_BGM_PLAY_SCENE);
		}
		//������x��������
		if (player->GetPos().y <= GAME_OVER_POS_Y && CFade::IsFadeEnd())
		{
			ChangeScene(SCENE_ID_GAMEOVER);	//�V�[���J��
		}
	}

	//�S�[���ɓ���������
	if (goal->GetGoalFlag() && CFade::IsFadeEnd())
	{
		CPlayerManager* player_manager = ThePlayerManager;
		CPlayer* player = player_manager->GetPlayer();
		CSoundManager::DeleteSound(SOUND_GROUP_PLAY);
		ChangeScene(SCENE_ID_CLEAR);	//�V�[���J��
		CSoundManager::Load(SOUND_GROUP_PLAY);
		CSoundManager::PlayBGM(SOUND_ID_BGM_PLAY_SCENE);
	}
	//�S�[��2�ɓ���������
	if (goal2->GetGoal2Flag() && CFade::IsFadeEnd())
	{
		CPlayerManager* player_manager = ThePlayerManager;
		CPlayer* player = player_manager->GetPlayer();
		CSoundManager::DeleteSound(SOUND_GROUP_PLAY);
		CFade::FadeOut();
		CFade::FadeIn();
		player->SetPos(DEFAULT_POS2);
		TheFieldManager->ChangeField(IFIELD_ID::Field02);	//�X�e�[�W�Q��
		CSoundManager::Load(SOUND_GROUP_PLAY);
		CSoundManager::PlayBGM(SOUND_ID_BGM_PLAY_SCENE);
	}
}

void CPlay::Update()
{
	TheBulletManager->Update();
	TheCameraManager->Update();
	TheSkyManager->Update();
	TheCollisionManager->Update();
}

void CPlay::Draw()
{
	TheEnemyManager->Draw();
	TheBoxManager->Draw();
	TheObstaclesManager->Draw();
	TheBulletManager->Draw();
	TheCameraManager->Draw();
	TheSkyManager->Draw();
	TheFieldManager->Draw();
	ThePlayerManager->Draw();
}

void CPlay::Fin()
{
	ThePlayerManager->Fin();
	TheEnemyManager->Fin();
	TheBoxManager->Fin();
	TheObstaclesManager->Fin();
	TheCameraManager->Fin();
	TheBulletManager->Fin();
	TheCollisionManager->Fin();
	TheSkyManager->Fin();
	TheFieldManager->Fin();
	TheCollisionManager->Fin();

	// �v���C�V�[���݂̂Ŏg�p������̂��폜
	PlayerManagerInstance::Delete();
	EnemyManagerInstance::Delete();
	BoxManagerInstance::Delete();
	ObstaclesManagerInstance::Delete();
	CameraManagerInstance::Delete();
	BulletManagerInstance::Delete();
	CollisionManagerInstance::Delete();
	SkyManagerInstance::Delete();
	FieldManagerInstance::Delete();
	CSoundManager::DeleteSound(SOUND_GROUP_PLAY);
}


void CPlay::InitBullet()
{
	TheBulletManager->Init();
}

void CPlay::InitEnemy()
{
	TheEnemyManager->Init();
}

void CPlay::InitBox()
{
	TheBoxManager->Init();
}

void CPlay::InitPlayer()
{
	ThePlayerManager->Init();
}

void CPlay::InitObstacles()
{
	TheObstaclesManager->Init();
}

void CPlay::InitStage()
{
	TheFieldManager->StartField(IFIELD_ID::Field01);
	TheSkyManager->CreateSky(SKY_ID::SKY_ID_MONO);
}

void CPlay::InitCamera()
{
	TheCameraManager->Init();
}

void CPlay::InitEffect()
{
}

void CPlay::InitCollision()
{
	TheCollisionManager->Init();
}

void CPlay::InitSky()
{
	TheSkyManager->Init();
}

//���[�h
void CPlay::LoadBullet()
{
	TheBulletManager->Load();
}

void CPlay::LoadPlayer()
{
	ThePlayerManager->Load();
}

void CPlay::LoadBox()
{
	TheBoxManager->Load();
}

void CPlay:: LoadObstacles()
{
}

void CPlay::LoadEffect()
{
}

void CPlay::LoadSound()
{
	CSoundManager::Load(SOUND_GROUP_PLAY);
}

void CPlay::LoadSky()
{
	TheSkyManager->Load();
}

void CPlay::LoadField()
{
	TheFieldManager->Load();
}