#include "Obstacles.h"
#include "Object/Player/PlayerManager.h"
#include "Math/MyMath.h"

CObstacles::CObstacles() : CObject(), collision_(nullptr)
{
	handle_ = 0;
	current_state_ = OBSTACLES_STATE::NONE;
	next_state_ = OBSTACLES_STATE::NONE;
	escape_speed_ = 0.0f;
	radian_ = 0.0f;
}

CObstacles::~CObstacles()
{
}

void CObstacles::Delete()
{
	if (collision_)
	{
		collision_->SetState(COLLISION_STATE_NONE);
	}

	MV1DeleteModel(handle_);

	handle_ = 0;
}

void CObstacles::Load(int handle)
{
	handle_ = MV1DuplicateModel(handle);
}

void CObstacles::Load(const char* path)
{
	handle_ = MV1LoadModel(path);
}

void CObstacles::Draw()
{
	MV1DrawModel(handle_);
}

void CObstacles::Fin()
{
	if (handle_ != 0)
	{
		Delete();
	}
}

void CObstacles::OnCollisionEnter(CObject* another)
{
	// プレイヤーが当たったら
	if (another->ObjectHasTag(IObject::PLAYER)) {
		// プレイヤー情報取得
		CPlayer* player = ThePlayerManager->GetPlayer();
		// 押し戻し処理実行
		player->SetPos(Extrude(player->GetPos(), player->GetSize(), pos_, size_));
	}
}
