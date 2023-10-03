#include "Fade.h"
#include "DxLib.h"

int CFade::handle_ = 0;
float CFade::param_ = 0;
float CFade::value_ = 0;
CFade::FadeStatus CFade::status_ = FADE_END;

void CFade::Init()
{
	handle_ = LoadGraph("Data/Image/Fade/Fade.png");
}

// フェード更新
void CFade::Step()
{
	if (status_ == FADE_OUT) {
		param_ += value_;
		if (param_ >= PARAM_MAX) {
			param_ = PARAM_MAX;
			status_ = FADE_END;
		}
	}
	else if (status_ == FADE_IN) {
		param_ -= value_;
		if (param_ <= 0) {
			param_ = 0;
			status_ = FADE_END;
		}
	}
}

// フェード描画
void CFade::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)param_);
	DrawGraph(0, 0, handle_, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void CFade::Fin()
{
	DeleteGraph(handle_);
}

// フェードイン開始
void CFade::FadeIn(int time)
{
	param_ = PARAM_MAX;
	value_ = PARAM_MAX / (float)time;
	status_ = FADE_IN;
}

// フェードアウト開始
void CFade::FadeOut(int time)
{
	param_ = 0;
	value_ = PARAM_MAX / (float)time;
	status_ = FADE_OUT;
}