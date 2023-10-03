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

//�C���X�^���X�ւ̃}�N���A�N�Z�X
#define ObstaclesManagerInstance MyLib::Singleton<CObstaclesManager>
//�C���X�^���X�Ăяo���ȗ���
#define TheObstaclesManager MyLib::Singleton<CObstaclesManager>::Get()

class CObstaclesManager{

private:
	//�A�N�Z�X�����t�^
	friend MyLib::Singleton<CObstaclesManager>;

private:
	CObstaclesManager();
	~CObstaclesManager();

public:
	static void CreatePrototypes();

	void Init();
	void SetObstacles();					//��Q�����Z�b�g����
	CObstacles *CreateCObstacles(int id);	//��Q�����쐬����
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