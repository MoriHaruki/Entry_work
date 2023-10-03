#include "PadInput.h"
#include "../Vector/MyLibData.h"
#include <cassert>

void CInputPad::Update()
{
    // Pad接続確認
    is_connect_ = GetJoypadNum() != 0;
    // 未接続の時Stepを回らない

    // 前フレの情報を記憶
    pre_pad_state_ = current_pad_state_;

    // 現在のコントローラー情報取得
    GetJoypadXInputState(DX_INPUT_PAD1, &current_pad_state_);
}

bool CInputPad::IsPush(int key_code)
{
#ifdef DEBUG_MODE
    int num = static_cast<int>(Pad::NUM);
    //範囲外数値確認時ゲーム停止
    assert(key_code > -1 && key_code < num);
#endif // DEBUG_MODE

    return (is_connect_ && pre_pad_state_.Buttons[key_code] == 0 && current_pad_state_.Buttons[key_code] == 1);
}

bool CInputPad::IsKeep(int key_code)
{
#ifdef DEBUG_MODE
    int num = static_cast<int>(Pad::NUM);
    //範囲外数値確認時ゲーム停止
    assert(key_code > -1 && key_code < num);
#endif // DEBUG_MODE

    return (is_connect_ && pre_pad_state_.Buttons[key_code] == 1 && current_pad_state_.Buttons[key_code] == 1);
}

bool CInputPad::IsRelease(int key_code)
{
#ifdef DEBUG_MODE
    int num = static_cast<int>(Pad::NUM);
    //範囲外数値確認時ゲーム停止
    assert(key_code > -1 && key_code < num);
#endif // DEBUG_MODE

    return (is_connect_ && pre_pad_state_.Buttons[key_code] == 1 && current_pad_state_.Buttons[key_code] == 0);
}

bool CInputPad::IsDown(int key_code)
{
#ifdef DEBUG_MODE
    int num = static_cast<int>(Pad::NUM);
    //範囲外数値確認時ゲーム停止
    assert(key_code > -1 && key_code < num);
#endif // DEBUG_MODE

    return (is_connect_ && current_pad_state_.Buttons[key_code] == 1);
}

void CInputPad::PadVibration(double time, Vibration power, int pad_type)
{
    // ミリ秒単位に直す
    int vibration_time = (int)time * 1000;
    int vibration_power = 0;
    switch (power) {
    case Vibration::_1: vibration_power = 100;  break;
    case Vibration::_2: vibration_power = 300;  break;
    case Vibration::_3: vibration_power = 500;  break;
    case Vibration::_4: vibration_power = 700;  break;
    case Vibration::_5: vibration_power = 1000; break;
    default: return;
    }

    // 振動開始
    StartJoypadVibration(pad_type, vibration_power, vibration_time);
}

Vector2D CInputPad::StickDir2D(const Stick& stick)
{
    Vector2D result;
    // 左スティック
    if (stick == Stick::LEFT) {
        result.x = (float)current_pad_state_.ThumbLX;
        result.y = (float)current_pad_state_.ThumbLY;
        // 正規化
        result.Normalize();
    }
    // 右スティック
    else if (stick == Stick::RIGHT) {
        result.x = (float)current_pad_state_.ThumbRX;
        result.y = (float)current_pad_state_.ThumbRY;
        // 正規化
        result.Normalize();
    }

    return result;
}

Vector3D CInputPad::StickDir3D(const Stick& stick)
{
    Vector3D result;
    // 左スティック
    if (stick == Stick::LEFT) {
        result.x = (float)current_pad_state_.ThumbLX;
        result.z = (float)current_pad_state_.ThumbLY;
        // 正規化
        result.Normalize();
    }
    // 右スティック
    else if (stick == Stick::RIGHT) {
        result.x = (float)current_pad_state_.ThumbRX;
        result.z = (float)current_pad_state_.ThumbRY;
        // 正規化
        result.Normalize();
    }

    return result;
}

float CInputPad::StickAngle(const Vector& vec, const Stick& stick)
{
    float result = 0.f;
    Vector2D calc_vec;

    //2D
    if (vec == Vector::_2D) {
        // 左スティック
        if (stick == Stick::LEFT) {
            Vector2D temp_vec = StickDir2D(Stick::LEFT);
            calc_vec(temp_vec);
        }
        // 右スティック
        else if (stick == Stick::RIGHT) {
            Vector2D temp_vec = StickDir2D(Stick::RIGHT);
            calc_vec(temp_vec);
        }
    }
    // 3D
    else if (vec == Vector::_3D) {
        // 左スティック
        if (stick == Stick::LEFT) {
            Vector3D temp_vec = StickDir3D(Stick::LEFT);
            calc_vec(temp_vec.x, temp_vec.z);
        }
        // 右スティック
        else if (stick == Stick::RIGHT) {
            Vector3D temp_vec = StickDir3D(Stick::RIGHT);
            calc_vec(temp_vec.x, temp_vec.z);
        }
    }
    // 角度計算
    result = MyLib::CalcVecAngle(calc_vec);

    return result;
}
