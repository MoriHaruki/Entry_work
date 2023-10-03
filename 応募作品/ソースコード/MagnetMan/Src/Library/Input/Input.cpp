#include "Input.h"
#include "../Input/KeyInput.h"
#include "../Input/MouseInput.h"
#include "../Input/PadInput.h"

void CInput::Init()
{
	// 必要なインプットクラスを追加
	device_.emplace_back(NEW CInputKeyBoard);
	device_.emplace_back(NEW CInputMouse);
	device_.emplace_back(NEW CInputPad);
}

void CInput::Step()
{
	for (auto device : device_)
	{
		// 更新処理
		device->Update();
	}
}

void CInput::Fin()
{
	for (auto device : device_)
	{
		// インプットクラス削除
		delete(device);
	}

	// リストクリア
	device_.clear();
	device_.shrink_to_fit();
}

bool CInput::IsPush(const int& key_code, const DeviceKind& device_kind)
{
	// 入力機器取得
	int kind = static_cast<int>(device_kind);

	return device_[kind]->IsPush(key_code);
}

bool CInput::IsKeep(const int& key_code, const DeviceKind& device_kind)
{
	// 入力機器取得
	int kind = static_cast<int>(device_kind);

	return device_[kind]->IsKeep(key_code);
}

bool CInput::IsRelease(const int& key_code, const DeviceKind& device_kind)
{
	// 入力機器取得
	int kind = static_cast<int>(device_kind);

	return device_[kind]->IsRelease(key_code);
}

bool CInput::IsDown(const int& key_code, const DeviceKind& device_kind)
{
	// 入力機器取得
	int kind = static_cast<int>(device_kind);

	return device_[kind]->IsDown(key_code);
}

CInputKeyBoard* CInput::GetKeyBoardInput()
{
	int keyboard = static_cast<int>(DeviceKind::KEYBOARD);
	return static_cast<CInputKeyBoard*>(device_[keyboard]);
}

CInputMouse* CInput::GetMouseInput()
{
	int mouse = static_cast<int>(DeviceKind::MOUSE);
	return static_cast<CInputMouse*>(device_[mouse]);
}

CInputPad* CInput::GetPadInput()
{
	int pad = static_cast<int>(DeviceKind::PAD);
	return static_cast<CInputPad*>(device_[pad]);
}
