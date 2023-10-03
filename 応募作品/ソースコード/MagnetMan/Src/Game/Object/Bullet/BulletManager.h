#pragma once

#include "Singleton/Singleton.h"
#include "Bullet.h"
#include "BulletParameter.h"
#include <vector>
#include <list>
#include "Common.h"

//インスタンスへのマクロアクセス
#define BulletManagerInstance MyLib::Singleton<CBulletManager>
//インスタンス呼び出し簡略化
#define TheBulletManager MyLib::Singleton<CBulletManager>::Get()

class CBulletManager {

private:
	//アクセス権限付与
	friend MyLib::Singleton<CBulletManager>;

private:
	CBulletManager();
	~CBulletManager();

public:
	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Delete();
	void Fin();
	int SetupBullet(int id, int category);
	CBullet* CreateBullet(int index);

private:
	// 使い終わったバレットを削除
	void DeleteEndBullet();

private:
	std::vector<CBullet*> prototype_bullets_;
	std::list<CBullet*> bullets_;
	
	
};
