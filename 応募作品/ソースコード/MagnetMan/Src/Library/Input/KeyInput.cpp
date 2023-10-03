#include "KeyInput.h"

void CInputKeyBoard::Update()
{
	//前フレーム情報記録
	for (int key_index = 0; key_index < DEVICE::KEY_BUF_LEN; ++key_index) {
		pre_key_buf_[key_index] = current_key_buf_[key_index];
	}

	//現在のキー情報を取得
	GetHitKeyStateAll(current_key_buf_);
}

bool CInputKeyBoard::IsPush(int key_code)
{
	//範囲外数値確認時ゲーム停止
#ifdef DEBUG_MODE
	assert(key_code > -1 && key_code < DEVICE::KEY_BUF_LEN);
#endif // DEBUG_MODE

	//前フレ＝０、現フレ＝１
	return (pre_key_buf_[key_code] == 0 && current_key_buf_[key_code] == 1);
}

bool CInputKeyBoard::IsKeep(int key_code)
{
	//範囲外数値確認時ゲーム停止
#ifdef DEBUG_MODE
	assert(key_code > -1 && key_code < DEVICE::KEY_BUF_LEN);
#endif // DEBUG_MODE

	//前フレ＝１、現フレ＝１
	return (pre_key_buf_[key_code] == 1 && current_key_buf_[key_code] == 1);
}

bool CInputKeyBoard::IsRelease(int key_code)
{
	//範囲外数値確認時ゲーム停止
#ifdef DEBUG_MODE
	assert(key_code > -1 && key_code < DEVICE::KEY_BUF_LEN);
#endif // DEBUG_MODE

	//前フレ＝１、現フレ＝０
	return (pre_key_buf_[key_code] == 1 && current_key_buf_[key_code] == 0);
}

bool CInputKeyBoard::IsDown(int key_code)
{
	//範囲外数値確認時ゲーム停止
#ifdef DEBUG_MODE
	assert(key_code > -1 && key_code < DEVICE::KEY_BUF_LEN);
#endif // DEBUG_MODE

	//現フレ＝１
	return (current_key_buf_[key_code] == 1);
}
