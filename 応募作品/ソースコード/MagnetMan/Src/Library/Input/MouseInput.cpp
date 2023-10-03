#include "MouseInput.h"
#include <cassert>
#include "Common.h"

void CInputMouse::Update()
{
	// �}�E�X�|�C���^�[���W�֘A�X�V
	{
		// ��U�ۑ�����
		Vector2D pre(pointer_);
		int current_x, current_y;
		GetMousePoint(&current_x, &current_y);
		pointer_.x = static_cast<float>(current_x);
		pointer_.y = static_cast<float>(current_y);

		// �ړ��ʎZ�o
		if (!is_move_calc_) {
			move_(0.f);
		}
		// ��ʊO�Ȃ�ړ��ʃ[��
		else if (pointer_.x < 0.f || pointer_.x > CCommon::WINDOW_W ||
			pointer_.y < 0.f || pointer_.y > CCommon::WINDOW_H) {
			move_(0.f);
		}
		else {
			move_ = pointer_.Create(pre);
		}

		// �}�E�X�|�C���^�[���Œ肷��
		if (is_bound_pointer_)
			SetMousePoint(static_cast<int>(DEVICE::MOUSE_SET_POS.x), static_cast<int>(DEVICE::MOUSE_SET_POS.y));
	}

	//�O�t���[���̏��L�^
	memcpy(pre_buf_, current_buf_, sizeof(pre_buf_));

	//���݂̃L�[�����擾
	{
		int mouse_input = GetMouseInput(), mouse_index = 0;

		for (auto& mouse : current_buf_) {
			mouse = mouse_input & (1 << mouse_index);
			++mouse_index;
		}
	}

	// �}�E�X�z�C�[����]�ʎ擾
	wheel_rot_ = GetMouseWheelRotVolF();
}

bool CInputMouse::IsPush(int key_code)
{
	//�͈͊O���l�m�F���Q�[����~
#ifdef DEBUG_MODE
	assert(key_code == MOUSE_INPUT_LEFT || key_code == MOUSE_INPUT_RIGHT || key_code == MOUSE_INPUT_MIDDLE);
#endif // DEBUG_MODE

	//2�Ŋ����������Y����
	return (!pre_buf_[key_code / 2] && current_buf_[key_code / 2]);
}

bool CInputMouse::IsKeep(int key_code)
{
	//�͈͊O���l�m�F���Q�[����~
#ifdef DEBUG_MODE
	assert(key_code == MOUSE_INPUT_LEFT || key_code == MOUSE_INPUT_RIGHT || key_code == MOUSE_INPUT_MIDDLE);
#endif // DEBUG_MODE

	//2�Ŋ����������Y����
	return (pre_buf_[key_code / 2] && current_buf_[key_code / 2]);
}

bool CInputMouse::IsRelease(int key_code)
{
	//�͈͊O���l�m�F���Q�[����~
#ifdef DEBUG_MODE
	assert(key_code == MOUSE_INPUT_LEFT || key_code == MOUSE_INPUT_RIGHT || key_code == MOUSE_INPUT_MIDDLE);
#endif // DEBUG_MODE

	//2�Ŋ����������Y����
	return (!pre_buf_[key_code / 2] && current_buf_[key_code / 2]);
}

bool CInputMouse::IsDown(int key_code)
{
	//�͈͊O���l�m�F���Q�[����~
#ifdef DEBUG_MODE
	assert(key_code == MOUSE_INPUT_LEFT || key_code == MOUSE_INPUT_RIGHT || key_code == MOUSE_INPUT_MIDDLE);
#endif // DEBUG_MODE

	//2�Ŋ����������Y����
	return current_buf_[key_code / 2];
}
