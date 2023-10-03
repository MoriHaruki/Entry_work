#include "FieldManager.h"
#include "../Object/Box/BoxManager.h"
#include "../Object/Obstacles/ObstaclesManager.h"


CFieldManager::CFieldManager()
{
	field_ = nullptr;
	id_ = -1;
}

CFieldManager::~CFieldManager()
{
	Fin();
}

void CFieldManager::Init()
{
	if (!field_)
	{
		field_ = NEW CField;
	}

	if (field_)
	{
		field_->Init();
	}
}

void CFieldManager::Load()
{
	if (field_)
	{
		field_->LoadData();
	}
}

void CFieldManager::Step()
{
	if (field_)
	{
		field_->Step();
	}
}

void CFieldManager::Draw()
{
	if (field_)
	{
		field_->Draw();
	}
}

void CFieldManager::Fin()
{
	if (field_)
	{
		field_->Fin();

		delete field_;
		field_ = nullptr;
	}
}

void CFieldManager::StartField(int field_id)
{
	//常に起動していたら処理を抜ける
	if (field_)
	{
		return;
	}

	id_ = field_id;

	field_ = NEW CField;
	field_->Init();
	field_->LoadData();
}

void CFieldManager::ChangeField(int change_id)
{
	//常にステージが生成されていたら先にデータを破棄する
	if (field_)
	{
		field_->Fin();
		delete field_;
		field_ = nullptr;
		TheBoxManager->Fin();
		TheObstaclesManager->Fin();
	}

	id_ = change_id;

	field_ = NEW CField;
	field_->Init();
	field_->LoadData();


	//ステージに必要なものを読み込む
	TheBoxManager->Init();
	TheObstaclesManager->Init();

}
