#pragma once

#include "Singleton/Singleton.h"
#include "PlayCamera.h"
#include "DebugCamera.h"
#include "Field/Field.h"

//インスタンスへのマクロアクセス
#define CameraManagerInstance MyLib::Singleton<CCameraManager>
//インスタンス呼び出し簡略化
#define TheCameraManager MyLib::Singleton<CCameraManager>::Get()

class CCameraManager{

private:
	//アクセス権限付与
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
