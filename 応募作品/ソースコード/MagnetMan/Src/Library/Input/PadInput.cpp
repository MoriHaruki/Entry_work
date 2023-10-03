#include "PadInput.h"
#include "../Vector/MyLibData.h"
#include <cassert>

void CInputPad::Update()
{
    // Pad�ڑ��m�F
    is_connect_ = GetJoypadNum() != 0;
    // ���ڑ��̎�Step�����Ȃ�

    // �O�t���̏����L��
    pre_pad_state_ = current_pad_state_;

    // ���݂̃R���g���[���[���擾
    GetJoypadXInputState(DX_INPUT_PAD1, &current_pad_state_);
}

bool CInputPad::IsPush(int key_code)
{
#ifdef DEBUG_MODE
    int num = static_cast<int>(Pad::NUM);
    //�͈͊O���l�m�F���Q�[����~
    assert(key_code > -1 && key_code < num);
#endif // DEBUG_MODE

    return (is_connect_ && pre_pad_state_.Buttons[key_code] == 0 && current_pad_state_.Buttons[key_code] == 1);
}

bool CInputPad::IsKeep(int key_code)
{
#ifdef DEBUG_MODE
    int num = static_cast<int>(Pad::NUM);
    //�͈͊O���l�m�F���Q�[����~
    assert(key_code > -1 && key_code < num);
#endif // DEBUG_MODE

    return (is_connect_ && pre_pad_state_.Buttons[key_code] == 1 && current_pad_state_.Buttons[key_code] == 1);
}

bool CInputPad::IsRelease(int key_code)
{
#ifdef DEBUG_MODE
    int num = static_cast<int>(Pad::NUM);
    //�͈͊O���l�m�F���Q�[����~
    assert(key_code > -1 && key_code < num);
#endif // DEBUG_MODE

    return (is_connect_ && pre_pad_state_.Buttons[key_code] == 1 && current_pad_state_.Buttons[key_code] == 0);
}

bool CInputPad::IsDown(int key_code)
{
#ifdef DEBUG_MODE
    int num = static_cast<int>(Pad::NUM);
    //�͈͊O���l�m�F���Q�[����~
    assert(key_code > -1 && key_code < num);
#endif // DEBUG_MODE

    return (is_connect_ && current_pad_state_.Buttons[key_code] == 1);
}

void CInputPad::PadVibration(double time, Vibration power, int pad_type)
{
    // �~���b�P�ʂɒ���
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

    // �U���J�n
    StartJoypadVibration(pad_type, vibration_power, vibration_time);
}

Vector2D CInputPad::StickDir2D(const Stick& stick)
{
    Vector2D result;
    // ���X�e�B�b�N
    if (stick == Stick::LEFT) {
        result.x = (float)current_pad_state_.ThumbLX;
        result.y = (float)current_pad_state_.ThumbLY;
        // ���K��
        result.Normalize();
    }
    // �E�X�e�B�b�N
    else if (stick == Stick::RIGHT) {
        result.x = (float)current_pad_state_.ThumbRX;
        result.y = (float)current_pad_state_.ThumbRY;
        // ���K��
        result.Normalize();
    }

    return result;
}

Vector3D CInputPad::StickDir3D(const Stick& stick)
{
    Vector3D result;
    // ���X�e�B�b�N
    if (stick == Stick::LEFT) {
        result.x = (float)current_pad_state_.ThumbLX;
        result.z = (float)current_pad_state_.ThumbLY;
        // ���K��
        result.Normalize();
    }
    // �E�X�e�B�b�N
    else if (stick == Stick::RIGHT) {
        result.x = (float)current_pad_state_.ThumbRX;
        result.z = (float)current_pad_state_.ThumbRY;
        // ���K��
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
        // ���X�e�B�b�N
        if (stick == Stick::LEFT) {
            Vector2D temp_vec = StickDir2D(Stick::LEFT);
            calc_vec(temp_vec);
        }
        // �E�X�e�B�b�N
        else if (stick == Stick::RIGHT) {
            Vector2D temp_vec = StickDir2D(Stick::RIGHT);
            calc_vec(temp_vec);
        }
    }
    // 3D
    else if (vec == Vector::_3D) {
        // ���X�e�B�b�N
        if (stick == Stick::LEFT) {
            Vector3D temp_vec = StickDir3D(Stick::LEFT);
            calc_vec(temp_vec.x, temp_vec.z);
        }
        // �E�X�e�B�b�N
        else if (stick == Stick::RIGHT) {
            Vector3D temp_vec = StickDir3D(Stick::RIGHT);
            calc_vec(temp_vec.x, temp_vec.z);
        }
    }
    // �p�x�v�Z
    result = MyLib::CalcVecAngle(calc_vec);

    return result;
}
