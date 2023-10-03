#pragma once
#include "DxLib.h"
#include "Object/Object.h"
#include "EnemyParameter.h"
#include "Collision/SphereCollision.h"

 enum class ENEMY_STATE
{
	ENEMY_STATE_NORMAL
};

class CEnemy : public CObject
{
private:
	enum State
	{
		WAIT,
		POSITIONING,
		ATTACK,
		ESCAPE,
	};

public:
	CEnemy();
	~CEnemy();
	void Init();
	void Load();
	void Delete();
	void Step();
	void Draw();
	void Fin();
	void ReflectCollision(VECTOR vAddVec);
	void SetInfo(EnemyInfo info) { info_ = info; }
	void KeepPlayerDistance();

private:
	int state_;
	int           m_nHandle;
	ENEMY_STATE  m_eState;
	float         m_fJumpTime;
	float escape_speed_;
	float timer_;
	EnemyInfo info_;
	SphereCollision* collision_;
	bool moving;	//“G“®‚«ƒtƒ‰ƒO
	int attack_cnt_;
	float	m_fGravity;
	int small_bullet_index_;
	float small_bullet_timer_;
};
