#pragma once

#include "Singleton/Singleton.h"
#include "Scene.h"
#include "Common.h"

//�C���X�^���X�ւ̃}�N���A�N�Z�X
#define SceneManagerInstance MyLib::Singleton<CSceneManager>
//�C���X�^���X�Ăяo���ȗ���
#define TheSceneManager MyLib::Singleton<CSceneManager>::Get()

class CSceneManager
{
private:
	//�A�N�Z�X�����t�^
	friend MyLib::Singleton<CSceneManager>;

private:
	CSceneManager();
	~CSceneManager();

public:
	//������
	void Init();

	//���[�v
	void Loop();

	//�㏈��
	void Fin();

	//�P�ԍŏ��̃V�[�����J�n����
	void StartFirstScene(int sceneID);

	//�����̃V�[���ɕύX����
	void ChangeScene(int sceneID);

	// ���݂̃V�[�����擾����
	CScene* GetNowScene() const { return scene_; }
	//���݃V�[����ID���l������
	int GetCurrentSceneID() const { return current_scene_id_; }

private:
	//�V�[���𐶐�����
	void CreateScene(int sceneID);
	//���̉�ʂɑJ�ڂ�����
	void ChangeNextScene();
	// �V�[�����[�v���̊e�֐�
	void SceneInit();
	void SceneLoad();
	void SceneLoadEnd();
	void SceneLoop();
	void SceneFin();

private:
	//���݂̃V�[��ID
	int current_scene_id_;
	int next_scene_id_;
	int current_scene_state_;

	//���|�C���^�P�ŊǗ�����
	CScene* scene_;
};