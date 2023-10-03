#pragma once

#include "Singleton/Singleton.h"
#include "Player.h"
#include "Common.h"

//インスタンスへのマクロアクセス
#define PlayerManagerInstance MyLib::Singleton<CPlayerManager>
//インスタンス呼び出し簡略化
#define ThePlayerManager MyLib::Singleton<CPlayerManager>::Get()

class CPlayerManager{

private:
	//アクセス権限付与
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
