#pragma once
constexpr int PARAM_MAX = (1000);

class CFade 
{
public:
	enum FadeStatus
	{
		FADE_IN,
		FADE_OUT,
		FADE_END,
	};
public:
	static void Init();
	static void Step();
	static void Draw();
	static void Fin();
	static void FadeIn(int time = 60);
	static void FadeOut(int time = 60);
	static bool IsFadeEnd() { return status_ == FADE_END; }

private:
	static int handle_;
	static float param_;
	static float value_;
	static FadeStatus status_;
};
