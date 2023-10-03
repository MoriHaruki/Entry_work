#pragma once

#include "Singleton/Singleton.h"
#include "Bullet.h"
#include "BulletParameter.h"
#include <vector>
#include <list>
#include "Common.h"

//�C���X�^���X�ւ̃}�N���A�N�Z�X
#define BulletManagerInstance MyLib::Singleton<CBulletManager>
//�C���X�^���X�Ăяo���ȗ���
#define TheBulletManager MyLib::Singleton<CBulletManager>::Get()

class CBulletManager {

private:
	//�A�N�Z�X�����t�^
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
	// �g���I������o���b�g���폜
	void DeleteEndBullet();

private:
	std::vector<CBullet*> prototype_bullets_;
	std::list<CBullet*> bullets_;
	
	
};
