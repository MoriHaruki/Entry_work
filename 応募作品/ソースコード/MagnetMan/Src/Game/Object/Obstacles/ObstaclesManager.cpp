#include "ObstaclesManager.h"
#include "Long.h"
#include "Short.h"
#include "GravityPlate.h"
#include "Lift.h"
#include "Goal.h"
#include "Goal2.h"
#include "Common.h"

namespace
{
	class Prototypeinstance 
	{
	public:
		Prototypeinstance()
		{
			proto = nullptr;
		}
		~Prototypeinstance()
		{
			if (proto)
			{
				for (auto obstacles : *proto)
				{
					obstacles->Delete();
				}

				for (auto itr = proto->begin(); itr != proto->end();)
				{
					CObstacles* obstacles = (*itr);
					delete obstacles;
					obstacles = nullptr;
					itr = proto->erase(itr);
				}
			}
		}

		void SetProtoTypes(std::vector<CObstacles*>* ptr) 
		{
			proto = ptr;
		}

		std::vector<CObstacles*>* proto;
	};

	Prototypeinstance prototypeinstance;
}

CObstaclesManager::CObstaclesManager()
{}

CObstaclesManager::~CObstaclesManager()
{
	Fin();
}

void CObstaclesManager::CreatePrototypes()
{
	//毎回ロードされるのでキャンセルする
	if (prototype_obstacles_.size() != 0)
		return;
	prototypeinstance.SetProtoTypes(&prototype_obstacles_);

	for (int obstacles_index = 0; obstacles_index < static_cast<int>(OBSTACLES_STATE::NUM); ++obstacles_index)
	{
		prototype_obstacles_.emplace_back(CreatePrototype(obstacles_index));
	}
	for (auto obstacles : prototype_obstacles_)
	{
		obstacles->Load();
	}
}

//初期化
void CObstaclesManager::Init()
{
	SetObstacles();
}

void CObstaclesManager::SetObstacles()
{
	//パラメーターを取得
	const ObstaclesParameter *param = OBSTACLES_DATABASE[TheFieldManager->GetID()];

	for (int index = 0; index < CREATE_OBSTACLES_NUM; index++)
	{
		if (param[index].id == static_cast<int>(OBSTACLES_STATE::NONE))
		{
			break;
		}
		auto *Obstacles = CreateCObstacles(param[index].id);
		Obstacles->SetPos(param[index].startpos);
	}
}

CObstacles *CObstaclesManager::CreateCObstacles(int id)
{
	CObstacles* obstacles = nullptr;
	obstacles = prototype_obstacles_[id]->Clone();
	obstacles_.emplace_back(obstacles);
	return obstacles;
}

void CObstaclesManager::Load()
{
}

//ステップ
void CObstaclesManager::Step()
{
	
	for (auto obstacles : obstacles_)
	{
		obstacles->Step();
		MV1SetPosition(obstacles->GetHandle(), obstacles->GetPos());
	}
}

//描画
void CObstaclesManager::Draw()
{
	for (auto obstacles : obstacles_)
	{
		obstacles->Draw();
	}
}

//消去
void CObstaclesManager::Delete()
{
	for (auto obstacles : obstacles_)
	{
		obstacles->Delete();
	}
}

//後処理
void CObstaclesManager::Fin()
{
	CObstaclesManager::Delete();


	for (auto itr = obstacles_.begin(); itr != obstacles_.end();)
	{
		CObstacles* obstacles = (*itr);
		delete obstacles;
		obstacles = nullptr;
		itr = obstacles_.erase(itr);
	}
}

CObstacles* CObstaclesManager::GetObstacles(OBSTACLES_STATE id)
{
	for (auto obstacles : obstacles_)
	{
		if (obstacles->GetCurrenState() == id)
		{
			return obstacles;
		}
	}
	return nullptr;
}


CObstacles* CObstaclesManager::CreatePrototype(int id)
{
	switch (id)
	{
	case static_cast<int>(OBSTACLES_STATE::LONG):
		return NEW CLong;

	case static_cast<int>(OBSTACLES_STATE::SHORT):
		return NEW CShort;

	case static_cast<int>(OBSTACLES_STATE::GRAVITY):
		return NEW CGravityPlate;

	case static_cast<int>(OBSTACLES_STATE::LIFT):
		return NEW CLift;

	case static_cast<int>(OBSTACLES_STATE::GOAL):
		return NEW CGoal;

	case static_cast<int>(OBSTACLES_STATE::GOAL2):
		return NEW CGoal2;

	default:
		return nullptr;
	}
}
