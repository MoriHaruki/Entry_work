#pragma once

#include "Singleton/Singleton.h"
#include "Sky.h"
#include"SkyParameter.h"
#include <list>
#include "Common.h"

//インスタンスへのマクロアクセス
#define SkyManagerInstance MyLib::Singleton<CSkyManager>
//インスタンス呼び出し簡略化
#define TheSkyManager MyLib::Singleton<CSkyManager>::Get()

class CSkyManager{

private:
	//アクセス権限付与
	friend MyLib::Singleton<CSkyManager>;

private:

	CSkyManager();
	~CSkyManager();

public:
	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Delete();
	void Fin();
	CSky* CreateSky(int id) { if (!sky_) sky_ = NEW CSky(id); return sky_; }

private:
	CSky* sky_;
	
};
