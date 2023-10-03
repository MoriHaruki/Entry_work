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
	// �Z�b�g�A�b�v�����o���b�g�����[�h
	for (auto bullet : prototype_bullets_)
	{
		bullet->Load();
	}
}

void CBulletManager::Step()
{
	// �o���b�g�X�e�b�v
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
	// �o���b�g�X�V
	for (auto bullet : bullets_)
	{
		bullet->Update();
	}
}

void CBulletManager::Draw()
{
	// �o���b�g�`��
	for (auto bullet : bullets_)
	{
		bullet->Draw();
	}
}

void CBulletManager::Delete()
{
	// �v���g�^�C�v�폜
	for (auto& bullet : prototype_bullets_)
	{
		delete bullet;
		bullet = nullptr;
	}

	// ���I�z��N���A
	prototype_bullets_.clear();
	prototype_bullets_.shrink_to_fit();

	// �o���b�g���X�g�N���A
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
	
	// �J�e�S���ɍ��킹���N���X����
	switch (category)
	{
	case BULLET_ID_PLAYER_PLUS: bullet = NEW CPlusBullet(id); break;
	case BULLET_ID_PLAYER_MINUS: bullet = NEW CMinusBullet(id);break;
	}

	if (bullet)
	{
		bullet->Init();							// ������
		prototype_bullets_.push_back(bullet);	// �ʎY���邽�߂Ƀv���g�^�C�v�z��Ɋi�[
	}
		
	return (int)prototype_bullets_.size() - 1;	// �A�N�Z�X�p�̃C���f�b�N�X��ԋp
}

CBullet* CBulletManager::CreateBullet(int index)
{
	// �v���g�^�C�v����N���[���𐶐�
	CBullet* bullet = prototype_bullets_[index]->Clone();
	bullets_.push_back(bullet);
	return bullet;
}

// �g���I������o���b�g���폜
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
