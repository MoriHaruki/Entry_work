#include "BulletManager.h"
#include "PlusBullet.h"
#include "MinusBullet.h"
#include "Common.h"
#include "Object/Player/PlayerManager.h"

CBulletManager::CBulletManager()
{
}

CBulletManager::~CBulletManager()
{
	Fin();
}

void CBulletManager::Init()
{
}

void CBulletManager::Load()
{
	// セットアップしたバレットをロード
	for (auto bullet : prototype_bullets_)
	{
		bullet->Load();
	}
}

void CBulletManager::Step()
{
	// バレットステップ
	for (auto itr = bullets_.begin(); itr != bullets_.end();) {
		if ((*itr)->IsActive()) {
			(*itr)->Step();
			++itr;
		}
		else {
			(*itr)->Delete();
			delete *itr;
			*itr = nullptr;
			itr = bullets_.erase(itr);
		}
	}
}

void CBulletManager::Update()
{
	// バレット更新
	for (auto bullet : bullets_)
	{
		bullet->Update();
	}
}

void CBulletManager::Draw()
{
	// バレット描画
	for (auto bullet : bullets_)
	{
		bullet->Draw();
	}
}

void CBulletManager::Delete()
{
	// プロトタイプ削除
	for (auto& bullet : prototype_bullets_)
	{
		delete bullet;
		bullet = nullptr;
	}

	// 動的配列クリア
	prototype_bullets_.clear();
	prototype_bullets_.shrink_to_fit();

	// バレットリストクリア
	for (auto& bullet : bullets_)
	{
		delete bullet;
		bullet = nullptr;
	}
	bullets_.clear();
}

void CBulletManager::Fin()
{
	Delete();
}

int CBulletManager::SetupBullet(int id, int category)
{
	CBullet* bullet = nullptr;
	
	// カテゴリに合わせたクラス生成
	switch (category)
	{
	case BULLET_ID_PLAYER_PLUS: bullet = NEW CPlusBullet(id); break;
	case BULLET_ID_PLAYER_MINUS: bullet = NEW CMinusBullet(id);break;
	}

	if (bullet)
	{
		bullet->Init();							// 初期化
		prototype_bullets_.push_back(bullet);	// 量産するためにプロトタイプ配列に格納
	}
		
	return (int)prototype_bullets_.size() - 1;	// アクセス用のインデックスを返却
}

CBullet* CBulletManager::CreateBullet(int index)
{
	// プロトタイプからクローンを生成
	CBullet* bullet = prototype_bullets_[index]->Clone();
	bullets_.push_back(bullet);
	return bullet;
}

// 使い終わったバレットを削除
void CBulletManager::DeleteEndBullet()
{
	for (auto itr = bullets_.begin(); itr != bullets_.end();)
	{
		CBullet* bullet = (*itr);
		if (!bullet->IsActive())
		{
			bullet->Delete();
			delete bullet;
			bullet = nullptr;
			itr = bullets_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}
