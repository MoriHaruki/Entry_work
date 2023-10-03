#pragma once

#include "GameUI.h"
#include "DxLib.h"
#include <vector>

// �A�j���[�V�����x�[�X�N���X
class GameUIAnimation {
public:
	GameUIAnimation();
	~GameUIAnimation();

public:
	virtual void Step() = 0;

public:
	bool IsPlay() const { return play_flg_; }

	void SetUI(CGameUI* ui) { ui_ = ui; }
	void Play() { play_flg_ = true; }
	void Stop() { play_flg_ = false; }

protected:
	bool play_flg_;
	CGameUI* ui_;
};

// ���ŃA�j���[�V����
class GameUIBlinkAnimation : public GameUIAnimation {
public:
	GameUIBlinkAnimation();
	~GameUIBlinkAnimation();

public:
	void Step() override;

public:
	void SetSpeed(float speed) { speed_ = speed; }

private:
	float speed_;
	float rad_;
};

// �㉺���V�A�j���[�V����
class GameUIFloatingAnimation : public GameUIAnimation {
public:
	GameUIFloatingAnimation();
	~GameUIFloatingAnimation();

public:
	void Step() override;

public:
	void SetSpeed(float speed) { speed_ = speed; }
	void SetFloating(float center, float size);

private:
	float speed_;
	float rad_;
	float center_pos_;
	float min_offset_;
	float max_offset_;
};

// �X���C�h�ړ��A�j���[�V����
class GameUISlidingAnimation : public GameUIAnimation {
public:
	GameUISlidingAnimation();
	~GameUISlidingAnimation();

public:
	void Step() override;
	void SetSpeed(float speed) { speed_ = speed; }
	void SetMove(VECTOR move) { move_ = move; }
	void SetStartPos(VECTOR pos) { start_pos_ = pos; }

private:
	VECTOR start_pos_;
	VECTOR move_;
	float rad_;
	float speed_;
};

// UI�A�j���[�V�����Ǘ�
class GameUIAnimationManager {
public:
	static void Init();
	static void Step();
	static void DeleteAnimation();

public:
	// �e�A�j���[�V�����Đ�
	static void PlayBlinkAnimation(CGameUI* ui, float speed);
	static void PlayFloatingAnimation(CGameUI* ui, float speed, float floating_size);
	static void PlaySlidingAnimation(CGameUI* ui, VECTOR start_pos, VECTOR end_pos, float speed);

private:
	static std::vector<GameUIAnimation*> animations_;
};
