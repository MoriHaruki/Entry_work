#include "PlayerManager.h"

CPlayerManager::CPlayerManager()
{
}

CPlayerManager::~CPlayerManager()
{
	
}

//������
void CPlayerManager::Init()
{
	player_ = NEW CPlayer;
	player_->Init();
}

//���[�h
void CPlayerManager::Load()
{
	player_->Load("Data/Model/Player/Player2.x");
}

//�X�e�b�v
void CPlayerManager::Step()
{
	player_->Step();
	player_->StepBullet();
}

//�`��
void CPlayerManager::Draw()
{
	player_->Draw();
}

//����
void CPlayerManager::Delete()
{
	player_->Delete();

}

//�㏈��
void CPlayerManager::Fin()
{
	player_->Fin();
	delete player_;
	player_ = nullptr;
}