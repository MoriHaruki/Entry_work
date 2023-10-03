#pragma once

#include "Singleton/Singleton.h"
#include "Collision.h"
#include <list>
#include "Common.h"

//�C���X�^���X�ւ̃}�N���A�N�Z�X
#define CollisionManagerInstance MyLib::Singleton<CCollisionManager>
//�C���X�^���X�Ăяo���ȗ���
#define TheCollisionManager  MyLib::Singleton<CCollisionManager>::Get()

class CCollisionManager {

private:
	//�A�N�Z�X�����t�^
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
	void CheckPlayerBulletAndBox();		//�v���C���[�̒e�Ɣ��̓����蔻��
	void CheckPlayerAndBox();			//�v���C���[��BOX�̓����蔻��
	void CheckPlayerAndObstacles();			//�v���C���[�Ə�Q��
	
private:
	std::list<Collision*>collisions_[COLLISION_CATEGORY_NUM];
	float optimize_interval_;
	float optimize_timer_;
};
