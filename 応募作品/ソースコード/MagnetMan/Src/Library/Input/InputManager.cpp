#include "InputManager.h"
#include "MouseInput.h"

namespace {
	constexpr char DEFAULT_INPUT_FILE[] = "Data/Binary/Input/DefaultInput.bin";		// デフォルトインプットデータ
	constexpr char CUSTOM_INPUT_FILE[] = "Data/Binary/Input/CustomInput.bin";		// カスタムインプットデータ

	const char* MOUSE_WHEEL_STATE[] = {
		"Front",	// 奥に回す
		"Back",		// 手前に回す
	};
}

void CGameInputManager::Init()
{
	// インプットクラス生成
	input_ = CreateInput();

	// インプット初期化
	input_->Init();

	for (int stick_index = 0; stick_index < static_cast<int>(GAME_INPUT::STICK::Kind::NUM); ++stick_index) {
		// スティックマップ初期化
		input_action_map_.stick_map[GAME_INPUT::STICK::ACTION_NAME[stick_index]]
			= GAME_INPUT::STICK::DEFAULT_STICK[stick_index];
	}

	for (int key_index = 0; key_index < static_cast<int>(GAME_INPUT::ACTION::Kind::NUM); ++key_index) {
		// 入力アクションマップ初期化
		input_action_map_.action_map[GAME_INPUT::ACTION::ACTION_NAME[key_index]]
			= GAME_INPUT::ACTION::DEFAULT_INPUT[key_index];
	}

	// 一時保存マップに代入する
	temp_action_map_ = input_action_map_;
}

void CGameInputManager::Step()
{
	// インプットステップ
	input_->Step();

	// 前フレの押下状態を保存
	pre_state_ = current_state_;

	// それぞれのアクション名に割り当たっている全ての入力をチェック
	for (const auto& map_info : input_action_map_.action_map) {
		bool is_pressed = false;
		for (const auto& input_info : map_info.second) {
			// キーボード
			if (input_info.kind == DeviceKind::KEYBOARD) {
				// 押されているか
				if (input_->IsDown(input_info.code, DeviceKind::KEYBOARD)) {
					// 当たっていたらtrue
					is_pressed = true;

					// ループを抜ける
					break;
				}
			}
			// パッド
			if (input_info.kind == DeviceKind::PAD) {
				// 押されているか
				if (input_->IsDown(input_info.code, DeviceKind::PAD)) {
					// 当たっていたらtrue
					is_pressed = true;

					// ループを抜ける
					break;
				}
			}
			// マウス
			if (input_info.kind == DeviceKind::MOUSE) {
				// 押されているか
				if (input_->IsDown(input_info.code, DeviceKind::MOUSE)) {
					// 当たっていたらtrue
					is_pressed = true;

					// ループを抜ける
					break;
				}
			}
		}
		// 現在の状態を代入
		current_state_[map_info.first] = is_pressed;
	}
}

void CGameInputManager::Fin()
{
	// インプットの後処理
	input_->Fin();

	// インプットポインタの削除
	delete(input_);
}

bool CGameInputManager::IsPush(const std::string& action)
{
	// アクションマップ探索
	auto pre = pre_state_.find(action);

	// 未定義のボタン名が来たら無条件でfalseを返す
	if (pre == pre_state_.end()) { return false; }

	// アクションマップ探索
	auto current = current_state_.find(action);

	// 未定義のボタン名が来たら無条件でfalseを返す
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
	// アクションマップ探索
	auto pre = pre_state_.find(action);

	// 未定義のボタン名が来たら無条件でfalseを返す
	if (pre == pre_state_.end()) { return false; }

	// アクションマップ探索
	auto current = current_state_.find(action);

	// 未定義のボタン名が来たら無条件でfalseを返す
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
	// アクションマップ探索
	auto pre = pre_state_.find(action);

	// 未定義のボタン名が来たら無条件でfalseを返す
	if (pre == pre_state_.end()) { return false; }

	// アクションマップ探索
	auto current = current_state_.find(action);

	// 未定義のボタン名が来たら無条件でfalseを返す
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
	// アクションマップ探索
	auto current = current_state_.find(action);

	// 未定義のボタン名が来たら無条件でfalseを返す
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
	// マウス取得
	CInputMouse* mouse = input_->GetMouseInput();

	// 奥に回している情報か手前に回している情報かを判断する


	// 定義していない文字列が来たら、無条件でfalse
	return false;
}

Stick CGameInputManager::GetStickActionCode(const std::string& action) const
{
	// 文字列探索
	auto stick = input_action_map_.stick_map.find(action);

	// 未定義の動作が来たら
	if (stick == input_action_map_.stick_map.end()) {
		return Stick::NONE;
	}

	// スティックコードを返す
	return stick->second;
}

// 入力を一時的に書き換える
void CGameInputManager::RewriteInputAction(const std::string& action, const InputMapInfo& info)
{
	auto& table = temp_action_map_.action_map[action];
	bool is_hit = false;
	for (auto& elem : table) {
		// 一致する入力タイプを検索する
		if (elem.kind == info.kind) {
			elem.code = info.code;
			return;
		}
		// 一致する検索タイプが無かったら、新しく追加
		table.emplace_back(info);
	}
}

int CGameInputManager::GetInputActionButtonCode(const std::string& action, DeviceKind device)
{
	// 文字列探索
	auto input_action = input_action_map_.action_map.find(action);

	// 未定義の動作が来たら
	if (input_action == input_action_map_.action_map.end()) {
		// -1を返す
		return -1;
	}

	// 探索
	for (auto& elem : input_action->second) {
		// 対応するデバイスを探索
		if (elem.kind == device) {
			// コードを返す
			return elem.code;
		}
	}

	// ここまで来たらデバイスが対応していないので、-1
	return -1;
}
