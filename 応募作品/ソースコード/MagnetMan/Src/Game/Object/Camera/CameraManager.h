#pragma once

#include "Singleton/Singleton.h"
#include "PlayCamera.h"
#include "DebugCamera.h"
#include "Field/Field.h"

//�C���X�^���X�ւ̃}�N���A�N�Z�X
#define CameraManagerInstance MyLib::Singleton<CCameraManager>
//�C���X�^���X�Ăяo���ȗ���
#define TheCameraManager MyLib::Singleton<CCameraManager>::Get()

class CCameraManager{

private:
	//�A�N�Z�X�����t�^
	friend MyLib::Singleton<CCameraManager>;

public:
	enum class CAMERA_ID
	{
		CAMERA_ID_PLAY,
		CAMERA_ID_DEBUG,
	};

private:

	CCameraManager();
	~CCameraManager();

public:

	void Init();
	void Step();
	void Update();
	void Draw();
	void Fin();
	void ChangeCamera(CAMERA_ID cameraID);
	CAMERA_ID GetCurrentID() { return current_camera_id_; }
	void SetNearFar(float near_val, float far_val);
	CPlayCamera* GetPlayCamera() { return &play_camera_; }
	CDebugCamera* GetDebugCamera() { return &debug_camera_; }

private:

	CAMERA_ID current_camera_id_;
	CPlayCamera play_camera_;
	CDebugCamera debug_camera_;
};
