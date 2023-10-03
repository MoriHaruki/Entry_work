#pragma once

#include "Input.h"

// �}�E�X���͊Ǘ��N���X
class CInputMouse : public CInputDeviceBase {
private:
	// �X�V����
	void Update() override;

private:
	// ���͊֘A
	// �������ꂽ
	bool IsPush(int key_code) override;

	// ���������Ă���
	bool IsKeep(int key_code) override;

	// ��������
	bool IsRelease(int key_code) override;

	// ������Ă���
	bool IsDown(int key_code) override;

public: // �A�N�Z�T

	// �}�E�X�|�C���^���W�擾
	inline Vector2D GetPointer() const { return pointer_; }

	// �}�E�X�|�C���^�ړ��ʎ擾
	inline Vector2D GetPointerMove() const { return move_; }

	// �}�E�X�|�C���^���Œ肵�Ă��邩
	inline bool IsBoundMousePointer() const { return is_bound_pointer_; }

	// �}�E�X�|�C���^���Œ肷��
	inline void BoundMousePointer() { is_bound_pointer_ = true; }

	// �}�E�X�|�C���^�̌Œ����������
	inline void LiberationMousePointer() { is_bound_pointer_ = false; }

	// �}�E�X�z�C�[����]����֐�
	// ��O�ɉ񂵂���
	inline bool IsMouseWheelBack() const { return wheel_rot_ < 0.f; }

	// ���ɉ񂵂���
	inline bool IsMouseWheelFront() const { return wheel_rot_ > 0.f; }

	// �}�E�X�̈ړ��ʂ��v�Z���Ă��邩
	inline bool IsCalcMousePointerMove() const { return is_move_calc_; }

	// �}�E�X�̈ړ��ʂ��v�Z����
	inline void CalcMousePointerMove() { is_move_calc_ = true; }

	// �}�E�X�̈ړ��ʂ��v�Z���Ȃ�
	inline void NotCalcMousePointerMove() { is_move_calc_ = false; }

private:
	// Input�ł̂ݐ����\
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
	// ���݂̃{�^�����
	bool current_buf_[DEVICE::MOUSE_BUF_LEN];

	// �O�t���̃{�^�����
	bool pre_buf_[DEVICE::MOUSE_BUF_LEN];

	// �}�E�X�z�C�[����]��
	float wheel_rot_;

	// �}�E�X���W
	Vector2D pointer_;

	// �}�E�X�ړ���
	Vector2D move_;

	// �}�E�X���W���Œ肷�邩
	bool is_bound_pointer_;

	// �}�E�X�̈ړ��ʂ��v�Z���邩
	bool is_move_calc_;
};