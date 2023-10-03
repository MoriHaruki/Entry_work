#pragma once

#include "Common.h"
#include <DxLib.h>


// �f�o�C�X���͊ȗ���
#define Mouse		(int)DEVICE::BUTTON::MOUSE
#define Pad			(int)DEVICE::BUTTON::XInput
#define Key			(int)DEVICE::BUTTON::KeyBoard
#define Stick		DEVICE::PAD::STICK
#define Vibration	DEVICE::PAD::VIBRATION
#define Vector		DEVICE::PAD::VECTOR

// ���͋@��ȗ���
#define DeviceKind	DEVICE::Kind

// ���͋@���
namespace DEVICE {
	enum class Kind
	{
		NONE = -1,
		KEYBOARD,
		MOUSE,
		PAD,
		NUM,
	};// enum class Kind

	// �L�[���z��
	static const int KEY_BUF_LEN = 256;

	// �}�E�X�{�^����
	static const int MOUSE_BUF_LEN = 5;

	// �}�E�X�Œ�ʒu
	static const Vector2D MOUSE_SET_POS(CCommon::WINDOW_CENTER);

	namespace BUTTON {
		// �}�E�X
		enum class MOUSE
		{
			NONE = -1,

			LEFT = 1,	// ��
			RIGHT = 2,	// �E
			WHEEL = 4,	// �z�C�[��

			ROT_FRONT = 6,	// ���Ƀz�C�[������
			ROT_BACK = 8,	// ��O�Ƀz�C�[������

			NUM,
		};// enum class Mouse

		// XInput
		enum class XInput
		{
			NONE = -1,

			UP = 0,	// ��
			DOWN = 1,	// ��
			LEFT = 2,	// ��
			RIGHT = 3,	// �E
			START = 4,	// Start
			BACK = 5,	// Back
			L_STICK = 6,	// ���X�e�B�b�N��������
			R_STICK = 7,	// �E�X�e�B�b�N��������
			LB = 8,	// LB
			RB = 9,	// RB
			A = 12,	// A
			B = 13,	// B
			X = 14,	// X
			Y = 15,	// Y
			L_TRIGGER = 16,	// ���g���K�[
			R_TRIGGER = 17,	// �E�g���K�[

			NUM,
		};// enum class XInput

		// �L�[�{�[�h
		enum class KeyBoard
		{
			NONE = -1,

			BACK = KEY_INPUT_BACK,			// BackSpace
			TAB = KEY_INPUT_TAB,			// Tab
			ENTER = KEY_INPUT_RETURN,			// Enter

			L_SHIFT = KEY_INPUT_LSHIFT,			// ��Shift
			R_SHIFT = KEY_INPUT_RSHIFT,			// �EShift
			L_CTR = KEY_INPUT_LCONTROL,		// ��Ctrl
			R_CTR = KEY_INPUT_RCONTROL,		// �ECtrl
			ESC = KEY_INPUT_ESCAPE,			// Esc
			SPACE = KEY_INPUT_SPACE,			// Space
			PAGE_UP = KEY_INPUT_PGUP,			// PageUp
			PAGE_DOWN = KEY_INPUT_PGDN,			// PageDown
			END = KEY_INPUT_END,			// End
			HOME = KEY_INPUT_HOME,			// Home
			LEFT = KEY_INPUT_LEFT,			// ��
			UP = KEY_INPUT_UP,				// ��
			RIGHT = KEY_INPUT_RIGHT,			// �E
			DOWN = KEY_INPUT_DOWN,			// ��
			INSERT = KEY_INPUT_INSERT,			// Insert
			DEL = KEY_INPUT_DELETE,			// Delete

			MINUS = KEY_INPUT_MINUS,			// -
			YEN = KEY_INPUT_YEN,			// \�L�[
			PREVTRACK = KEY_INPUT_PREVTRACK,		// ^
			PERIOD = KEY_INPUT_PERIOD,			// .
			SLASH = KEY_INPUT_SLASH,			// /
			L_ALT = KEY_INPUT_LALT,			// ��ALT
			R_ALT = KEY_INPUT_RALT,			// �EALT
			SCROLL = KEY_INPUT_SCROLL,			// ScrollLock
			SEMICOLON = KEY_INPUT_SEMICOLON,		// ;
			COLON = KEY_INPUT_COLON,			// :
			LB_RACKET = KEY_INPUT_LBRACKET,		// [
			RB_RACKET = KEY_INPUT_RBRACKET,		// ]
			AT = KEY_INPUT_AT,				// @
			BACK_SLASH = KEY_INPUT_BACKSLASH,		// �_
			COMMA = KEY_INPUT_COMMA,			// ,
			KANJI = KEY_INPUT_KANJI,			// �����L�[
			CONVERT = KEY_INPUT_CONVERT,		// �ϊ��L�[
			NO_CONVERT = KEY_INPUT_NOCONVERT,		// ���ϊ��L�[
			KANA = KEY_INPUT_KANA,			// �J�i�L�[
			APPS = KEY_INPUT_APPS,			// �A�v���P�[�V�����L�[
			CAPS_LOCK = KEY_INPUT_CAPSLOCK,		// CaspLock
			PRINT_SCREEN = KEY_INPUT_SYSRQ,			// PrintScreen
			PAUSE = KEY_INPUT_PAUSE,			// PauseBreak
			L_WIN = KEY_INPUT_LWIN,			// ��Win
			R_WIN = KEY_INPUT_RWIN,			// �EWin

			NUMLOCK = KEY_INPUT_NUMLOCK,		// �e���L�[NumLock
			NUMPAD_0 = KEY_INPUT_NUMPAD0,		// �e���L�[0
			NUMPAD_1 = KEY_INPUT_NUMPAD1,		// �e���L�[1
			NUMPAD_2 = KEY_INPUT_NUMPAD2,		// �e���L�[2
			NUMPAD_3 = KEY_INPUT_NUMPAD3,		// �e���L�[3
			NUMPAD_4 = KEY_INPUT_NUMPAD4,		// �e���L�[4
			NUMPAD_5 = KEY_INPUT_NUMPAD5,		// �e���L�[5
			NUMPAD_6 = KEY_INPUT_NUMPAD6,		// �e���L�[6
			NUMPAD_7 = KEY_INPUT_NUMPAD7,		// �e���L�[7
			NUMPAD_8 = KEY_INPUT_NUMPAD8,		// �e���L�[8
			NUMPAD_9 = KEY_INPUT_NUMPAD9,		// �e���L�[9

			F1 = KEY_INPUT_F1,				// F1
			F2 = KEY_INPUT_F2,				// F2
			F3 = KEY_INPUT_F3,				// F3
			F4 = KEY_INPUT_F4,				// F4
			F5 = KEY_INPUT_F5,				// F5
			F6 = KEY_INPUT_F6,				// F6
			F7 = KEY_INPUT_F7,				// F7
			F8 = KEY_INPUT_F8,				// F8
			F9 = KEY_INPUT_F9,				// F9
			F10 = KEY_INPUT_F10,			// F10
			F11 = KEY_INPUT_F11,			// F11
			F12 = KEY_INPUT_F12,			// F12

			A = KEY_INPUT_A,				// A
			B = KEY_INPUT_B,				// B
			C = KEY_INPUT_C,				// C
			D = KEY_INPUT_D,				// D
			E = KEY_INPUT_E,				// E
			F = KEY_INPUT_F,				// F
			G = KEY_INPUT_G,				// G
			H = KEY_INPUT_H,				// H
			I = KEY_INPUT_I,				// I
			J = KEY_INPUT_J,				// J
			K = KEY_INPUT_K,				// K
			L = KEY_INPUT_L,				// L
			M = KEY_INPUT_M,				// M
			N = KEY_INPUT_N,				// N
			O = KEY_INPUT_O,				// O
			P = KEY_INPUT_P,				// P
			Q = KEY_INPUT_Q,				// Q
			R = KEY_INPUT_R,				// R
			S = KEY_INPUT_S,				// S
			T = KEY_INPUT_T,				// T
			U = KEY_INPUT_U,				// U
			V = KEY_INPUT_V,				// V
			W = KEY_INPUT_W,				// W
			X = KEY_INPUT_X,				// X
			Y = KEY_INPUT_Y,				// Y
			Z = KEY_INPUT_Z,				// Z

			_0 = KEY_INPUT_0,				// 0
			_1 = KEY_INPUT_1,				// 1
			_2 = KEY_INPUT_2,				// 2
			_3 = KEY_INPUT_3,				// 3
			_4 = KEY_INPUT_4,				// 4
			_5 = KEY_INPUT_5,				// 5
			_6 = KEY_INPUT_6,				// 6
			_7 = KEY_INPUT_7,				// 7
			_8 = KEY_INPUT_8,				// 8
			_9 = KEY_INPUT_9,				// 9
		};// enum class KeyBoard

	}// namespace BUTTON

	namespace PAD {
		// �X�e�B�b�N�ݒ�
		enum class STICK
		{
			NONE = -1,

			LEFT,		// ��
			RIGHT,		// �E
		};// enum class Stick
		/*
			�p�b�h�U���^�C�v(�f�t�H���g�ł�5�i�K�Őݒ�)
			TYPE�̐��l���㏸����ɂ�ĐU���̋����������Ȃ�
		*/
		enum class VIBRATION
		{
			_1,
			_2,
			_3,
			_4,
			_5,
		};// enum class Vibration

		// �x�N�g���^�C�v
		enum class VECTOR
		{
			_2D,	// 2D
			_3D,	// 3D
		};// enum class Vector

	}// namespace PAD

}// namespace DEVICE

// ���͋@��x�[�X
class CInputDeviceBase {
public:	// �������z�֐��Ő錾

	// ���͊֘A
	// ��������
	virtual bool IsPush(int key_code) = 0;

	// ���������Ă���
	virtual bool IsKeep(int key_code) = 0;

	// ��������
	virtual bool IsRelease(int key_code) = 0;

	// �����Ă���
	virtual bool IsDown(int key_code) = 0;

	// ���͏��X�V
	virtual void Update() = 0;
};