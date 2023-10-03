#pragma once

#include "Input.h"
#include "../Vector/Vector3D.h"

// �p�b�h���͊Ǘ��N���X
class CInputPad : public CInputDeviceBase {
private:
	// �X�V����
	void Update() override;

private:
	// Input�ł̂ݐ����\
	friend class CInput;

	CInputPad()
		: current_pad_state_()
		, pre_pad_state_()
		, is_connect_(false)
	{}
	~CInputPad() {}

private: // ���͊֘A

	// �������ꂽ
	bool IsPush(int key_code) override;

	// ���������Ă���
	bool IsKeep(int key_code) override;

	// ��������
	bool IsRelease(int key_code) override;

	// ������Ă���
	bool IsDown(int key_code) override;

public:
	/*
		�W���C�p�b�h��U��������
		�����F	time		:	�U�������鎞��(�b)
				power		:	�U���̋���(�U���^�C�v��enum class���Q��)
				pad_type	:	�U�����������p�b�h

		��{�I�ɂ͈����Ȃ��Ŏg����
		�ڍׂɐݒ肵�����ꍇ�͈����Őݒ肷��
		�������w�肵�����ꍇ��0�`1000�܂ł̒l�Őݒ肷��(�͈͊O�̒l��n���Ă��͈͓��ɃL���X�g�����)
	*/
	void PadVibration(double time = 1.0, Vibration power = Vibration::_3, int pad_type = DX_INPUT_PAD1);
	/*
		�W���C�p�b�h�X�e�B�b�N�̓��͕������擾(2D�x�N�g��)
		�����F		stick	:	���E�̃X�e�B�b�N�̂ǂ���̓��͂�Ԃ���(stick��enum class�Q��)
		�߂�l	:	�[���x�N�g�����Ԃ��Ă�������͂��Ă��Ȃ�

		�Ԃ��Ă���x�N�g���͒P�ʃx�N�g���ɂȂ��Ă���̂ŁA�g���Ƃ��ɂ͖߂�l�̃x�N�g�����X�P�[���{���Ďg��
	*/
	Vector2D StickDir2D(const Stick& stick);
	/*
		�W���C�p�b�h�X�e�B�b�N�̓��͕������擾(3D�x�N�g��)
		�����F		stick	:	���E�̃X�e�B�b�N�̂ǂ���̓��͂�Ԃ���(stick��enum class�Q��)
		�߂�l	:	�[���x�N�g�����Ԃ��Ă�������͂��Ă��Ȃ�

		�Ԃ��Ă���x�N�g���͒P�ʃx�N�g���ɂȂ��Ă���̂ŁA�g���Ƃ��ɂ͖߂�l�̃x�N�g�����X�P�[���{���Ďg��
	*/
	Vector3D StickDir3D(const Stick& stick);
	/*
		�W���C�p�b�h�̃X�e�B�b�N�����ʕ����𐳂̌����������Ƃ��ɁA�ǂ̂��炢�p�x������̂����擾
		�����F	dimention	:	2D�x�N�g����3D�x�N�g����(�x�N�g���^�C�v��enum class�Q��)
				stick		:	���E�̃X�e�B�b�N�̂ǂ���̓��͂�Ԃ���(stick��enum class�Q��)
	*/
	float StickAngle(const Vector& vec, const Stick& stick);

private:
	// ���݂̃p�b�h���
	XINPUT_STATE current_pad_state_;
	// �O�t���̃p�b�h���
	XINPUT_STATE pre_pad_state_;
	// �p�b�h�ڑ��m�F�t���O
	bool is_connect_;
};