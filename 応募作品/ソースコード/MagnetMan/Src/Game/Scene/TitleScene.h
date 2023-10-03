#pragma once

#include "Scene.h"
#include "GameUI/GameUI.h"

namespace TITLE
{
	const float LOGO_POS_X = 250.0f;			//タイトルロゴｘ座標
	const float LOGO_POS_Y = 60.0f;				//タイトルロゴｙ座標
	const float LOGO_FLOATING_SPEED = 0.03f;	//タイトルロゴ上下浮遊速度
	const float LOGO_FLOATING_SIZE = 10.0f;		//タイトルロゴ上下浮遊幅
	const float PRESS_B_KEY_POS_X = 350.0;		//プレイシーンへの入力ガイドｘ座標
	const float PRESS_B_KEY_POS_Y = 420.0f;		//プレイシーンへの入力ガイドｙ座標
	const float PRESS_Z_KEY_BLINK_SPEED = 0.02f;//プレイシーンへの入力ガイド点滅速度
}

class CTitle : public CScene {

public:
	CTitle();
	virtual ~CTitle();

public:
	void Init()			override;	//初期化
	void Load()			override;	//読み込み
	void OnLoadEnd()	override;	//読み込み終了
	void Step()			override;	//通常
	void Update()		override;	//更新
	void Draw()			override;	//描画
	void Fin()			override;	//後処理
};
