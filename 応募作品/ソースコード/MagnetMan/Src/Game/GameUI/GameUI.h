#pragma once

//UIのベースとなるクラス
class CGameUI {
public:
	CGameUI();
	virtual ~CGameUI();

public:
	virtual void Init(float pos_x, float pos_y) = 0;
	virtual void Load(const char *file_path) = 0;
	virtual void Step() = 0;
	virtual void Draw() = 0;
	virtual void Delete() = 0;
	virtual void Fin() = 0;

	void SetPosX(float pos_x) { pos_x_ = pos_x; }
	void SetPosY(float pos_y) { pos_y_ = pos_y; }
	void SetAlpha(float alpha) { alpha_ = alpha; }

	float GetPosX() const { return pos_x_; }
	float GetPosY() const { return pos_y_; }
	float GetAlpha() const { return alpha_; }

protected:
	float pos_x_;
	float pos_y_;
	float alpha_;
};