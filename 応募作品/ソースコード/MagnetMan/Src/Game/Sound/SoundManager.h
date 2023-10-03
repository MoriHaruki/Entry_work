#pragma once
#include "SoundParameter.h"

class CSoundManager {

public:
	static void Load(int group_id);
	static void PlaySE(int id);			//Œø‰Ê‰¹Ä¶
	static void PlayBGM(int id);		//BGMÄ¶
	static void DeleteSound(int group_id);

private:
	static int sound_handle_[SOUND_ID_MAX];
};
