#pragma once

#include "Singleton/Singleton.h"
#include "Enemy.h"
#include <list>
#include "Common.h"

//�C���X�^���X�ւ̃}�N���A�N�Z�X
#define EnemyManagerInstance MyLib::Singleton<CEnemyManager>
//�C���X�^���X�Ăяo���ȗ���
#define TheEnemyManager MyLib::Singleton<CEnemyManager>::Get()

class CEnemyManager{

private:
	//�A�N�Z�X�����t�^
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