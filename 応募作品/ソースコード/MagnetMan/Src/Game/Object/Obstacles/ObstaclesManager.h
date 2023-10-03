#pragma once

#include "Singleton/Singleton.h"
#include "Obstacles.h"
#include <list>
#include <vector>
#include "Common.h"
#include "Goal.h"
#include "Goal2.h"
#include "Lift.h"
#include "GravityPlate.h"
#include "Long.h"
#include "Short.h"

//インスタンスへのマクロアクセス
#define ObstaclesManagerInstance MyLib::Singleton<CObstaclesManager>
//インスタンス呼び出し簡略化
#define TheObstaclesManager MyLib::Singleton<CObstaclesManager>::Get()

class CObstaclesManager{

private:
	//アクセス権限付与
	friend MyLib::Singleton<CObstaclesManager>;

private:
	CObstaclesManager();
	~CObstaclesManager();

public:
	static void CreatePrototypes();

	void Init();
	void SetObstacles();					//障害物をセットする
	CObstacles *CreateCObstacles(int id);	//障害物を作成する
	void Load();
	void Step();
	void Draw();
	void Delete();
	void Fin();
	CObstacles* GetObstacles(OBSTACLES_STATE id);

private:
	static CObstacles* CreatePrototype(int id);
	std::list<CObstacles*> obstacles_;
	inline static std::vector<CObstacles*> prototype_obstacles_;
};