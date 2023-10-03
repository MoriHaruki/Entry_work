#include "EnemyManager.h"
#include "Common.h"

using namespace ENEMY;

CEnemyManager::CEnemyManager()
{
}

CEnemyManager::~CEnemyManager()
{
}

//������
void CEnemyManager::Init()
{
}

void CEnemyManager::CreateEnemy()
{
	for (int e = 0; e != E_MAX_NUM; e++)
	{
		CEnemy* enemy = NEW CEnemy;
		enemy->Init();
		enemy->Load();
		enemy->SetPos(ENEMY_DATABASE[e].startpos);
		enemies_.push_back(enemy);
	}
}

//�X�e�b�v
void CEnemyManager::Step()
{
	/*m_enemy.Step();*/
	for (auto enemy : enemies_) 
	{
		enemy->Step();
	}
}

//�`��
void CEnemyManager::Draw()
{
	for (auto enemy : enemies_)
	{
		enemy->Draw();
	}
}

//����
void CEnemyManager::Delete()
{
	for (auto enemy : enemies_)
	{
		enemy->Delete();
	}

}

//�㏈��
void CEnemyManager::Fin()
{
	for (auto itr = enemies_.begin(); itr != enemies_.end();)
	{
		CEnemy* enemy = (*itr);
		delete enemy;
		itr = enemies_.erase(itr);
	}
	
}