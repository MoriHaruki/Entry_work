#include "DxLib.h"
#include "GameUISprite.h"
#include <assert.h>

GameUISprite::GameUISprite() 
{
	handle_ = 0;
}

GameUISprite::~GameUISprite()
{
	Fin();
}

void GameUISprite::Init(float pos_x, float pos_y)
{
	pos_x_ = pos_x;
	pos_y_ = pos_y;
	alpha_ = 255.0f;
}

void GameUISprite::Load(const char *file_path)
{
	handle_ = LoadGraph(file_path);
}

void GameUISprite::Step()
{
	// スプライトの更新処理
}

void GameUISprite::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha_);
	DrawGraph((int)pos_x_, (int)pos_y_, handle_, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameUISprite::Delete()
{
	DeleteGraph(handle_);
	handle_ = 0;
}

void GameUISprite::Fin()
{
	if (handle_) {
		Delete();
	}
}

