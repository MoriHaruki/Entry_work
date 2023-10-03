#pragma once
#include "GameInputParameter.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "PadInput.h"
#include "Singleton/Singleton.h"
#include "Common.h"

// �C���X�^���X�ւ̃A�N�Z�X�}�N��
#define GameInputInstance MyLib::Singleton<CGameInputManager>

// �C���X�^���X�Ăяo���ȗ���
#define TheGameInputManager MyLib::Singleton<CGameInputManager>::Get()

/*
	���̃Q�[���ł̃C���v�b�g���Ǘ�����N���X
	�^�C�g����v���C����L�[�R�[�h��ύX�ł���悤�ɂ��邽��
*/
class CGameInputManager {
	// �V���O���g��
private:
	friend MyLib::Singleton<CGameInputManager>;

private: // �����̋֎~

	CGameInputManager()
		: input_(nullptr)
	{}

public: // �W�����\�b�h

	// ������
	void Init();

	// �X�e�b�v
	void Step();

	// �㏈��
	void Fin();

public: // ���͔���

	// �������u��
	bool IsPush(const std::string& action);
	bool IsPush(const char* action);

	// ���������Ă���
	bool IsKeep(const std::string& action);
	bool IsKeep(const char* action);

	// �������u��
	bool IsRelease(const std::string& action);
	bool IsRelease(const char* action);

	// ��������Ă��邩
	bool IsDown(const std::string& action);
	bool IsDown(const char* action);

public: // �L�[�֘A�A�N�Z�T

		// �C���v�b�g���擾
	inline CInput* GetInput() const { return input_; }

	// �L�[���擾
	inline CInputKeyBoard* GetInputKeyBoard() const { return (input_) ? input_->GetKeyBoardInput() : nullptr; }

public: // �}�E�X�֘A�A�N�Z�T

	// �}�E�X�z�C�[���̏�Ԃ��擾����
	bool IsMouseWheelState(const std::string& action);

	// �}�E�X���擾
	inline CInputMouse* GetInputMouse() const { return (input_) ? input_->GetMouseInput() : nullptr; }

public: // �p�b�h�֘A�A�N�Z�T

	// ���̓A�N�V�����ɑ΂���X�e�B�b�N�R�[�h��Ԃ�
	Stick GetStickActionCode(const std::string& action) const;

	// �p�b�h���擾
	inline CInputPad* GetInputPad() const { return (input_) ? input_->GetPadInput() : nullptr; }

public: // ���͏��������p�֐��Q

	// ���͂��ꎞ�I�ɏ���������
	void RewriteInputAction(const std::string& action, const InputMapInfo& info);

	// ���͏㏑��
	inline void Commit() { input_action_map_ = temp_action_map_; }

	// ���͂��f�t�H���g�ɖ߂�
	inline void RollBackDefaultInput() { input_action_map_ = default_action_map_; }

private: // �������\�b�h

	// �C���v�b�g�N���X����
	CInput* CreateInput() { return (input_) ? input_ : input_ = NEW CInput; }

public: // �A�N�Z�T

	// �Q�b�g�֐�
	inline int GetActionNum() const { return static_cast<int>(GAME_INPUT::ACTION::Kind::NUM); }
	inline int GetStickActionNum() const { return static_cast<int>(GAME_INPUT::STICK::Kind::NUM); }
	inline InputStickMap GetInputStickMap() const { return input_action_map_.stick_map; }
	inline InputActionMap GetInputActionMap() const { return input_action_map_.action_map; }

	/*
		�����̃A�N�V�����ɑΉ�����{�^���̃R�[�h��Ԃ�
		�����F	action		:	�A�N�V����
				device		:	�f�o�C�X
		�߂�l�F�{�^���R�[�h(����`�̃A�N�V������f�o�C�X�̃{�^�����ݒ肳��Ă��Ȃ�������-1��Ԃ�)
	*/
	int GetInputActionButtonCode(const std::string& action, DeviceKind device);

private: // �����o�ϐ�

	// �C���v�b�g�N���X�|�C���^
	CInput* input_;

	// ���͂ƃA�N�V�����̑Ή��e�[�u��
	SaveInputData input_action_map_;

	// �L�[���������ꎞ�e�[�u��
	SaveInputData temp_action_map_;

	// �f�t�H���g�L�[�e�[�u��
	SaveInputData default_action_map_;

	// ���݂̉������
	std::map<std::string, bool> current_state_;

	// �O�t���̉������
	std::map<std::string, bool > pre_state_;
};