
#pragma once

#include "InputParameter.h"
#include "Vector/MyLibData.h"
#include <vector> 

// �C���v�b�g�N���X�O���錾
class CInputKeyBoard;
class CInputMouse;
class CInputPad;

class CInput
{
	// �R���X�g���N�^�A�f�X�g���N�^
public:
	CInput() {}
	~CInput() {}

public:
	// ������
	void Init();

	// �ʏ폈��
	void Step();

	// �㏈��
	void Fin();

public:
	// ���͏��擾

	// �������u��
	bool IsPush(const int& key_code, const DeviceKind& device_kind);

	// ���������Ă���
	bool IsKeep(const int& key_code, const DeviceKind& device_kind);

	// �������u��
	bool IsRelease(const int& key_code, const DeviceKind& device_kind);

	// ��������Ă��邩
	bool IsDown(const int& key_code, const DeviceKind& device_kind);

public: // �A�N�Z�T
	//�L�[�{�[�h���X�|�C���^���擾
	CInputKeyBoard* GetKeyBoardInput();

	// �}�E�X�N���X�|�C���^���擾
	CInputMouse* GetMouseInput();

	// �p�b�h�N���X�|�C���^���擾
	CInputPad* GetPadInput();

private:
	// ���͋@����
	std::vector<CInputDeviceBase*> device_;
};