#include "DxLib.h"
#include "Common.h"

using namespace std;

int CCommon::old_time_ = 0;
float CCommon::delta_frame_ = 0;
mt19937 CCommon::mt_;


void CCommon::Init()
{
	old_time_ = GetNowCount();
}

void CCommon::Step()
{
	int now_time = GetNowCount();
	delta_frame_ = (float)(now_time - old_time_) / (1000 / GAME_FPS);

	old_time_ = now_time;
}

float CCommon::GetGameDeltaFrame()
{
#ifdef _DEBUG
	return 1;
#else
	return delta_frame_;
#endif
}

float CCommon::GetGameDeltaTime()
{
#ifdef _DEBUG
	return 1.f / GAME_FPS;
#else
	return delta_frame_ / GAME_FPS;
#endif
}

void CCommon::InitRandom()
{
	random_device rand;
	mt_.seed(rand());
}

int CCommon::GetRandom(int min_value, int max_value)
{
	int range = max_value - min_value + 1;
	return (mt_() % range) + min_value;
}

// ¬”“_‘æ5ˆÊ‚Ü‚Å‚Ì—”
float CCommon::GetRandom(float min_value, float max_value, int digit)
{
	int coe = 1;
	for (int i = 0; i < digit - 1; i++) {
		coe *= 10;
	}

	float min = (min_value)*coe;
	float max = (max_value)*coe;
	int range = static_cast<int>(max - min);

	// ƒ‰ƒ“ƒ_ƒ€”ÍˆÍ‚ª–³‚¢ê‡‚ÍÅ¬’l‚ğ•Ô‚·
	if (range == 0) return min;

	return ((mt_() % range) + min) / coe;
}
