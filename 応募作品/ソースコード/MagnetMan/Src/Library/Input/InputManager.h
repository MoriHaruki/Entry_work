#pragma once
#include "GameInputParameter.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "PadInput.h"
#include "Singleton/Singleton.h"
#include "Common.h"

// インスタンスへのアクセスマクロ
#define GameInputInstance MyLib::Singleton<CGameInputManager>

// インスタンス呼び出し簡略化
#define TheGameInputManager MyLib::Singleton<CGameInputManager>::Get()

/*
	このゲームでのインプットを管理するクラス
	タイトルやプレイからキーコードを変更できるようにするため
*/
class CGameInputManager {
	// シングルトン
private:
	friend MyLib::Singleton<CGameInputManager>;

private: // 生成の禁止

	CGameInputManager()
		: input_(nullptr)
	{}

public: // 標準メソッド

	// 初期化
	void Init();

	// ステップ
	void Step();

	// 後処理
	void Fin();

public: // 入力判定

	// 押した瞬間
	bool IsPush(const std::string& action);
	bool IsPush(const char* action);

	// 押し続けている
	bool IsKeep(const std::string& action);
	bool IsKeep(const char* action);

	// 離した瞬間
	bool IsRelease(const std::string& action);
	bool IsRelease(const char* action);

	// 今押されているか
	bool IsDown(const std::string& action);
	bool IsDown(const char* action);

public: // キー関連アクセサ

		// インプット情報取得
	inline CInput* GetInput() const { return input_; }

	// キー情報取得
	inline CInputKeyBoard* GetInputKeyBoard() const { return (input_) ? input_->GetKeyBoardInput() : nullptr; }

public: // マウス関連アクセサ

	// マウスホイールの状態を取得する
	bool IsMouseWheelState(const std::string& action);

	// マウス情報取得
	inline CInputMouse* GetInputMouse() const { return (input_) ? input_->GetMouseInput() : nullptr; }

public: // パッド関連アクセサ

	// 入力アクションに対するスティックコードを返す
	Stick GetStickActionCode(const std::string& action) const;

	// パッド情報取得
	inline CInputPad* GetInputPad() const { return (input_) ? input_->GetPadInput() : nullptr; }

public: // 入力書き換え用関数群

	// 入力を一時的に書き換える
	void RewriteInputAction(const std::string& action, const InputMapInfo& info);

	// 入力上書き
	inline void Commit() { input_action_map_ = temp_action_map_; }

	// 入力をデフォルトに戻す
	inline void RollBackDefaultInput() { input_action_map_ = default_action_map_; }

private: // 内部メソッド

	// インプットクラス生成
	CInput* CreateInput() { return (input_) ? input_ : input_ = NEW CInput; }

public: // アクセサ

	// ゲット関数
	inline int GetActionNum() const { return static_cast<int>(GAME_INPUT::ACTION::Kind::NUM); }
	inline int GetStickActionNum() const { return static_cast<int>(GAME_INPUT::STICK::Kind::NUM); }
	inline InputStickMap GetInputStickMap() const { return input_action_map_.stick_map; }
	inline InputActionMap GetInputActionMap() const { return input_action_map_.action_map; }

	/*
		引数のアクションに対応するボタンのコードを返す
		引数：	action		:	アクション
				device		:	デバイス
		戻り値：ボタンコード(未定義のアクションやデバイスのボタンが設定されていなかったら-1を返す)
	*/
	int GetInputActionButtonCode(const std::string& action, DeviceKind device);

private: // メンバ変数

	// インプットクラスポインタ
	CInput* input_;

	// 入力とアクションの対応テーブル
	SaveInputData input_action_map_;

	// キー書き換え一時テーブル
	SaveInputData temp_action_map_;

	// デフォルトキーテーブル
	SaveInputData default_action_map_;

	// 現在の押下状態
	std::map<std::string, bool> current_state_;

	// 前フレの押下状態
	std::map<std::string, bool > pre_state_;
};