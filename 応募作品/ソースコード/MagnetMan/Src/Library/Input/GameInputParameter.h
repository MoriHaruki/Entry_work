#pragma once

#include "InputParameter.h"
#include <map>
#include <string>
#include <vector>
// int�^�L���X�gdefine
#define IInputActionKind (int)GAME_INPUT::ACTION::Kind

/*
	�Q�[���Ŏg���C���v�b�g�p�����[�^
*/

// ���͑Ή��}�b�v���(��̃L�[���Ƃ̏��\����)
struct InputMapInfo {
	InputMapInfo()
		: kind(DeviceKind::NONE)
		, code(0)
	{}
	InputMapInfo(const DeviceKind& device_kind, const int& input_code)
		: kind(device_kind)
		, code(input_code)
	{}

	DeviceKind	kind;	// �f�o�C�X���
	int			code;	// ���̓R�[�h
};

// ���̓A�N�V�����}�b�v�ȗ��\��

typedef std::map<std::string, Stick> InputStickMap;
typedef std::map<std::string, std::vector<InputMapInfo>> InputActionMap;

// �Z�[�u�C���v�b�g�f�[�^
struct SaveInputData {
	SaveInputData()
		: stick_map()
		, action_map()
	{}

	InputStickMap	stick_map;		// �X�e�B�b�N�A�N�V�����}�b�v
	InputActionMap	action_map;		// ���̓A�N�V�����}�b�v
};

namespace GAME_INPUT
{
	namespace STICK
	{
		enum class Kind {
			MOVE,	// �ړ�
			ROT,	// ��]
			NUM,
		};

		static const char* ACTION_NAME[] = {
			"Move",
			"Rot",
		};

		// �f�t�H���g�ړ��X�e�B�b�N
		static Stick DEFAULT_MOVE_STICK = Stick::LEFT;

		// �f�t�H���g���_��]�X�e�B�b�N
		static Stick DEFAULT_ROT_LOOK_STICK = Stick::RIGHT;

		// �f�t�H���g�X�e�B�b�N�A�N�V����
		static Stick DEFAULT_STICK[] = {
			DEFAULT_MOVE_STICK,
			DEFAULT_ROT_LOOK_STICK,
		};
	}

	namespace ACTION
	{
		enum class Kind {
			ESC,				// �����I��
			START_DEBUG_CAMERA,	//�f�o�b�N�J�����N��
			OK,					// ����
			CANCEL,				// �L�����Z��
			FIRE_PLUS_BULLET,	//�v���X�o���b�g����
			FIRE_MINUS_BULLET,	//�}�C�i�X�o���b�g����
			MOVE_FORWARD,		// �O�ړ�
			MOVE_BACK,			// ���ړ�
			MOVE_UP,			// ��ړ�
			MOVE_DOWN,			// ���ړ�
			MOVE_LEFT,			// ���ړ�
			MOVE_RIGHT,			// �E�ړ�
			JUMP,				// �W�����v
			RESTART,			// ���X�^�[�g
			ENTER,				//����
			NUM,
		};

		// �ǉ����������̓A�N�V����������΂����ɒǉ�����
		static const char* ACTION_NAME[] = {
			"ESC",			// �����I��
			"StartDebugCamera",	//�f�o�b�N�J�����N��			
			"OK",			// ����
			"Cancel",		// �L�����Z��
			"FirePlusBullet",	//�v���X�o���b�g����
			"FireMinusBullet",//�}�C�i�X�o���b�g����
			"MoveForward",	// �O�ɐi��
			"MoveBack",		// ���ɐi��
			"MoveUp",		// ��ɐi��
			"MoveDown",		// ���ɐi��
			"MoveLeft",		// ���ɐi��
			"MoveRight",	// �E�ɐi��
			"CursorUp",		// ��
			"CursorDown",	// ��
			"CursorLeft",	// ��
			"CursorRight",	// ��
			"Jump",			// �W�����v
			"Menu",			// ���j���[���J��
			"Enter"			//����

		};

		// �����I���f�t�H���g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_ESC = {
			{ DeviceKind::KEYBOARD, Key::ESC }
		};

		//�f�o�b�N�J����
		static std::vector<InputMapInfo> DEFAULT_INPUT_START_DEBUG_CAMERA = {
			{DeviceKind::KEYBOARD, Key::C}
		};

		// ����f�t�H���g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_OK = {
			{ DeviceKind::KEYBOARD, Key::B }, { DeviceKind::PAD, Pad::B }
		};

		// �L�����Z���f�t�H���g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_CANCEL = {
			{ DeviceKind::KEYBOARD, Key::BACK }, { DeviceKind::PAD, Pad::A }
		};

		//�v���X�o���b�g����
		static std::vector<InputMapInfo> DEFAULT_INPUT_FIRE_PLUS_BULLET = {
			{ DeviceKind::KEYBOARD, Key::K }, { DeviceKind::PAD, Pad::RB }, { DeviceKind::MOUSE, Mouse::RIGHT },
		};

		//�}�C�i�X�o���b�g����
		static std::vector<InputMapInfo> DEFAULT_INPUT_FIRE_MINUS_BULLET = {
			{ DeviceKind::KEYBOARD, Key::J }, { DeviceKind::PAD, Pad::LB }, { DeviceKind::MOUSE, Mouse::RIGHT },
		};

		// �O�ړ��f�t�H���g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_MOVE_FORWARD = {
			{ DeviceKind::KEYBOARD, Key::W  }
		};

		// ���ړ��f�t�H���g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_MOVE_BACK = {
			{ DeviceKind::KEYBOARD, Key::S }
		};

		// ��ړ��f�t�H���g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_MOVE_UP = {
			{ DeviceKind::KEYBOARD, Key::SPACE }, { DeviceKind::PAD, Pad::R_TRIGGER }
		};

		// ���ړ��f�t�H���g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_MOVE_DOWN = {
			{ DeviceKind::KEYBOARD, Key::L_SHIFT }, { DeviceKind::PAD, Pad::L_TRIGGER }
		};

		// ���ړ��f�t�H���g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_MOVE_LEFT = {
			{ DeviceKind::KEYBOARD, Key::A }
		};

		// �E�ړ��f�t�H���g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_MOVE_RIGHT = {
			{ DeviceKind::KEYBOARD, Key::D }
		};

		// ���f�t�H���g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_CURSOR_UP = {
			{ DeviceKind::KEYBOARD, Key::UP }, { DeviceKind::PAD, Pad::UP }
		};

		// ���f�t�H���g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_CURSOR_DOWN = {
			{ DeviceKind::KEYBOARD, Key::DOWN }, { DeviceKind::PAD, Pad::DOWN }
		};

		// ���f�t�H���g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_CURSOR_LEFT = {
			{ DeviceKind::KEYBOARD, Key::LEFT }, { DeviceKind::PAD, Pad::LEFT }
		};

		// ���f�t�H���g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_CURSOR_RIGHT = {
			{ DeviceKind::KEYBOARD, Key::RIGHT }, { DeviceKind::PAD, Pad::RIGHT }
		};

		// �W�����v�f�t�H���g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_JUMP = {
			{ DeviceKind::KEYBOARD, Key::SPACE }, { DeviceKind::PAD, Pad::A }
		};

		// ���j���[�f�X�^�[�g�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_RESTART = {
			{ DeviceKind::KEYBOARD, Key::E }, { DeviceKind::PAD, Pad::START }
		};

		// Enter�L�[
		static std::vector<InputMapInfo> DEFAULT_INPUT_DEBUG_ENTER = {
			{ DeviceKind::KEYBOARD, Key::Z }, { DeviceKind::PAD, Pad::BACK }
		};

		// �f�t�H���g�L�[�p�����[�^
		static std::vector<InputMapInfo> DEFAULT_INPUT[] = {
			DEFAULT_INPUT_ESC,				// �����I��
			DEFAULT_INPUT_START_DEBUG_CAMERA,//�f�o�b�N�J�����J�n
			DEFAULT_INPUT_OK,				// ����
			DEFAULT_INPUT_CANCEL,			// �L�����Z��
			DEFAULT_INPUT_FIRE_PLUS_BULLET,		// �v���X�o���b�g����
			DEFAULT_INPUT_FIRE_MINUS_BULLET,		// �}�C�i�X�o���b�g����
			DEFAULT_INPUT_MOVE_FORWARD,		// �O�Ɉړ�
			DEFAULT_INPUT_MOVE_BACK,		// ���Ɉړ�
			DEFAULT_INPUT_MOVE_UP,			// ��Ɉړ�
			DEFAULT_INPUT_MOVE_DOWN,		// ���Ɉړ�
			DEFAULT_INPUT_MOVE_LEFT,		// ���Ɉړ�
			DEFAULT_INPUT_MOVE_RIGHT,		// �E�Ɉړ�
			DEFAULT_INPUT_JUMP,				// �W�����v
			DEFAULT_INPUT_RESTART,				// ���j���[���J��
			DEFAULT_INPUT_DEBUG_ENTER,		//����
		};

	} // namespace ACTION

} // namespace INPUT
