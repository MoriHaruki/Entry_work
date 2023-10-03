#include "EnemyManager.h"
#include "Common.h"

using namespace ENEMY;

CEnemyManager::CEnemyManager()
{
}

CEnemyManager::~CEnemyManager()
{
}

//初期化
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

//ステップ
void CEnemyManager::Step()
{
	/*m_enemy.Step();*/
	for (auto enemy : enemies_) 
	{
		enemy->Step();
	}
}

//描画
void CEnemyManager::Draw()
{
	for (auto enemy : enemies_)
	{
		enemy->Draw();
	}
}

//消去
void CEnemyManager::Delete()
{
	for (auto enemy : enemies_)
	{
		enemy->Delete();
	}

}

//後処理
void CEnemyManager::Fin()
{
	for (auto itr = enemies_.begin(); itr != enemies_.end();)
	{
		CEnemy* enemy = (*itr);
		delete enemy;
		itr = enemies_.erase(itr);
	}
	
}