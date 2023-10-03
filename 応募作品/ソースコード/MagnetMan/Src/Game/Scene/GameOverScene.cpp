#include "GameOverScene.h"
#include "SceneParameter.h"
#include "Input/GameInputParameter.h"
#include "Input/InputManager.h"
#include "Scene/SceneManager.h"
#include "Sound/SoundManager.h"
#include "Fade/Fade.h"
#include "GameUI/GameUIManager.h"
#include "GameUI/GameUIParameter.h"
#include "GameUI/GameUIAnimation.h"
#include "Field/FieldManager.h"
#include"Object/Player/PlayerManager.h"

using namespace GAME_INPUT::ACTION;
using namespace GAMEOVER;

CGameOver::CGameOver()
{
}

CGameOver::~CGameOver()
{
}

void CGameOver::Init()
{
	TheGameUIManager;
}

void CGameOver::Load()
{
	CSoundManager::Load(SOUND_GROUP_GAMEOVER);
	//UI¶¬
	TheGameUIManager->CreateUI(UI_TYPE_SPRITE, 0, 0, "Data/Image/Wall/GameOver.png");
	TheGameUIManager->CreateUI(UI_TYPE_SPRITE, PRESS_B_KEY_POS_X, PRESS_B_KEY_POS_Y, "Data/Image/UI/Title/Key_B_UI.png");
}

void CGameOver::OnLoadEnd()
{
	CFade::FadeIn(FADEIN_TIME);
	state_ = SCENE_STATE_FADEIN;
	// BGMÄ¶
	CSoundManager::PlayBGM(SOUND_ID_BGM_GAMEOVER_SCENE);
}

void CGameOver::Step()
{
	CScene::Step();

	//Bƒ{ƒ^ƒ“‚ÅˆÚ“®
	if (CFade::IsFadeEnd() && TheGameInputManager->IsKeep("OK"))
	{
		CSoundManager::PlaySE(SOUND_ID_SE_CLICK_ENTER);
		ChangeScene(SCENE_ID_TITLE);
	}
}

void CGameOver::Update()
{
}

void CGameOver::Draw()
{
	TheGameUIManager->Draw();
}

void CGameOver::Fin()
{
	TheGameUIManager->DeleteAll();
	GameUIManagerInstance::Delete();
	CSoundManager::DeleteSound(SOUND_GROUP_GAMEOVER);
}
