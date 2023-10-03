#pragma once

#include "Object/Object.h"

class BoxCollision;

class CBullet : public CObject {
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Init();
	virtual void Load();
	virtual void Fire(Vector3D pos, Vector3D rot, float speed, float life);
	virtual void Step();
	virtual void Update();
	virtual void Draw();
	virtual void Delete();
	virtual void Fin();
	virtual CBullet* Clone() = 0;
	virtual void OnCollisionEnter(CObject* another) override;

protected:
	void CreateCollision();
	void SetHandle(int handle) { handle_ = handle; }

public:
	void SetPos(Vector3D pos) { pos_ = pos; }
	void SetRotation(Vector3D rot) { rot_ = rot; }
	void SetSpeed(float speed) { speed_ = speed; }
	void SetLife(float life) { life_ = life; }
	Vector3D GetPos() const { return pos_; }
	Vector3D GetRotation() const { return rot_; }
	float GetSpeed() const { return speed_; }
	float GetLife() const { return life_; }

protected:
	int id_;
	int handle_;
	Vector3D move_;
	float speed_;
	float life_;
	bool minus_flag_;
	bool plus_flag_;
	BoxCollision* collision_;
};
