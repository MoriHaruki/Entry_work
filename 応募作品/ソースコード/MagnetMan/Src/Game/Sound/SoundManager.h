#pragma once
#include "SoundParameter.h"

class CSoundManager {

public:
	static void Load(int group_id);
	static void PlaySE(int id);			//効果音再生
	static void PlayBGM(int id);		//BGM再生
	static void DeleteSound(int group_id);

private:
	static int sound_handle_[SOUND_ID_MAX];
};
