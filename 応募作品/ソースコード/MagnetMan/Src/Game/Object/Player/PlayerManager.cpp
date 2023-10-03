#include "PlayerManager.h"

CPlayerManager::CPlayerManager()
{
}

CPlayerManager::~CPlayerManager()
{
	
}

//初期化
void CPlayerManager::Init()
{
	player_ = NEW CPlayer;
	player_->Init();
}

//ロード
void CPlayerManager::Load()
{
	player_->Load("Data/Model/Player/Player2.x");
}

//ステップ
void CPlayerManager::Step()
{
	player_->Step();
	player_->StepBullet();
}

//描画
void CPlayerManager::Draw()
{
	player_->Draw();
}

//消去
void CPlayerManager::Delete()
{
	player_->Delete();

}

//後処理
void CPlayerManager::Fin()
{
	player_->Fin();
	delete player_;
	player_ = nullptr;
}