
#pragma once

#include "InputParameter.h"
#include "Vector/MyLibData.h"
#include <vector> 

// インプットクラス前方宣言
class CInputKeyBoard;
class CInputMouse;
class CInputPad;

class CInput
{
	// コンストラクタ、デストラクタ
public:
	CInput() {}
	~CInput() {}

public:
	// 初期化
	void Init();

	// 通常処理
	void Step();

	// 後処理
	void Fin();

public:
	// 入力情報取得

	// 押した瞬間
	bool IsPush(const int& key_code, const DeviceKind& device_kind);

	// 押し続けている
	bool IsKeep(const int& key_code, const DeviceKind& device_kind);

	// 離した瞬間
	bool IsRelease(const int& key_code, const DeviceKind& device_kind);

	// 今押されているか
	bool IsDown(const int& key_code, const DeviceKind& device_kind);

public: // アクセサ
	//キーボードラスポインタを取得
	CInputKeyBoard* GetKeyBoardInput();

	// マウスクラスポインタを取得
	CInputMouse* GetMouseInput();

	// パッドクラスポインタを取得
	CInputPad* GetPadInput();

private:
	// 入力機器情報
	std::vector<CInputDeviceBase*> device_;
};