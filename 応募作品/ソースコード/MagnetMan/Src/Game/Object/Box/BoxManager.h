#pragma once

#include "Singleton/Singleton.h"
#include "Box.h"
#include"MinusBox.h"
#include"PlusBox.h"
#include <list>
#include <vector>
#include "Common.h"

//インスタンスへのマクロアクセス
#define BoxManagerInstance MyLib::Singleton<CBoxManager>
//インスタンス呼び出し簡略化
#define TheBoxManager MyLib::Singleton<CBoxManager>::Get()

class CBoxManager
{
private:
	//アクセス権限付与
	friend MyLib::Singleton<CBoxManager>;

private:
	CBoxManager();
	~CBoxManager();

public:
	static void CreatePrototypes();

	void Init();
	void SetBox();					//BOXをセットする
	CBox* CreateBOX(int id);	//BOXを作成する
	void Load();
	void Step();
	void StepAttract();
	void Draw();
	void Delete();
	void Fin();
	void StepChenckChengeBox();		//常に箱の種類を変更をすか確認する
	void StepCheckAttractBoxs();	//ボックス同士を引き寄せる処理
	void BoxCollision();			//箱同士の当たり判定

private:
	static CBox* CreatePrototype(int id);
	std::list<CBox*> boxs_;
	static inline std::vector<CBox*> prototype_box_;
};