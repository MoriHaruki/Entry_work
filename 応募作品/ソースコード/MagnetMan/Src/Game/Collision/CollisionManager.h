#pragma once

#include "Singleton/Singleton.h"
#include "Collision.h"
#include <list>
#include "Common.h"

//インスタンスへのマクロアクセス
#define CollisionManagerInstance MyLib::Singleton<CCollisionManager>
//インスタンス呼び出し簡略化
#define TheCollisionManager  MyLib::Singleton<CCollisionManager>::Get()

class CCollisionManager {

private:
	//アクセス権限付与
	friend MyLib::Singleton<CCollisionManager>;

private:
	CCollisionManager();
	~CCollisionManager();
	
public:
	void Init();
	void Step();
	void Update();
	void Draw();
	void Delete();
	void Fin();

public:
	Collision* CreateCollision(int shape, int category);
	void DeleteEndCollision();

public:
	void CheckCollision();

private:
	void CheckPlayerBulletAndBox();		//プレイヤーの弾と箱の当たり判定
	void CheckPlayerAndBox();			//プレイヤーとBOXの当たり判定
	void CheckPlayerAndObstacles();			//プレイヤーと障害物
	
private:
	std::list<Collision*>collisions_[COLLISION_CATEGORY_NUM];
	float optimize_interval_;
	float optimize_timer_;
};
