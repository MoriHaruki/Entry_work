#pragma once

const int FADEIN_TIME = 60;

class CScene
{
protected:
	enum SceneState 
	{
		SCENE_STATE_NONE,
		SCENE_STATE_FADEIN,
		SCENE_STATE_FADEOUT,
	};
public:
	CScene();
	virtual ~CScene();

	//������
	virtual void Init() = 0;

	//���[�h
	virtual void Load() = 0;

	//���[�h����
	virtual void OnLoadEnd() = 0;

	//�X�e�b�v����
	virtual void Step();

	//�X�V����
	virtual void Update() = 0;

	//�`��
	virtual void Draw() = 0;

	//�㏈��
	virtual void Fin() = 0;

protected:
	void ChangeScene(int next_scene, int fade_time = 60);
	virtual void OnFadeinEnd();

protected:
	int state_;

private:
	int next_scene_;
};