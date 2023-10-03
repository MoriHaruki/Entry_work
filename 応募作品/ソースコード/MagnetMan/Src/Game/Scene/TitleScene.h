#pragma once

#include "Scene.h"
#include "GameUI/GameUI.h"

namespace TITLE
{
	const float LOGO_POS_X = 250.0f;			//�^�C�g�����S�����W
	const float LOGO_POS_Y = 60.0f;				//�^�C�g�����S�����W
	const float LOGO_FLOATING_SPEED = 0.03f;	//�^�C�g�����S�㉺���V���x
	const float LOGO_FLOATING_SIZE = 10.0f;		//�^�C�g�����S�㉺���V��
	const float PRESS_B_KEY_POS_X = 350.0;		//�v���C�V�[���ւ̓��̓K�C�h�����W
	const float PRESS_B_KEY_POS_Y = 420.0f;		//�v���C�V�[���ւ̓��̓K�C�h�����W
	const float PRESS_Z_KEY_BLINK_SPEED = 0.02f;//�v���C�V�[���ւ̓��̓K�C�h�_�ő��x
}

class CTitle : public CScene {

public:
	CTitle();
	virtual ~CTitle();

public:
	void Init()			override;	//������
	void Load()			override;	//�ǂݍ���
	void OnLoadEnd()	override;	//�ǂݍ��ݏI��
	void Step()			override;	//�ʏ�
	void Update()		override;	//�X�V
	void Draw()			override;	//�`��
	void Fin()			override;	//�㏈��
};
