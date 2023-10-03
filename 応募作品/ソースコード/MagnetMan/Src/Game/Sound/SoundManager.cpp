#include "SoundManager.h"
#include "DxLib.h"

int CSoundManager::sound_handle_[SOUND_ID_MAX] = { 0 };

void CSoundManager::Load(int group_id)
{
	const int* group = SOUND_GROUP[group_id];

	for (int i = 0; i < SOUND_ID_MAX; i++, group++) {
		int index = (*group);
		if (index < 0 || index > SOUND_ID_MAX) break;

		sound_handle_[index] = LoadSoundMem(SOUND_DATABASE[index].file_path);
	}
}

void CSoundManager::PlaySE(int id)
{
	WaitHandleASyncLoad(sound_handle_[id]);
	PlaySoundMem(sound_handle_[id], DX_PLAYTYPE_BACK);
}

void CSoundManager::PlayBGM(int id)
{
	WaitHandleASyncLoad(sound_handle_[id]);
	PlaySoundMem(sound_handle_[id], DX_PLAYTYPE_LOOP);
}

void CSoundManager::DeleteSound(int group_id)
{
	const int* group = SOUND_GROUP[group_id];

	for (int i = 0; i < SOUND_ID_MAX; i++, group++) {
		int index = (*group);
		if (index < 0 || index > SOUND_ID_MAX) break;

		
		if (DeleteSoundMem(sound_handle_[index]) != -1)
		{
			sound_handle_[index] = 0;
		}
		
	}
}
