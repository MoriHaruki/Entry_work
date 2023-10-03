#include "SceneManager.h"
#include "SceneParameter.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include "ClearScene.h"
#include "GameOverScene.h"
#include "Input/Input.h"
#include "Fade/Fade.h"

CSceneManager::CSceneManager(): 
	scene_(nullptr),current_scene_state_(SCENE_STATE_INIT)
{
	scene_ = nullptr;
	current_scene_state_ = SCENE_STATE_INIT;
	next_scene_id_ = SCENE_ID_NUM;
	current_scene_id_ = SCENE_ID_NUM;
}

CSceneManager::~CSceneManager()
{
}

//������
void CSceneManager::Init()
{
	CFade::Init();
}

//���[�v
void CSceneManager::Loop()
{
	static void (CSceneManager:: * scene_func[])() = {
		&CSceneManager::SceneInit,
		&CSceneManager::SceneLoad,
		&CSceneManager::SceneLoadEnd,
		&CSceneManager::SceneLoop,
		&CSceneManager::SceneFin,
	};

	(this->*scene_func[current_scene_state_])();
}

// �V�[�����[�v���̊e�֐�
void CSceneManager::SceneInit()
{
	scene_->Init();
	current_scene_state_ = SCENE_STATE_LOAD;
}

void CSceneManager::SceneLoad()
{
	scene_->Load();
	current_scene_state_ = SCENE_STATE_LOAD_END;
}

void CSceneManager::SceneLoadEnd()
{
	scene_->OnLoadEnd();
	current_scene_state_ = SCENE_STATE_LOOP;
}

void CSceneManager::SceneLoop()
{
	scene_->Step();
	scene_->Update();
	scene_->Draw();
}

void CSceneManager::SceneFin()
{
	scene_->Fin();
	ChangeNextScene();
}

//�㏈��
void CSceneManager::Fin()
{
	if (scene_) {
		scene_->Fin();
		delete scene_;
		scene_ = nullptr;
	}
}

//�P�ԍŏ��̃V�[�����J�n����
void CSceneManager::StartFirstScene(int sceneID)
{
	//���ɉ����V�[���������Ă�̂ł���Α��I��
	if (scene_) return;

	//�V�[���𐶐����ď���������J�n����
	CreateScene(sceneID);
	current_scene_id_ = sceneID;
	current_scene_state_ = SCENE_STATE_INIT;
}

//�����̃V�[���ɕύX����
void CSceneManager::ChangeScene(int sceneID)
{
	//���ɑJ�ڂ���V�[�����o���Ă����A�I��������
	next_scene_id_ = sceneID;
	current_scene_state_ = SCENE_STATE_FIN;
}

//�V�[���𐶐�����
void CSceneManager::CreateScene(int sceneID)
{
	//�V�[���𐶐�
	switch (sceneID)
	{
	case SCENE_ID_TITLE: scene_ = NEW CTitle; break;
	case SCENE_ID_PLAY: scene_ = NEW CPlay; break;
	case SCENE_ID_CLEAR: scene_ = NEW Clear; break;
	case SCENE_ID_GAMEOVER: scene_ = NEW CGameOver; break;
	default:								break;
	}
}

//���̃V�[���ɑJ�ڂ���
void CSceneManager::ChangeNextScene()
{
	//�I�������V�[�����폜
	delete scene_;
	scene_ = nullptr;
	//���̃V�[���𐶐�
	CreateScene(next_scene_id_);
	//���݂̃V�[��ID�ݒ�
	current_scene_id_ = next_scene_id_;
	//��Ԃ��������ɖ߂�
	current_scene_state_ = SCENE_STATE_INIT;
}