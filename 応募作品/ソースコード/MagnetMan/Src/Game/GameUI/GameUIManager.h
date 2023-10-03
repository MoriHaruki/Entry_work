#pragma once

#include "Singleton/Singleton.h"
#include "GameUISprite.h"
#include <vector>
#include "Common.h"

//インスタンスへのマクロアクセス
#define GameUIManagerInstance MyLib::Singleton<CGameUIManager>
//インスタンス呼び出し簡略化
#define TheGameUIManager MyLib::Singleton<CGameUIManager>::Get()

//UI管理用クラス
class CGameUIManager {

private:
	//アクセス権限付与
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

