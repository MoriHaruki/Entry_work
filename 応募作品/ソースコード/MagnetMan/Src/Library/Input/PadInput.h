#pragma once

#include "Input.h"
#include "../Vector/Vector3D.h"

// パッド入力管理クラス
class CInputPad : public CInputDeviceBase {
private:
	// 更新処理
	void Update() override;

private:
	// Inputでのみ生成可能
	friend class CInput;

	CInputPad()
		: current_pad_state_()
		, pre_pad_state_()
		, is_connect_(false)
	{}
	~CInputPad() {}

private: // 入力関連

	// 今押された
	bool IsPush(int key_code) override;

	// 押し続けている
	bool IsKeep(int key_code) override;

	// 今離した
	bool IsRelease(int key_code) override;

	// 押されている
	bool IsDown(int key_code) override;

public:
	/*
		ジョイパッドを振動させる
		引数：	time		:	振動させる時間(秒)
				power		:	振動の強さ(振動タイプのenum classを参照)
				pad_type	:	振動させたいパッド

		基本的には引数なしで使える
		詳細に設定したい場合は引数で設定する
		強さを指定したい場合は0～1000までの値で設定する(範囲外の値を渡しても範囲内にキャストされる)
	*/
	void PadVibration(double time = 1.0, Vibration power = Vibration::_3, int pad_type = DX_INPUT_PAD1);
	/*
		ジョイパッドスティックの入力方向を取得(2Dベクトル)
		引数：		stick	:	左右のスティックのどちらの入力を返すか(stickのenum class参照)
		戻り値	:	ゼロベクトルが返ってきたら入力していない

		返ってくるベクトルは単位ベクトルになっているので、使うときには戻り値のベクトルをスケール倍して使う
	*/
	Vector2D StickDir2D(const Stick& stick);
	/*
		ジョイパッドスティックの入力方向を取得(3Dベクトル)
		引数：		stick	:	左右のスティックのどちらの入力を返すか(stickのenum class参照)
		戻り値	:	ゼロベクトルが返ってきたら入力していない

		返ってくるベクトルは単位ベクトルになっているので、使うときには戻り値のベクトルをスケール倍して使う
	*/
	Vector3D StickDir3D(const Stick& stick);
	/*
		ジョイパッドのスティックが正面方向を正の向きをしたときに、どのくらい角度があるのかを取得
		引数：	dimention	:	2Dベクトルか3Dベクトルか(ベクトルタイプのenum class参照)
				stick		:	左右のスティックのどちらの入力を返すか(stickのenum class参照)
	*/
	float StickAngle(const Vector& vec, const Stick& stick);

private:
	// 現在のパッド情報
	XINPUT_STATE current_pad_state_;
	// 前フレのパッド情報
	XINPUT_STATE pre_pad_state_;
	// パッド接続確認フラグ
	bool is_connect_;
};