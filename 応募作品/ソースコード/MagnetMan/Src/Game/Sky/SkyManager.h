#pragma once

#include "Singleton/Singleton.h"
#include "Sky.h"
#include"SkyParameter.h"
#include <list>
#include "Common.h"

//�C���X�^���X�ւ̃}�N���A�N�Z�X
#define SkyManagerInstance MyLib::Singleton<CSkyManager>
//�C���X�^���X�Ăяo���ȗ���
#define TheSkyManager MyLib::Singleton<CSkyManager>::Get()

class CSkyManager{

private:
	//�A�N�Z�X�����t�^
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
