#include <math.h>
#include "DxLib.h"
#include "Input/InputManager.h"
#include"Collision/CollisionManager.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneParameter.h"
#include "Fade/Fade.h"
//メモリリーク検知用
#ifdef _DEBUG
#include <crtdbg.h>
#endif

//システム情報を取得
SYSTEM_INFO GetSystemInfo() {
	SYSTEM_INFO SystemInfo = { 0 };
	::GetSystemInfo(&SystemInfo);
	return SystemInfo;
}

namespace FRAME_RATE
{
	//フレームレート関連
	int g_nCurrentTime = 0;			//現在の時間
	int g_nLastFrameTime = 0;		//前回のフレーム実行時の時間
	int g_nFrameCnt = 0;			//フレームカウント用
	int g_nUpdateFrameRateTime = 0;	//フレームレートを更新した時間
	float g_fFrameRate = 0.f;		//フレームレート（表示用）
	int SoundHundle = 0;
}

void CalcFrameRate();			//フレームレート計算
void DrawFrameRate();			//フレームレート表示（デバッグ用）
using namespace FRAME_RATE;
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(true);	//ウィンドウの状態を設定する
	//ウィンドウの設定
	SetWindowStyleMode(8);
	SetWindowSizeChangeEnableFlag(TRUE);
	SetWindowSizeExtendRate(0.75f);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);		//NEWによるメモリリーク検知開始
	//DXライブラリの初期化
	if(DxLib_Init() == -1)												
	{
		return -1;
	}
	SetUseASyncLoadFlag(true);
	SetASyncLoadThreadNum(GetSystemInfo().dwNumberOfProcessors);
	SetGraphMode(CCommon::WINDOW_W, CCommon::WINDOW_H, 32);				//ウィンドウサイズを変更
	SetDrawScreen(DX_SCREEN_BACK);										//描画するスクリーンを設定
	SetTransColor(0, 127, 127);											//透過色を設定

	//キー入力初期化
	TheGameInputManager->Init();
	TheGameInputManager->GetInputMouse()->LiberationMousePointer();
	//フェード機能を初期化
	CFade::Init();

	//シーンマネージャクラス生成と初期化
	CSceneManager* scene_manager = TheSceneManager;
	scene_manager->StartFirstScene(SCENE_ID_TITLE);

	//ゲームメインループ
	while(ProcessMessage() != -1)
	{
		Sleep(1);													//システムに処理を返す
		g_nCurrentTime = GetNowCount();								//現在の時刻を取得
		// 現在の時刻が、前回のフレーム時より
		// 1/60秒経過していたら処理を実行する
		if(g_nCurrentTime - g_nLastFrameTime >= 1000 / CCommon::FRAME_RATE)
		{
			g_nLastFrameTime = g_nCurrentTime;						//フレーム実行時の時間を更新
			g_nFrameCnt++;											//フレーム数をカウント
			if(TheGameInputManager->IsPush("ESC"))					//エスケープキーが押されたら終了
			{
				break;
			}
			ClearDrawScreen();										//画面に表示されたものを初期化
			CCommon::Step();											//インプットステップ
			TheGameInputManager->Step();
			CFade::Step();											//フェード通常
			PlaySoundMem(SoundHundle, DX_PLAYTYPE_BACK, true);		//BGM
			CalcFrameRate();										//フレームレート計算
			DrawFrameRate();										//フレームレート表示（デバッグ用）
			scene_manager->Loop();									//シーンの更新
			TheCollisionManager->Draw();
			CFade::Draw();											//フェード描画
			ScreenFlip();											//フリップ関数（ループの終わりに１度だけ行う）

		}
	}

	TheGameInputManager->Fin();
	GameInputInstance::Delete();
	CFade::Fin();													//フェード機能の後処理
	TheSceneManager->Fin();
	SceneManagerInstance::Delete();
	DeleteSoundMem(SoundHundle);									//効果音破棄
	InitGraph();													//使用したすべての画像を破棄
	DxLib_End();													//DXライブラリの後処理
	return 0;
}
//フレームレート計算
void CalcFrameRate()
{
	int nDifTime = g_nCurrentTime - g_nUpdateFrameRateTime;			//前回のフレームレート更新からの経過時間を求める
	if(nDifTime > 1000)												//前回のフレームレート更新から１秒以上経過していたらフレームレートを更新する
	{
		float fFrameCnt = (float)(g_nFrameCnt * 1000);				//フレーム回数をミリ秒に合わせる。　小数まで出したいのでfloatにキャスト
		g_fFrameRate = fFrameCnt / nDifTime;						//フレームレートを求める。　理想どおりなら 60000 / 1000 で 60 となる
		g_nFrameCnt = 0;											//フレームカウントをクリア
		g_nUpdateFrameRateTime = g_nCurrentTime;					//フレームレート更新時間を更新
	}
}
//フレームレート表示（デバッグ用）
void DrawFrameRate()
{
#ifdef DEBUG
	DrawFormatString(180, 100, GetColor(255, 30, 30), "FPS[%.2f]", g_fFrameRate);
#endif

	
}