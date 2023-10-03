#pragma once

#include "Scene.h"

class CPlay : public CScene {
public:
	CPlay();
	virtual ~CPlay();
public:
	void Init()			override;	//初期化
	void Load()			override;	//読み込み
	void OnLoadEnd()	override;	//読み込み終了
	void Step()			override;	//通常
	void Update()		override;	//更新
	void Draw()			override;	//描画
	void Fin()			override;	//後処理

private:
	void InitBullet();		//弾		初期化
	void InitPlayer();		//プレイヤー初期化
	void InitEnemy();		//エネミー	初期化
	void InitBox();			//箱オブジェ初期化
	void InitObstacles();	//障害物	初期化
	void InitStage();		//ステージ	初期化
	void InitCamera();		//カメラ	初期化
	void InitEffect();		//エフェクト初期化
	void InitCollision();	//当たり判定初期化
	void InitSky();			//天球		初期化	

	void LoadBullet();		//弾		読み込み
	void LoadPlayer();		//プレイヤー読み込み
	void LoadBox();			//箱オブジェ読み込み
	void LoadObstacles();	//障害物	読み込み
	void LoadEffect();		//エフェクト読み込み
	void LoadSound();		//サウンド	読み込み
	void LoadSky();			//天球		読み込み
	void LoadField();		//フィールド読み込み
};