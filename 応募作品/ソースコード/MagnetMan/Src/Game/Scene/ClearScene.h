#pragma once
#include "Scene.h"
#include"../GameUI/GameUI.h"

namespace CLEAR
{
	const float LOGO_POS_X = 250.0f;			//�^�C�g�����S�����W
	const float LOGO_POS_Y = 60.0f;				//�^�C�g�����S�����W
	const float LOGO_FLOATING_SPEED = 0.03f;	//�^�C�g�����S�㉺���V���x
	const float LOGO_FLOATING_SIZE = 10.0f;		//�^�C�g�����S�㉺���V��
	const float PRESS_B_KEY_POS_X = 350.0;		//�v���C�V�[���ւ̓��̓K�C�h�����W
	const float PRESS_B_KEY_POS_Y = 420.0f;		//�v���C�V�[���ւ̓��̓K�C�h�����W
	const float PRESS_Z_KEY_BLINK_SPEED = 0.02f;//�v���C�V�[���ւ̓��̓K�C�h�_�ő��x
}

class Clear :public CScene
{
public:
	Clear();
	virtual ~Clear();
public:
	void Init()			override;
	void Load()			override;
	void OnLoadEnd()	override;
	void Step()			override;
	void Update()		override;
	void Draw()			override;
	void Fin()			override;
};