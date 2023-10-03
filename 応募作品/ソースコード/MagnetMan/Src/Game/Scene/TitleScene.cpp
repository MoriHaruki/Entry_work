#include "TitleScene.h"
#include "SceneParameter.h"
#include "Object/Camera/CameraManager.h"
#include "Input/Input.h"
#include "Input/GameInputParameter.h"
#include "Input/InputManager.h"
#include "Scene/SceneManager.h"
#include "Sound/SoundManager.h"
#include "Fade/Fade.h"
#include "GameUI/GameUIManager.h"
#include "GameUI/GameUIParameter.h"
#include "GameUI/GameUIAnimation.h"
#include "Object/Camera/CameraManager.h"
#include "Object/Obstacles/ObstaclesManager.h"
#include "Object/Box/BoxManager.h"

using namespace GAME_INPUT::ACTION;
using namespace TITLE;

CTitle::CTitle() : CScene()
{
}

CTitle::~CTitle()
{
}

void CTitle::Init()
{
}

void CTitle::Load()
{
	CSoundManager::Load(SOUND_GROUP_TITLE);
	//UIロード
	TheGameUIManager->CreateUI(UI_TYPE_SPRITE, 0, 0, "Data/Image/Wall/title wall.png");
	TheGameUIManager->CreateUI(UI_TYPE_SPRITE, LOGO_POS_X, LOGO_POS_Y, "Data/Image/UI/Title/Title_Logo.png");
	TheGameUIManager->CreateUI(UI_TYPE_SPRITE, PRESS_B_KEY_POS_X, PRESS_B_KEY_POS_Y, "Data/Image/UI/Title/Key_B_UI.png");
}

void CTitle::OnLoadEnd()
{
	// フェードイン
	CFade::FadeIn(FADEIN_TIME);
	state_ = SCENE_STATE_FADEIN;
	// BGM再生
	CSoundManager::PlayBGM(SOUND_ID_BGM_TITLE_SCENE);

	CObstaclesManager::CreatePrototypes();
	CBoxManager::CreatePrototypes();
}

void CTitle::Step()
{
	CScene::Step();

	// フェードインが終わってから入力を受け付ける&&Bボタンで移動
	if (CFade::IsFadeEnd() && TheGameInputManager->IsPush(ACTION_NAME[IInputActionKind::OK]))
	{
		CSoundManager::PlaySE(SOUND_ID_SE_CLICK_ENTER);
		// シーン遷移
		ChangeScene(SCENE_ID_PLAY);
	}
}

void CTitle::Update()
{
}

void CTitle::Draw()
{
	TheGameUIManager->Draw();

}

void CTitle::Fin()
{
	TheGameUIManager->DeleteAll();
	GameUIManagerInstance::Delete();
	CSoundManager::DeleteSound(SOUND_GROUP_TITLE);
}
