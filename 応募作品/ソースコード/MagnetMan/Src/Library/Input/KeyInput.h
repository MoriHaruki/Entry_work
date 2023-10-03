#pragma once

#include "Input.h"
#include "InputParameter.h"

// キーボード入力管理クラス
class CInputKeyBoard : public CInputDeviceBase {


private:
	// 更新処理
	void Update() override;

private:
	//入力関連
	bool IsPush(int key_code) override;
	bool IsKeep(int key_code) override;
	bool IsRelease(int key_code) override;
	bool IsDown(int key_code) override;
private:
	// Inputでのみ生成可能
	friend class CInput;

	CInputKeyBoard()
		: current_key_buf_()
		, pre_key_buf_()
	{}
	~CInputKeyBoard() {}

private:
	// 現在のキー情報
	char current_key_buf_[DEVICE::KEY_BUF_LEN];
	// 前フレのキー情報
	char pre_key_buf_[DEVICE::KEY_BUF_LEN];
};