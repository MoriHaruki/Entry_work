#pragma once

#include "Singleton/Singleton.h"
#include "Field.h"
#include <list>
#include "Common.h"

//インスタンスへのマクロアクセス
#define FieldManagerInstance MyLib::Singleton<CFieldManager>
//インスタンス呼び出し簡略化
#define TheFieldManager MyLib::Singleton<CFieldManager>::Get()

class CFieldManager
{
private:
	//アクセス権限付与
	friend MyLib::Singleton<CFieldManager>;

private:
	 CFieldManager();
	~ CFieldManager();
public:
	void Init();
	void Load();
	void Step();
	void Draw();
	void Fin();
	void StartField(int field_id);			//ステージの起動
	void ChangeField(int change_id);			//ステージの切り替え
	CField* GetNowField() { return field_; }	//現在のステージデータを取得

	int GetID() const { return id_; }	//ID取得
	void SetID(int id) { id_ = id; }	//ID設定


private:
	CField*		field_;	//フィールドをクラス1つで管理する
	int			id_;	//フィールドID
};

