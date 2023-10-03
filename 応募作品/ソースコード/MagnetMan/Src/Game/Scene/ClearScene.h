#pragma once
#include "Scene.h"
#include"../GameUI/GameUI.h"

namespace CLEAR
{
	const float LOGO_POS_X = 250.0f;			//タイトルロゴｘ座標
	const float LOGO_POS_Y = 60.0f;				//タイトルロゴｙ座標
	const float LOGO_FLOATING_SPEED = 0.03f;	//タイトルロゴ上下浮遊速度
	const float LOGO_FLOATING_SIZE = 10.0f;		//タイトルロゴ上下浮遊幅
	const float PRESS_B_KEY_POS_X = 350.0;		//プレイシーンへの入力ガイドｘ座標
	const float PRESS_B_KEY_POS_Y = 420.0f;		//プレイシーンへの入力ガイドｙ座標
	const float PRESS_Z_KEY_BLINK_SPEED = 0.02f;//プレイシーンへの入力ガイド点滅速度
}

class Clear :public CScene
{
public:
	Clear();
	virtual ~Clear();
public:
	void Init()			override;
	void Load()			override;
	void OnLoadEnd()	override;
	void Step()			override;
	void Update()		override;
	void Draw()			override;
	void Fin()			override;
};