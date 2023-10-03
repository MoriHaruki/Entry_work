#pragma once

#include "Singleton/Singleton.h"
#include "Scene.h"
#include "Common.h"

//インスタンスへのマクロアクセス
#define SceneManagerInstance MyLib::Singleton<CSceneManager>
//インスタンス呼び出し簡略化
#define TheSceneManager MyLib::Singleton<CSceneManager>::Get()

class CSceneManager
{
private:
	//アクセス権限付与
	friend MyLib::Singleton<CSceneManager>;

private:
	CSceneManager();
	~CSceneManager();

public:
	//初期化
	void Init();

	//ループ
	void Loop();

	//後処理
	void Fin();

	//１番最初のシーンを開始する
	void StartFirstScene(int sceneID);

	//引数のシーンに変更する
	void ChangeScene(int sceneID);

	// 現在のシーンを取得する
	CScene* GetNowScene() const { return scene_; }
	//現在シーンのIDを獲得する
	int GetCurrentSceneID() const { return current_scene_id_; }

private:
	//シーンを生成する
	void CreateScene(int sceneID);
	//次の画面に遷移させる
	void ChangeNextScene();
	// シーンループ中の各関数
	void SceneInit();
	void SceneLoad();
	void SceneLoadEnd();
	void SceneLoop();
	void SceneFin();

private:
	//現在のシーンID
	int current_scene_id_;
	int next_scene_id_;
	int current_scene_state_;

	//基底ポインタ１つで管理する
	CScene* scene_;
};