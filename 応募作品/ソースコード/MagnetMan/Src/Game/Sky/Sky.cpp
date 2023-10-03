#include "Sky.h"
#include "SkyParameter.h"
#include "Object/Player/PlayerManager.h"

CSky::CSky(int id)
{
	id_ = id;
	handle_ = -1;
}

CSky::~CSky()
{
	Fin();
}

void CSky::Init()
{
}

void CSky::Load()
{
	handle_ = MV1LoadModel(SKY_DATABASE[id_].FILE_PATH);
}

void CSky::Step()
{
	// �v���C���[�ɒǏ]����
	CPlayerManager* player_manager = ThePlayerManager;
	if (player_manager) {
		CPlayer* player = player_manager->GetPlayer();
		if (player) {
			pos_ = player->GetPos();
		}
		// Y���W�̂݌Œ�
		pos_.y = SKY_POS_Y;
	}
}

void CSky::Update()
{
	MV1SetPosition(handle_, pos_);
}

void CSky::Draw()
{
	MV1DrawModel(handle_);
}

void CSky::Delete()
{
	MV1DeleteModel(handle_);
}

void CSky::Fin()
{
	Delete();
}
