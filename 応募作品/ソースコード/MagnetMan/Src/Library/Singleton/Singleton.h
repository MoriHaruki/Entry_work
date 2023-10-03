#pragma once

#include "Common.h"

/*
	�V���O���g���Ǘ��N���X
	�V���O���g�����̗p����Ƃ��͂��̃w�b�_�[���C���N���[�h���邱��	
*/

namespace MyLib {
	template<class T>
	class Singleton {
		// �R���X�g���N�^�A�f�X�g���N�^�͊O�������֎~
	protected:
		Singleton(){}
		virtual ~Singleton() {}

	public:
		// �C���X�^���X����������Ă��Ȃ����NEW�Ő�������
		inline static T* Get() { return (!instance_) ? instance_ = NEW T : instance_; }
		// �C���X�^���X�폜
		inline static void Delete() { if (instance_) { delete instance_; instance_ = nullptr; } }

	private:
		// �C���X�^���X
		inline static T* instance_ = nullptr;
	};
}
