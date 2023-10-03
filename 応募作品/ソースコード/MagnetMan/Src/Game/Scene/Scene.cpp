
//SceneBase.cpp
//シーン用基底クラス

#include "Scene.h"
#include "SceneParameter.h"
#include "SceneManager.h"
#include "Fade/Fade.h"


CScene::CScene()
{
	state_ = SCENE_STATE_NONE;
	next_scene_ = -1;
}

CScene::~CScene()
{
}

void CScene::Step()
{
	bool is = CFade::IsFadeEnd();

	if (state_ == SCENE_STATE_FADEIN && is)
	{
		TheSceneManager->GetNowScene()->OnFadeinEnd();
	}
	if (state_ == SCENE_STATE_FADEOUT && is)
	{
		TheSceneManager->ChangeScene(next_scene_);
	}

	//シーンの区別
	switch (TheSceneManager->GetCurrentSceneID())
	{
	case 0: {
		DrawString(0, 50, "Title", GetColor(255, 0, 0));
	}break;
	case 1: {
		DrawString(0, 50, "Play", GetColor(255, 0, 0));
	}break;
	case 2: {
		DrawString(0, 50, "Clear", GetColor(255, 0, 0));
	}
	default:
		break;
	}

}

void CScene::ChangeScene(int next_scene, int fade_time)
{
	next_scene_ = next_scene;
	state_ = SCENE_STATE_FADEOUT;
	CFade::FadeOut(fade_time);
}

void CScene::OnFadeinEnd()
{
	state_ = SCENE_STATE_NONE;
}
