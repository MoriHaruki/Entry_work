#include "KeyInput.h"

void CInputKeyBoard::Update()
{
	//�O�t���[�����L�^
	for (int key_index = 0; key_index < DEVICE::KEY_BUF_LEN; ++key_index) {
		pre_key_buf_[key_index] = current_key_buf_[key_index];
	}

	//���݂̃L�[�����擾
	GetHitKeyStateAll(current_key_buf_);
}

bool CInputKeyBoard::IsPush(int key_code)
{
	//�͈͊O���l�m�F���Q�[����~
#ifdef DEBUG_MODE
	assert(key_code > -1 && key_code < DEVICE::KEY_BUF_LEN);
#endif // DEBUG_MODE

	//�O�t�����O�A���t�����P
	return (pre_key_buf_[key_code] == 0 && current_key_buf_[key_code] == 1);
}

bool CInputKeyBoard::IsKeep(int key_code)
{
	//�͈͊O���l�m�F���Q�[����~
#ifdef DEBUG_MODE
	assert(key_code > -1 && key_code < DEVICE::KEY_BUF_LEN);
#endif // DEBUG_MODE

	//�O�t�����P�A���t�����P
	return (pre_key_buf_[key_code] == 1 && current_key_buf_[key_code] == 1);
}

bool CInputKeyBoard::IsRelease(int key_code)
{
	//�͈͊O���l�m�F���Q�[����~
#ifdef DEBUG_MODE
	assert(key_code > -1 && key_code < DEVICE::KEY_BUF_LEN);
#endif // DEBUG_MODE

	//�O�t�����P�A���t�����O
	return (pre_key_buf_[key_code] == 1 && current_key_buf_[key_code] == 0);
}

bool CInputKeyBoard::IsDown(int key_code)
{
	//�͈͊O���l�m�F���Q�[����~
#ifdef DEBUG_MODE
	assert(key_code > -1 && key_code < DEVICE::KEY_BUF_LEN);
#endif // DEBUG_MODE

	//���t�����P
	return (current_key_buf_[key_code] == 1);
}
