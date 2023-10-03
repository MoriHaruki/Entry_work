#pragma once

#include "Singleton/Singleton.h"
#include "Player.h"
#include "Common.h"

//�C���X�^���X�ւ̃}�N���A�N�Z�X
#define PlayerManagerInstance MyLib::Singleton<CPlayerManager>
//�C���X�^���X�Ăяo���ȗ���
#define ThePlayerManager MyLib::Singleton<CPlayerManager>::Get()

class CPlayerManager{

private:
	//�A�N�Z�X�����t�^
	friend MyLib::Singleton<CPlayerManager>;

private:

	CPlayerManager();
	~CPlayerManager();

public:

	void Init();
	void Load();
	void Step();
	void Draw();
	void Delete();
	void Fin();

	CPlayer* GetPlayer() { return player_; }
private:

	CPlayer* player_;
};
