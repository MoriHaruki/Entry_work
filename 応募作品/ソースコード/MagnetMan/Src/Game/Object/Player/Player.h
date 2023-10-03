#pragma once
#include "PlayerParameterh.h"
#include "Object/Bullet/BulletParameter.h"
#include "Object/Object.h"
#include "Collision/BoxCollision.h"
#include "Vector/Vector3D.h"

enum PLAYER_STATE
{
	PLAYER_STATE_NORMAL,
	PLAYER_STATE_JUMP_UP,
	PLAYER_STATE_FALL
};

class CPlayer : public CObject
{
public:
	CPlayer();
	~CPlayer();
	void Init();
	void Init(Vector3D pos, Vector3D rot);
	void Load(const char* file_path);
	void Delete();
	void Step();
	void Draw();
	void Fin();
	void ReflectCollision(Vector3D vAddVec);
	Vector3D GetCenter();
	float GetRadius();

	void OnCollisionEnter(CObject* another);

private:
	void CalcForward();
private:
	void MoveByKeyboard();
	void MoveByPad();
	void RotByPad();
public:
	//バレット関連
	void StepBullet();
	void PlusBullet();
	void MinusBullet();
	

public:
	Vector3D GetPos() const { return pos_; }
	void SetPos(Vector3D pos) override { pos_ = pos; MV1SetPosition(handle_, pos_); }
	void SetState(int state) { state_ = state; }
	Vector3D GetRot() { return rot_; }
	void SetRot(Vector3D rot) { rot_ = rot; }
	int GetHandle() const { return handle_; }
	void SetHandle(int handle) { handle_ = handle; }
	Vector3D GetForward() const { return forward_; }
	Vector3D GetMove() const { return move_; }
	void SetMove(const Vector3D& move) { move_ = move; }


	
	
private:
	int          handle_;
	Vector3D	move_;
	Vector3D	forward_;
	int state_;
	float bullet_timer_;
	int plus_bullet_index_;
	int minus_bullet_index_;
	float		 hp_;
	BoxCollision* box_collision_;
};