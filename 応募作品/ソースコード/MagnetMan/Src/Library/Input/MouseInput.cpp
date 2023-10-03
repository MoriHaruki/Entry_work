#include "MouseInput.h"
#include <cassert>
#include "Common.h"

void CInputMouse::Update()
{
	// マウスポインター座標関連更新
	{
		// 一旦保存する
		Vector2D pre(pointer_);
		int current_x, current_y;
		GetMousePoint(&current_x, &current_y);
		pointer_.x = static_cast<float>(current_x);
		pointer_.y = static_cast<float>(current_y);

		// 移動量算出
		if (!is_move_calc_) {
			move_(0.f);
		}
		// 画面外なら移動量ゼロ
		else if (pointer_.x < 0.f || pointer_.x > CCommon::WINDOW_W ||
			pointer_.y < 0.f || pointer_.y > CCommon::WINDOW_H) {
			move_(0.f);
		}
		else {
			move_ = pointer_.Create(pre);
		}

		// マウスポインターを固定する
		if (is_bound_pointer_)
			SetMousePoint(static_cast<int>(DEVICE::MOUSE_SET_POS.x), static_cast<int>(DEVICE::MOUSE_SET_POS.y));
	}

	//前フレームの情報記録
	memcpy(pre_buf_, current_buf_, sizeof(pre_buf_));

	//現在のキー情報を取得
	{
		int mouse_input = GetMouseInput(), mouse_index = 0;

		for (auto& mouse : current_buf_) {
			mouse = mouse_input & (1 << mouse_index);
			++mouse_index;
		}
	}

	// マウスホイール回転量取得
	wheel_rot_ = GetMouseWheelRotVolF();
}

bool CInputMouse::IsPush(int key_code)
{
	//範囲外数値確認時ゲーム停止
#ifdef DEBUG_MODE
	assert(key_code == MOUSE_INPUT_LEFT || key_code == MOUSE_INPUT_RIGHT || key_code == MOUSE_INPUT_MIDDLE);
#endif // DEBUG_MODE

	//2で割った商が添え字
	return (!pre_buf_[key_code / 2] && current_buf_[key_code / 2]);
}

bool CInputMouse::IsKeep(int key_code)
{
	//範囲外数値確認時ゲーム停止
#ifdef DEBUG_MODE
	assert(key_code == MOUSE_INPUT_LEFT || key_code == MOUSE_INPUT_RIGHT || key_code == MOUSE_INPUT_MIDDLE);
#endif // DEBUG_MODE

	//2で割った商が添え字
	return (pre_buf_[key_code / 2] && current_buf_[key_code / 2]);
}

bool CInputMouse::IsRelease(int key_code)
{
	//範囲外数値確認時ゲーム停止
#ifdef DEBUG_MODE
	assert(key_code == MOUSE_INPUT_LEFT || key_code == MOUSE_INPUT_RIGHT || key_code == MOUSE_INPUT_MIDDLE);
#endif // DEBUG_MODE

	//2で割った商が添え字
	return (!pre_buf_[key_code / 2] && current_buf_[key_code / 2]);
}

bool CInputMouse::IsDown(int key_code)
{
	//範囲外数値確認時ゲーム停止
#ifdef DEBUG_MODE
	assert(key_code == MOUSE_INPUT_LEFT || key_code == MOUSE_INPUT_RIGHT || key_code == MOUSE_INPUT_MIDDLE);
#endif // DEBUG_MODE

	//2で割った商が添え字
	return current_buf_[key_code / 2];
}
