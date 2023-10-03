#pragma once
#include "SoundParameter.h"

class CSoundManager {

public:
	static void Load(int group_id);
	static void PlaySE(int id);			//���ʉ��Đ�
	static void PlayBGM(int id);		//BGM�Đ�
	static void DeleteSound(int group_id);

private:
	static int sound_handle_[SOUND_ID_MAX];
};
