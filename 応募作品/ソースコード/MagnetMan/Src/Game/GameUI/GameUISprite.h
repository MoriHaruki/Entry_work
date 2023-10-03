#pragma once

#include "GameUI.h"

//UIスプライトクラス
class GameUISprite : public CGameUI {
public:
	GameUISprite();
	~GameUISprite();

public:
	void Init(float pos_x, float pos_y) override;
	void Load(const char *file_path) override;
	void Step() override;
	void Draw() override;
	void Delete() override;
	void Fin() override;

private:
	int handle_;
};

