#pragma once
#include "DxLib.h"
#include "Object/Object.h"
#include "BoxParameter.h"
#include "Collision/BoxCollision.h"

class CBox : public CObject
{
public:

	CBox();
	virtual ~CBox();

	void Delete();
	virtual void  Init()	= 0;
	virtual void Load()		= 0;
	virtual void Step();
	virtual void Draw()		= 0;
	virtual void Fin()		= 0;
	virtual CBox* Clone()	= 0;

public:

	int GetHandle() const {return handle_;}
	BOX_STATE GetCurrenState ()const {return current_state_;}
	BOX_STATE GetNextState() const { return next_state_; }
	MOVE_STATE GetMoveState() const { return move_state_; }
	Collision* GetCollision() const { return collision_; }
	VECTOR GetMove() const { return move_; }
	void OnCollisionEnter(CObject* another) override;
	void SetMove(VECTOR move) { move_ = move; };
	void  SetNextState(BOX_STATE state) { next_state_ = state; };
	void SetMoveState(MOVE_STATE state) { move_state_ = state; }


protected:
	int handle_;
	BOX_STATE  current_state_;
	MOVE_STATE move_state_;
	float escape_speed_;
	VECTOR move_;
	BoxCollision* collision_;
	float radian_;

private:
	BOX_STATE next_state_;
	
};