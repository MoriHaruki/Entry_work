#include "GameUIManager.h"
#include "GameUIParameter.h"
#include "GameUIAnimation.h"

CGameUIManager::CGameUIManager()
{
}

CGameUIManager::~CGameUIManager()
{
	
}

// UI生成
CGameUI* CGameUIManager::CreateUI(int type)
{
	CGameUI* ui = nullptr;
	switch (type)
	{
		case UI_TYPE_SPRITE: ui = NEW GameUISprite; break;
	}
	
	ui_vec_.push_back(ui);
	
	return ui;
}

CGameUI* CGameUIManager::CreateUI(int type, float pos_x, float pos_y, const char *file_path)
{
	CGameUI *ui = CreateUI(type);
	ui->Init(pos_x, pos_y);
	ui->Load(file_path);
	return ui;
}

void CGameUIManager::Step()
{
	for (auto itr : ui_vec_ ) {
		itr->Step();
	}
}

void CGameUIManager::Draw()
{
	for (auto itr : ui_vec_) {
		itr->Draw();
	}
}

void CGameUIManager::Fin()
{
	DeleteAll();
}

// vector内のUIをすべて削除
void CGameUIManager::DeleteAll()
{
	// まずUIを削除してから
	for (auto itr = ui_vec_.begin(); itr != ui_vec_.end(); itr++) {
		delete (*itr);
		(*itr) = nullptr;
	}
	// 配列を削除する
	ui_vec_.clear();
	ui_vec_.shrink_to_fit();

	// UIアニメーションも削除
	GameUIAnimationManager::DeleteAnimation();
}

