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

//初期化
void CSceneManager::Init()
{
	CFade::Init();
}

//ループ
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

// シーンループ中の各関数
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

//後処理
void CSceneManager::Fin()
{
	if (scene_) {
		scene_->Fin();
		delete scene_;
		scene_ = nullptr;
	}
}

//１番最初のシーンを開始する
void CSceneManager::StartFirstScene(int sceneID)
{
	//既に何かシーンが動いてるのであれば即終了
	if (scene_) return;

	//シーンを生成して初期化から開始する
	CreateScene(sceneID);
	current_scene_id_ = sceneID;
	current_scene_state_ = SCENE_STATE_INIT;
}

//引数のシーンに変更する
void CSceneManager::ChangeScene(int sceneID)
{
	//次に遷移するシーンを覚えておき、終了処理へ
	next_scene_id_ = sceneID;
	current_scene_state_ = SCENE_STATE_FIN;
}

//シーンを生成する
void CSceneManager::CreateScene(int sceneID)
{
	//シーンを生成
	switch (sceneID)
	{
	case SCENE_ID_TITLE: scene_ = NEW CTitle; break;
	case SCENE_ID_PLAY: scene_ = NEW CPlay; break;
	case SCENE_ID_CLEAR: scene_ = NEW Clear; break;
	case SCENE_ID_GAMEOVER: scene_ = NEW CGameOver; break;
	default:								break;
	}
}

//次のシーンに遷移する
void CSceneManager::ChangeNextScene()
{
	//終了したシーンを削除
	delete scene_;
	scene_ = nullptr;
	//次のシーンを生成
	CreateScene(next_scene_id_);
	//現在のシーンID設定
	current_scene_id_ = next_scene_id_;
	//状態を初期化に戻す
	current_scene_state_ = SCENE_STATE_INIT;
}