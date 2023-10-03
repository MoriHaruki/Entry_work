#include "InputManager.h"
#include "MouseInput.h"

namespace {
	constexpr char DEFAULT_INPUT_FILE[] = "Data/Binary/Input/DefaultInput.bin";		// �f�t�H���g�C���v�b�g�f�[�^
	constexpr char CUSTOM_INPUT_FILE[] = "Data/Binary/Input/CustomInput.bin";		// �J�X�^���C���v�b�g�f�[�^

	const char* MOUSE_WHEEL_STATE[] = {
		"Front",	// ���ɉ�
		"Back",		// ��O�ɉ�
	};
}

void CGameInputManager::Init()
{
	// �C���v�b�g�N���X����
	input_ = CreateInput();

	// �C���v�b�g������
	input_->Init();

	for (int stick_index = 0; stick_index < static_cast<int>(GAME_INPUT::STICK::Kind::NUM); ++stick_index) {
		// �X�e�B�b�N�}�b�v������
		input_action_map_.stick_map[GAME_INPUT::STICK::ACTION_NAME[stick_index]]
			= GAME_INPUT::STICK::DEFAULT_STICK[stick_index];
	}

	for (int key_index = 0; key_index < static_cast<int>(GAME_INPUT::ACTION::Kind::NUM); ++key_index) {
		// ���̓A�N�V�����}�b�v������
		input_action_map_.action_map[GAME_INPUT::ACTION::ACTION_NAME[key_index]]
			= GAME_INPUT::ACTION::DEFAULT_INPUT[key_index];
	}

	// �ꎞ�ۑ��}�b�v�ɑ������
	temp_action_map_ = input_action_map_;
}

void CGameInputManager::Step()
{
	// �C���v�b�g�X�e�b�v
	input_->Step();

	// �O�t���̉�����Ԃ�ۑ�
	pre_state_ = current_state_;

	// ���ꂼ��̃A�N�V�������Ɋ��蓖�����Ă���S�Ă̓��͂��`�F�b�N
	for (const auto& map_info : input_action_map_.action_map) {
		bool is_pressed = false;
		for (const auto& input_info : map_info.second) {
			// �L�[�{�[�h
			if (input_info.kind == DeviceKind::KEYBOARD) {
				// ������Ă��邩
				if (input_->IsDown(input_info.code, DeviceKind::KEYBOARD)) {
					// �������Ă�����true
					is_pressed = true;

					// ���[�v�𔲂���
					break;
				}
			}
			// �p�b�h
			if (input_info.kind == DeviceKind::PAD) {
				// ������Ă��邩
				if (input_->IsDown(input_info.code, DeviceKind::PAD)) {
					// �������Ă�����true
					is_pressed = true;

					// ���[�v�𔲂���
					break;
				}
			}
			// �}�E�X
			if (input_info.kind == DeviceKind::MOUSE) {
				// ������Ă��邩
				if (input_->IsDown(input_info.code, DeviceKind::MOUSE)) {
					// �������Ă�����true
					is_pressed = true;

					// ���[�v�𔲂���
					break;
				}
			}
		}
		// ���݂̏�Ԃ���
		current_state_[map_info.first] = is_pressed;
	}
}

void CGameInputManager::Fin()
{
	// �C���v�b�g�̌㏈��
	input_->Fin();

	// �C���v�b�g�|�C���^�̍폜
	delete(input_);
}

bool CGameInputManager::IsPush(const std::string& action)
{
	// �A�N�V�����}�b�v�T��
	auto pre = pre_state_.find(action);

	// ����`�̃{�^�����������疳������false��Ԃ�
	if (pre == pre_state_.end()) { return false; }

	// �A�N�V�����}�b�v�T��
	auto current = current_state_.find(action);

	// ����`�̃{�^�����������疳������false��Ԃ�
	if (current == current_state_.end()) { return false; }

	return !pre->second && current->second;
}

bool CGameInputManager::IsPush(const char* action)
{
	const std::string Action = std::string(action);

	return IsPush(Action);
}

bool CGameInputManager::IsKeep(const std::string& action)
{
	// �A�N�V�����}�b�v�T��
	auto pre = pre_state_.find(action);

	// ����`�̃{�^�����������疳������false��Ԃ�
	if (pre == pre_state_.end()) { return false; }

	// �A�N�V�����}�b�v�T��
	auto current = current_state_.find(action);

	// ����`�̃{�^�����������疳������false��Ԃ�
	if (current == current_state_.end()) { return false; }

	return pre->second && current->second;
}

bool CGameInputManager::IsKeep(const char* action)
{
	const std::string Action = std::string(action);

	return IsKeep(Action);
}

bool CGameInputManager::IsRelease(const std::string& action)
{
	// �A�N�V�����}�b�v�T��
	auto pre = pre_state_.find(action);

	// ����`�̃{�^�����������疳������false��Ԃ�
	if (pre == pre_state_.end()) { return false; }

	// �A�N�V�����}�b�v�T��
	auto current = current_state_.find(action);

	// ����`�̃{�^�����������疳������false��Ԃ�
	if (current == current_state_.end()) { return false; }

	return pre->second && !current->second;
}

bool CGameInputManager::IsRelease(const char* action)
{
	const std::string Action = std::string(action);

	return IsRelease(Action);
}

bool CGameInputManager::IsDown(const std::string& action)
{
	// �A�N�V�����}�b�v�T��
	auto current = current_state_.find(action);

	// ����`�̃{�^�����������疳������false��Ԃ�
	if (current == current_state_.end()) { return false; }

	return current->second;
}

bool CGameInputManager::IsDown(const char* action)
{
	const std::string Action = std::string(action);

	return IsDown(Action);
}

bool CGameInputManager::IsMouseWheelState(const std::string& action)
{
	// �}�E�X�擾
	CInputMouse* mouse = input_->GetMouseInput();

	// ���ɉ񂵂Ă����񂩎�O�ɉ񂵂Ă����񂩂𔻒f����


	// ��`���Ă��Ȃ������񂪗�����A��������false
	return false;
}

Stick CGameInputManager::GetStickActionCode(const std::string& action) const
{
	// ������T��
	auto stick = input_action_map_.stick_map.find(action);

	// ����`�̓��삪������
	if (stick == input_action_map_.stick_map.end()) {
		return Stick::NONE;
	}

	// �X�e�B�b�N�R�[�h��Ԃ�
	return stick->second;
}

// ���͂��ꎞ�I�ɏ���������
void CGameInputManager::RewriteInputAction(const std::string& action, const InputMapInfo& info)
{
	auto& table = temp_action_map_.action_map[action];
	bool is_hit = false;
	for (auto& elem : table) {
		// ��v������̓^�C�v����������
		if (elem.kind == info.kind) {
			elem.code = info.code;
			return;
		}
		// ��v���錟���^�C�v������������A�V�����ǉ�
		table.emplace_back(info);
	}
}

int CGameInputManager::GetInputActionButtonCode(const std::string& action, DeviceKind device)
{
	// ������T��
	auto input_action = input_action_map_.action_map.find(action);

	// ����`�̓��삪������
	if (input_action == input_action_map_.action_map.end()) {
		// -1��Ԃ�
		return -1;
	}

	// �T��
	for (auto& elem : input_action->second) {
		// �Ή�����f�o�C�X��T��
		if (elem.kind == device) {
			// �R�[�h��Ԃ�
			return elem.code;
		}
	}

	// �����܂ŗ�����f�o�C�X���Ή����Ă��Ȃ��̂ŁA-1
	return -1;
}
