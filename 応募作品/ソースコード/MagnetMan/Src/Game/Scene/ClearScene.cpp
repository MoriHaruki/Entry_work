#include "ClearScene.h"
#include "SceneParameter.h"
#include "Input/GameInputParameter.h"
#include "Input/InputManager.h"
#include "Scene/SceneManager.h"
#include "Sound/SoundManager.h"
#include "Fade/Fade.h"
#include "GameUI/GameUIManager.h"
#include "GameUI/GameUIParameter.h"
#include "GameUI/GameUIAnimation.h"

using namespace GAME_INPUT::ACTION;
using namespace CLEAR;

Clear::Clear()
{
}

Clear::~Clear()
{
}

void Clear::Init()
{
	TheGameUIManager;
}

void Clear::Load()
{
	CSoundManager::Load(SOUND_GROUP_CLEAR);
	//UIロード
	TheGameUIManager->CreateUI(UI_TYPE_SPRITE, 0, 0, "Data/Image/Wall/GameClear.png");
	TheGameUIManager->CreateUI(UI_TYPE_SPRITE, PRESS_B_KEY_POS_X, PRESS_B_KEY_POS_Y, "Data/Image/UI/Title/Key_B_UI.png");
}

void Clear::OnLoadEnd()
{
	CFade::FadeIn(FADEIN_TIME);
	state_ = SCENE_STATE_FADEIN;
	CSoundManager::PlayBGM(SOUND_ID_BGM_CLEAR_SCENE);
}

void Clear::Step()
{
	CScene::Step();

	//Bボタンで移動
	if (CFade::IsFadeEnd() && TheGameInputManager->IsKeep("OK"))
	{
		CSoundManager::PlaySE(SOUND_ID_SE_CLICK_ENTER);
		ChangeScene(SCENE_ID_TITLE);
	}
}

void Clear::Update()
{
}

void Clear::Draw()
{
	TheGameUIManager->Draw();
}

void Clear::Fin()
{
	TheGameUIManager->DeleteAll();
	GameUIManagerInstance::Delete();
	CSoundManager::DeleteSound(SOUND_GROUP_CLEAR);
}
