#include "CameraManager.h"
#include "Input/InputManager.h"

CCameraManager::CCameraManager()
{
	current_camera_id_ = CAMERA_ID::CAMERA_ID_PLAY;
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::Init()
{
	SetNearFar(1.0f, 150.0f);
	play_camera_.Init(VGet(0.0f,8.0f,0.0f), VGet(0.0f,0.0f,0.0f));
}

void CCameraManager::Step()
{
#ifdef _DEBUG

	if (TheGameInputManager->IsPush(std::string("StartDebugCamera")))
	{
		switch (GetCurrentID())
		{

		case CCameraManager::CAMERA_ID::CAMERA_ID_DEBUG:
		{
			ChangeCamera(CCameraManager::CAMERA_ID::CAMERA_ID_PLAY);
		}
		break;

		case CCameraManager::CAMERA_ID::CAMERA_ID_PLAY:
		{
			ChangeCamera(CCameraManager::CAMERA_ID::CAMERA_ID_DEBUG);
		}
		break;
		}
	}
#endif
	switch (current_camera_id_)
	{
	case CAMERA_ID::CAMERA_ID_PLAY:
	{
		play_camera_.Step();
		CField	field;
		play_camera_.SetPos(field.HitCheck(play_camera_.GetFocus(),play_camera_.GetPos()));
	}
	break;
	case CAMERA_ID::CAMERA_ID_DEBUG:
	{
		debug_camera_.Step();
	}
	break;
	}
}

void CCameraManager::Update()
{
	switch (current_camera_id_)
	{
	case CAMERA_ID::CAMERA_ID_PLAY:
	{
		play_camera_.Update();
	}
	break;
	case CAMERA_ID::CAMERA_ID_DEBUG:
	{
		debug_camera_.Update();
	}
	break;
	}
}

void CCameraManager::Draw()
{
	switch (current_camera_id_)
	{
	
	case CAMERA_ID::CAMERA_ID_PLAY:
	{
	}
	break;
	
	case CAMERA_ID::CAMERA_ID_DEBUG:
	{
		debug_camera_.Draw();

	}
	break;
	}
}

void CCameraManager::Fin()
{
	play_camera_.Fin();

	debug_camera_.Fin();
	
}

void CCameraManager::ChangeCamera(CAMERA_ID cameraID)
{
	current_camera_id_ = cameraID;

	if (cameraID == CAMERA_ID::CAMERA_ID_DEBUG)
	{
		debug_camera_.Init(play_camera_.GetPos(), play_camera_.GetFocus());
	}
}



void CCameraManager::SetNearFar(float near_val, float far_val)
{
	SetCameraNearFar(near_val, far_val);
}
