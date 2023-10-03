#pragma once

#include "InputParameter.h"
#include <map>
#include <string>
#include <vector>
// int型キャストdefine
#define IInputActionKind (int)GAME_INPUT::ACTION::Kind

/*
	ゲームで使うインプットパラメータ
*/

// 入力対応マップ情報(一つのキーごとの情報構造体)
struct InputMapInfo {
	InputMapInfo()
		: kind(DeviceKind::NONE)
		, code(0)
	{}
	InputMapInfo(const DeviceKind& device_kind, const int& input_code)
		: kind(device_kind)
		, code(input_code)
	{}

	DeviceKind	kind;	// デバイス情報
	int			code;	// 入力コード
};

// 入力アクションマップ簡略表示

typedef std::map<std::string, Stick> InputStickMap;
typedef std::map<std::string, std::vector<InputMapInfo>> InputActionMap;

// セーブインプットデータ
struct SaveInputData {
	SaveInputData()
		: stick_map()
		, action_map()
	{}

	InputStickMap	stick_map;		// スティックアクションマップ
	InputActionMap	action_map;		// 入力アクションマップ
};

namespace GAME_INPUT
{
	namespace STICK
	{
		enum class Kind {
			MOVE,	// 移動
			ROT,	// 回転
			NUM,
		};

		static const char* ACTION_NAME[] = {
			"Move",
			"Rot",
		};

		// デフォルト移動スティック
		static Stick DEFAULT_MOVE_STICK = Stick::LEFT;

		// デフォルト視点回転スティック
		static Stick DEFAULT_ROT_LOOK_STICK = Stick::RIGHT;

		// デフォルトスティックアクション
		static Stick DEFAULT_STICK[] = {
			DEFAULT_MOVE_STICK,
			DEFAULT_ROT_LOOK_STICK,
		};
	}

	namespace ACTION
	{
		enum class Kind {
			ESC,				// 強制終了
			START_DEBUG_CAMERA,	//デバックカメラ起動
			OK,					// 決定
			CANCEL,				// キャンセル
			FIRE_PLUS_BULLET,	//プラスバレット発射
			FIRE_MINUS_BULLET,	//マイナスバレット発射
			MOVE_FORWARD,		// 前移動
			MOVE_BACK,			// 後ろ移動
			MOVE_UP,			// 上移動
			MOVE_DOWN,			// 下移動
			MOVE_LEFT,			// 左移動
			MOVE_RIGHT,			// 右移動
			JUMP,				// ジャンプ
			RESTART,			// リスタート
			ENTER,				//決定
			NUM,
		};

		// 追加したい入力アクションがあればここに追加する
		static const char* ACTION_NAME[] = {
			"ESC",			// 強制終了
			"StartDebugCamera",	//デバックカメラ起動			
			"OK",			// 決定
			"Cancel",		// キャンセル
			"FirePlusBullet",	//プラスバレット発射
			"FireMinusBullet",//マイナスバレット発射
			"MoveForward",	// 前に進む
			"MoveBack",		// 後ろに進む
			"MoveUp",		// 上に進む
			"MoveDown",		// 下に進む
			"MoveLeft",		// 左に進む
			"MoveRight",	// 右に進む
			"CursorUp",		// ↑
			"CursorDown",	// ↓
			"CursorLeft",	// ←
			"CursorRight",	// →
			"Jump",			// ジャンプ
			"Menu",			// メニューを開く
			"Enter"			//決定

		};

		// 強制終了デフォルトキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_ESC = {
			{ DeviceKind::KEYBOARD, Key::ESC }
		};

		//デバックカメラ
		static std::vector<InputMapInfo> DEFAULT_INPUT_START_DEBUG_CAMERA = {
			{DeviceKind::KEYBOARD, Key::C}
		};

		// 決定デフォルトキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_OK = {
			{ DeviceKind::KEYBOARD, Key::B }, { DeviceKind::PAD, Pad::B }
		};

		// キャンセルデフォルトキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_CANCEL = {
			{ DeviceKind::KEYBOARD, Key::BACK }, { DeviceKind::PAD, Pad::A }
		};

		//プラスバレット発射
		static std::vector<InputMapInfo> DEFAULT_INPUT_FIRE_PLUS_BULLET = {
			{ DeviceKind::KEYBOARD, Key::K }, { DeviceKind::PAD, Pad::RB }, { DeviceKind::MOUSE, Mouse::RIGHT },
		};

		//マイナスバレット発射
		static std::vector<InputMapInfo> DEFAULT_INPUT_FIRE_MINUS_BULLET = {
			{ DeviceKind::KEYBOARD, Key::J }, { DeviceKind::PAD, Pad::LB }, { DeviceKind::MOUSE, Mouse::RIGHT },
		};

		// 前移動デフォルトキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_MOVE_FORWARD = {
			{ DeviceKind::KEYBOARD, Key::W  }
		};

		// 後ろ移動デフォルトキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_MOVE_BACK = {
			{ DeviceKind::KEYBOARD, Key::S }
		};

		// 上移動デフォルトキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_MOVE_UP = {
			{ DeviceKind::KEYBOARD, Key::SPACE }, { DeviceKind::PAD, Pad::R_TRIGGER }
		};

		// 下移動デフォルトキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_MOVE_DOWN = {
			{ DeviceKind::KEYBOARD, Key::L_SHIFT }, { DeviceKind::PAD, Pad::L_TRIGGER }
		};

		// 左移動デフォルトキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_MOVE_LEFT = {
			{ DeviceKind::KEYBOARD, Key::A }
		};

		// 右移動デフォルトキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_MOVE_RIGHT = {
			{ DeviceKind::KEYBOARD, Key::D }
		};

		// ↑デフォルトキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_CURSOR_UP = {
			{ DeviceKind::KEYBOARD, Key::UP }, { DeviceKind::PAD, Pad::UP }
		};

		// ↓デフォルトキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_CURSOR_DOWN = {
			{ DeviceKind::KEYBOARD, Key::DOWN }, { DeviceKind::PAD, Pad::DOWN }
		};

		// ←デフォルトキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_CURSOR_LEFT = {
			{ DeviceKind::KEYBOARD, Key::LEFT }, { DeviceKind::PAD, Pad::LEFT }
		};

		// →デフォルトキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_CURSOR_RIGHT = {
			{ DeviceKind::KEYBOARD, Key::RIGHT }, { DeviceKind::PAD, Pad::RIGHT }
		};

		// ジャンプデフォルトキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_JUMP = {
			{ DeviceKind::KEYBOARD, Key::SPACE }, { DeviceKind::PAD, Pad::A }
		};

		// メニューデスタートキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_RESTART = {
			{ DeviceKind::KEYBOARD, Key::E }, { DeviceKind::PAD, Pad::START }
		};

		// Enterキー
		static std::vector<InputMapInfo> DEFAULT_INPUT_DEBUG_ENTER = {
			{ DeviceKind::KEYBOARD, Key::Z }, { DeviceKind::PAD, Pad::BACK }
		};

		// デフォルトキーパラメータ
		static std::vector<InputMapInfo> DEFAULT_INPUT[] = {
			DEFAULT_INPUT_ESC,				// 強制終了
			DEFAULT_INPUT_START_DEBUG_CAMERA,//デバックカメラ開始
			DEFAULT_INPUT_OK,				// 決定
			DEFAULT_INPUT_CANCEL,			// キャンセル
			DEFAULT_INPUT_FIRE_PLUS_BULLET,		// プラスバレット発射
			DEFAULT_INPUT_FIRE_MINUS_BULLET,		// マイナスバレット発射
			DEFAULT_INPUT_MOVE_FORWARD,		// 前に移動
			DEFAULT_INPUT_MOVE_BACK,		// 後ろに移動
			DEFAULT_INPUT_MOVE_UP,			// 上に移動
			DEFAULT_INPUT_MOVE_DOWN,		// 下に移動
			DEFAULT_INPUT_MOVE_LEFT,		// 左に移動
			DEFAULT_INPUT_MOVE_RIGHT,		// 右に移動
			DEFAULT_INPUT_JUMP,				// ジャンプ
			DEFAULT_INPUT_RESTART,				// メニューを開く
			DEFAULT_INPUT_DEBUG_ENTER,		//決定
		};

	} // namespace ACTION

} // namespace INPUT
