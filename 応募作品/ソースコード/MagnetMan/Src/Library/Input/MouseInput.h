#pragma once

#include "Input.h"

// マウス入力管理クラス
class CInputMouse : public CInputDeviceBase {
private:
	// 更新処理
	void Update() override;

private:
	// 入力関連
	// 今押された
	bool IsPush(int key_code) override;

	// 押し続けている
	bool IsKeep(int key_code) override;

	// 今離した
	bool IsRelease(int key_code) override;

	// 押されている
	bool IsDown(int key_code) override;

public: // アクセサ

	// マウスポインタ座標取得
	inline Vector2D GetPointer() const { return pointer_; }

	// マウスポインタ移動量取得
	inline Vector2D GetPointerMove() const { return move_; }

	// マウスポインタを固定しているか
	inline bool IsBoundMousePointer() const { return is_bound_pointer_; }

	// マウスポインタを固定する
	inline void BoundMousePointer() { is_bound_pointer_ = true; }

	// マウスポインタの固定を解除する
	inline void LiberationMousePointer() { is_bound_pointer_ = false; }

	// マウスホイール回転判定関数
	// 手前に回したか
	inline bool IsMouseWheelBack() const { return wheel_rot_ < 0.f; }

	// 奥に回したか
	inline bool IsMouseWheelFront() const { return wheel_rot_ > 0.f; }

	// マウスの移動量を計算しているか
	inline bool IsCalcMousePointerMove() const { return is_move_calc_; }

	// マウスの移動量を計算する
	inline void CalcMousePointerMove() { is_move_calc_ = true; }

	// マウスの移動量を計算しない
	inline void NotCalcMousePointerMove() { is_move_calc_ = false; }

private:
	// Inputでのみ生成可能
	friend class CInput;

	CInputMouse()
		: current_buf_()
		, pre_buf_()
		, wheel_rot_(0.f)
		, pointer_()
		, move_()
		, is_bound_pointer_(true)
		, is_move_calc_(true)
	{}
	~CInputMouse(){}

private:
	// 現在のボタン情報
	bool current_buf_[DEVICE::MOUSE_BUF_LEN];

	// 前フレのボタン情報
	bool pre_buf_[DEVICE::MOUSE_BUF_LEN];

	// マウスホイール回転量
	float wheel_rot_;

	// マウス座標
	Vector2D pointer_;

	// マウス移動量
	Vector2D move_;

	// マウス座標を固定するか
	bool is_bound_pointer_;

	// マウスの移動量を計算するか
	bool is_move_calc_;
};