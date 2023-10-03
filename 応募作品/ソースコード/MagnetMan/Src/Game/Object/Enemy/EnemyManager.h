#pragma once

#include "Singleton/Singleton.h"
#include "Enemy.h"
#include <list>
#include "Common.h"

//インスタンスへのマクロアクセス
#define EnemyManagerInstance MyLib::Singleton<CEnemyManager>
//インスタンス呼び出し簡略化
#define TheEnemyManager MyLib::Singleton<CEnemyManager>::Get()

class CEnemyManager{

private:
	//アクセス権限付与
	friend MyLib::Singleton<CEnemyManager>;

private:

	CEnemyManager();
	~CEnemyManager();

public:

	void Init();
	void CreateEnemy();
	void Step();
	void Draw();
	void Delete();
	void Fin();
	CEnemy* GetEnemy() { return &enemy_; }

private:
	std::list<CEnemy* > enemies_;
	CEnemy  enemy_;
};