#pragma once

#include "Input.h"
#include "InputParameter.h"

// �L�[�{�[�h���͊Ǘ��N���X
class CInputKeyBoard : public CInputDeviceBase {


private:
	// �X�V����
	void Update() override;

private:
	//���͊֘A
	bool IsPush(int key_code) override;
	bool IsKeep(int key_code) override;
	bool IsRelease(int key_code) override;
	bool IsDown(int key_code) override;
private:
	// Input�ł̂ݐ����\
	friend class CInput;

	CInputKeyBoard()
		: current_key_buf_()
		, pre_key_buf_()
	{}
	~CInputKeyBoard() {}

private:
	// ���݂̃L�[���
	char current_key_buf_[DEVICE::KEY_BUF_LEN];
	// �O�t���̃L�[���
	char pre_key_buf_[DEVICE::KEY_BUF_LEN];
};