#include "CollisionManager.h"
#include "SphereCollision.h"
#include "Common.h"
#include "Collision/BoxCollision.h"

CCollisionManager::CCollisionManager()
{
	optimize_interval_ = 0.0f;
	optimize_timer_ = 0.0f;
}

CCollisionManager::~CCollisionManager()
{
	Fin();
}

void CCollisionManager::Init()
{
}

void CCollisionManager::Step()
{
	for (int i = 0; i < COLLISION_CATEGORY_NUM; i++) 
	{
		for (auto collision : collisions_[i]) 
		{
			collision->Step();
		}
	}

	// �o���b�g���X�g�œK���i��������剻�΍�j
	if (optimize_timer_ >= optimize_interval_) 
	{
		DeleteEndCollision();
	}
	optimize_timer_ += CCommon::GetGameDeltaFrame();
	CheckCollision();
}

void CCollisionManager::Update()
{
	for (int i = 0; i < COLLISION_CATEGORY_NUM; i++) 
	{
		for (auto collision : collisions_[i]) 
		{
			collision->Update();
		}
	}
}

void CCollisionManager::Draw()
{
	for (int i = 0; i < COLLISION_CATEGORY_NUM; i++)
	{
		for (auto collision : collisions_[i]) 
		{
			collision->Draw();
		}
	}
#ifdef _DEBUG
	DrawFormatString(10, 600, 0xff00ff, "collision_size�F%d", collisions_[COLLISION_CATEGORY_BOX].size());
#endif
}

void CCollisionManager::Delete()
{
	for (int i = 0; i < COLLISION_CATEGORY_NUM; i++)
	{
		for (auto& collision : collisions_[i])
		{
			delete collision;
			collision = nullptr;
		}
		collisions_[i].clear();
	}
}

void CCollisionManager::Fin()
{
	Delete();
}

Collision* CCollisionManager::CreateCollision(int shape, int category)
{
	Collision* collision = nullptr;

	switch (shape) 
	{
	case COLLISION_SHAPE_SPHERE: collision = NEW SphereCollision; break;
	case COLLISION_SHAPE_BOX: collision = NEW BoxCollision; break;
	}

	if (collision)
	{
		collision->SetState(COLLISION_STATE_ACTIVE);
		collisions_[category].push_back(collision);
	}
	return collision;
}


//�g���I����������蔻���j��
void CCollisionManager::DeleteEndCollision()
{
	for (int i = 0; i < COLLISION_CATEGORY_NUM; i++) 
	{
		for (auto itr = collisions_[i].begin(); itr != collisions_[i].end();) 
		{
			Collision* collision = (*itr);
			if (collision->IsNone()) 
			{
				delete collision;
				collision = nullptr;
				itr = collisions_[i].erase(itr);
			}
			else 
			{
				itr++;
			}
		}
	}
}

void CCollisionManager::CheckCollision()
{
	CheckPlayerBulletAndBox();	// �v���C���[�o���b�g�Ɣ��̓����蔻��
	CheckPlayerAndBox();		//�v���C���[��BOX�̓����蔻��
	CheckPlayerAndObstacles();		//�v���C���[�Ə�Q���̓����蔻��
}

void CCollisionManager::CheckPlayerBulletAndBox()
{
	//�o���b�g�ƃv���C���[�̓����蔻��
	auto player_bullet_collisions = collisions_[COLLISION_CATEGORY_BULLET];
	auto box_collisions = collisions_[COLLISION_CATEGORY_BOX];
	for (auto bullet_collision : player_bullet_collisions) 
	{
		if (!bullet_collision->IsCheck()) continue;
		for (auto box_collision : box_collisions) 
		{
			if (!box_collision->IsCheck()) continue;

			if (bullet_collision->CheckCollision(box_collision)) 
			{
				bullet_collision->GetOwner()->OnCollisionEnter(box_collision->GetOwner());
				box_collision->GetOwner()->OnCollisionEnter(bullet_collision->GetOwner());
			}
		}
	}
}

void CCollisionManager::CheckPlayerAndBox()
{
	//�v���C���[��BOX�̓����蔻��
	auto players = collisions_[COLLISION_CATEGORY_PLAYER];
	auto boxs = collisions_[COLLISION_CATEGORY_BOX];
	for (auto player : players)
	{
		if(!player->IsCheck())continue;
		{
			for (auto box:boxs)
			{
				if (!box->IsCheck()) continue;
				if (player->CheckCollision(box))
				{
					player->GetOwner()->OnCollisionEnter(box->GetOwner());
					box->GetOwner()->OnCollisionEnter(player->GetOwner());
				}
			}
		}
	}
}

//�v���C���[�Ə�Q���̓����蔻��
void CCollisionManager::CheckPlayerAndObstacles()
{
	auto players = collisions_[COLLISION_CATEGORY_PLAYER];
	auto obstacles = collisions_[COLLISION_CATEGORY_OBSTACLES];
	for (auto player : players)
	{
		if (!player->IsCheck()) continue;
		for (auto obstacle : obstacles)
		{
			if (!obstacle->IsCheck()) continue;
			if (player->CheckCollision(obstacle))
			{
				player->GetOwner()->OnCollisionEnter(obstacle->GetOwner());
				obstacle->GetOwner()->OnCollisionEnter(player->GetOwner());
			}
		}
	}
}

