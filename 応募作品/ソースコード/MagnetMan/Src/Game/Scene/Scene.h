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

	//初期化
	virtual void Init() = 0;

	//ロード
	virtual void Load() = 0;

	//ロード完了
	virtual void OnLoadEnd() = 0;

	//ステップ処理
	virtual void Step();

	//更新処理
	virtual void Update() = 0;

	//描画
	virtual void Draw() = 0;

	//後処理
	virtual void Fin() = 0;

protected:
	void ChangeScene(int next_scene, int fade_time = 60);
	virtual void OnFadeinEnd();

protected:
	int state_;

private:
	int next_scene_;
};