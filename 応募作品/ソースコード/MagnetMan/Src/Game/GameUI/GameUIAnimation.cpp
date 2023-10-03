#include "GameUIAnimation.h"
#include "Math/MyMath.h"
#include "Common.h"

// UI�A�j���[�V����
GameUIAnimation::GameUIAnimation()
{
	play_flg_ = false;
	ui_ = nullptr;
}

GameUIAnimation::~GameUIAnimation()
{
}

// ���ŃA�j���[�V����
GameUIBlinkAnimation::GameUIBlinkAnimation()
{
	speed_ = 0.0f;
	rad_ = 0.0f;
}

GameUIBlinkAnimation::~GameUIBlinkAnimation()
{
}

void GameUIBlinkAnimation::Step()
{
	float alpha = GetSin(0.0f, 255.0f, rad_);
	ui_->SetAlpha(alpha);
	rad_ += speed_;
}

// ���V�A�j���[�V����
GameUIFloatingAnimation::GameUIFloatingAnimation()
{
	speed_ = 0.0f;
	rad_ = 0.0f;
	center_pos_ = 0.0f;
	min_offset_ = 0.0f;
	max_offset_ = 0.0f;

}

GameUIFloatingAnimation::~GameUIFloatingAnimation()
{
}

void GameUIFloatingAnimation::Step()
{
	float offset = GetSin(min_offset_, max_offset_, rad_);
	ui_->SetPosY(center_pos_ + offset);
	rad_ += speed_;
}

void GameUIFloatingAnimation::SetFloating(float center, float size)
{
	center_pos_ = center;
	min_offset_ = -(size / 2.0f);
	max_offset_ =  (size / 2.0f);
}

// �X���C�f�B���O�A�j���[�V����
GameUISlidingAnimation::GameUISlidingAnimation()
{
	start_pos_ = { 0.0f };
	move_ = { 0.0f };
	rad_ = 0.0f;
	speed_ = 0.0f;
}

GameUISlidingAnimation::~GameUISlidingAnimation()
{
}

void GameUISlidingAnimation::Step()
{
	if (rad_ > DX_PI_F / 2.0f) {
		rad_ = DX_PI_F / 2.0f;
		play_flg_ = false;
	}

	float scale = GetSin(rad_);
	VECTOR offset = VecScale(move_, scale);
	VECTOR pos = VecAdd(start_pos_, offset);

	ui_->SetPosX(pos.x);
	ui_->SetPosY(pos.y);

	rad_ += speed_;
}

// �A�j���[�V�����Ǘ�
std::vector<GameUIAnimation*> GameUIAnimationManager::animations_;
void GameUIAnimationManager::Init()
{
}

void GameUIAnimationManager::Step()
{
	for (auto animation : animations_) {
		if (animation->IsPlay()) {
			animation->Step();
		}
	}
}

void GameUIAnimationManager::DeleteAnimation()
{
	for (auto animation : animations_) {
		delete animation;
	}

	animations_.clear();
	animations_.shrink_to_fit();
}

// ���ŃA�j���[�V�����Đ�
void GameUIAnimationManager::PlayBlinkAnimation(CGameUI* ui, float speed)
{
	GameUIBlinkAnimation* anim = NEW GameUIBlinkAnimation;
	anim->SetUI(ui);
	anim->SetSpeed(speed);
	anim->Play();

	animations_.push_back(anim);
}

// ���V�A�j���[�V�����Đ�
void GameUIAnimationManager::PlayFloatingAnimation(CGameUI* ui, float speed, float floating_size)
{
	GameUIFloatingAnimation* anim = NEW GameUIFloatingAnimation;
	anim->SetUI(ui);
	anim->SetSpeed(speed);
	anim->SetFloating(ui->GetPosY(), floating_size);
	anim->Play();

	animations_.push_back(anim);
}

// �X���C�f�B���O�A�j���[�V�����Đ�
void GameUIAnimationManager::PlaySlidingAnimation(CGameUI* ui, VECTOR start_pos, VECTOR end_pos, float speed)
{
	GameUISlidingAnimation* anim = NEW GameUISlidingAnimation;
	anim->SetUI(ui);
	anim->SetSpeed(speed);
	VECTOR move = VecCreate(start_pos, end_pos);
	anim->SetMove(move);
	anim->SetStartPos(start_pos);
	anim->Play();

	animations_.push_back(anim);
}

