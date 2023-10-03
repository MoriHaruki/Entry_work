#include <math.h>
#include "Enemy.h"
#include "Input/Input.h"
#include "Math/MyMath.h"
#include "Object/Player/PlayerManager.h"
#include "Collision/CollisionManager.h"
#include "Common.h"
#include "Object/Bullet/BulletManager.h"

using namespace ENEMY;

CEnemy::CEnemy() : CObject()
{
	state_ = 0;
	m_nHandle = 0;
	m_eState = ENEMY_STATE::ENEMY_STATE_NORMAL;
	m_fJumpTime = 0.0f;
	escape_speed_ = 0.0f;
	timer_ = 0.0f;
	collision_ = nullptr;
	moving = false;  //敵動きフラグ
	attack_cnt_ = 0;
	small_bullet_index_ = 0;
	small_bullet_timer_ = 0.f;
	info_ = {0};
	m_fGravity = 0.0f;
}

CEnemy::~CEnemy()
{
}

void CEnemy::Init()
{
	info_ = INIT_ENEMY_INFO;
	m_nHandle = 0;
	m_eState = ENEMY_STATE::ENEMY_STATE_NORMAL;
	m_fJumpTime = 0.0f;
	//コリジョン設定
	collision_ = static_cast<SphereCollision*>(TheCollisionManager->CreateCollision((int)CollisionShape::COLLISION_SHAPE_SPHERE,
	(int)CollisionCategory::COLLISION_CATEGORY_ENEMY));
	collision_->SetOwner(this);
	collision_->SetRadius(COLLISION_RADIUS);
}

void CEnemy::Load()
{
	m_nHandle = MV1LoadModel("Data/Model/Enemy/Enemy.x");
}

void CEnemy::Delete()
{
	MV1DeleteModel(m_nHandle);
	m_nHandle = 0;
}

void CEnemy::Step()
{
	//重力処理
	pos_.y -= GRAVITY;
	//Y軸の当たり判定
	if (pos_.y - ENEMY_RAD < 0.0f)
	{
		pos_.y = ENEMY_RAD;
		m_eState = ENEMY_STATE::ENEMY_STATE_NORMAL;
	}
		// プレイヤーまでの距離
		const CPlayer* player = ThePlayerManager->GetPlayer();
		float player_dist = VecLong(pos_, player->GetPos());
		if (player_dist <= info_.active_dist)
		{
			state_ = POSITIONING;
			collision_->SetState(COLLISION_STATE_ACTIVE);
		}
		
		// プレイヤーまでの距離(Z値のみ)
		player_dist = VecLong(VGet(0.0f, 0.0f, pos_.z), VGet(0.0f, 0.0f, player->GetPos().z));
		moving = false;
		// 距離が遠い場合は近寄る
		if (player_dist <= info_.range)
		{
			pos_.z -= info_.speed;
			rot_.x -= info_.speed;
			/*	KeepPlayerDistance();*/
			//動作判定用
			moving = true;
		}
	
	MV1SetRotationXYZ(m_nHandle, rot_);
	MV1SetPosition(m_nHandle, pos_);
}

void CEnemy::Draw()
{
		MV1DrawModel(m_nHandle);
}


void CEnemy::Fin()
{
	if (m_nHandle != 0)
	{
		Delete();
	}
	moving = false;
}

void CEnemy::ReflectCollision(VECTOR vAddVec)
{
	// オールゼロなら何もしない
	if (vAddVec.x == 0.0f && vAddVec.y == 0.0f && vAddVec.z == 0.0f) return;
	VECTOR	vPos = GetPos();
	vPos = VAdd(vPos, vAddVec);
	pos_ = vPos;
	MV1SetPosition(m_nHandle, vPos);
	m_fGravity = 0.0f;	// とりあえず物体にぶつかったら重力を
}

void CEnemy::KeepPlayerDistance()
{
	const CPlayer* player = ThePlayerManager->GetPlayer();
	float player_dist = VecLong(VGet(0.0f, 0.0f, pos_.z), VGet(0.0f, 0.0f, player->GetPos().z));
	if (player_dist <= info_.range) 
	{
		// 近寄った後は一定距離を保つ
		pos_.z += info_.range - player_dist;
	}
}