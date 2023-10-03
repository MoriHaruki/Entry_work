#pragma once

#define SKY_POS_Y (-10.0f)

enum SKY_ID
{
	SKY_ID_MONO,
	SKY_ID_NUM
};

struct SkyParameter
{
	const char FILE_PATH[128];
};

static const SkyParameter SKY_DATABASE[SKY_ID_NUM] = {
	"Data/Model/Sky/Sky.x"
};