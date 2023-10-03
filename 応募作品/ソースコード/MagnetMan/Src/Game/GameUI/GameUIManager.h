#pragma once

#include "Singleton/Singleton.h"
#include "GameUISprite.h"
#include <vector>
#include "Common.h"

//�C���X�^���X�ւ̃}�N���A�N�Z�X
#define GameUIManagerInstance MyLib::Singleton<CGameUIManager>
//�C���X�^���X�Ăяo���ȗ���
#define TheGameUIManager MyLib::Singleton<CGameUIManager>::Get()

//UI�Ǘ��p�N���X
class CGameUIManager {

private:
	//�A�N�Z�X�����t�^
	friend MyLib::Singleton<CGameUIManager>;

private:
	CGameUIManager();
	~CGameUIManager();

public:
	CGameUI* CreateUI(int type);
	CGameUI* CreateUI(int type, float pos_x, float pos_y, const char *file_path);

	void Step();
	void Draw();
	void Fin();
	void DeleteAll();

private:
	std::vector<CGameUI*> ui_vec_;
};

