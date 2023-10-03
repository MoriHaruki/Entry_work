#pragma once

#include "DxLib.h"
#include "Primitive/Primitive.h"
#include "ObjectParameter.h"

class CObject {

public:
	CObject();
	~CObject();

public:
	virtual void OnCollisionEnter(CObject* another);

public:
	void SetActive(bool active) { active_ = active; }
	virtual void SetPos(Vector3D pos) { pos_ = pos; }
	void SetRot(Vector3D rot) { rot_ = rot; }
	void SetSize(Vector3D size) { size_ = size; }
	void SetTag(int tag) { tag_ |= (1 << tag); }
	bool IsActive() const { return active_; }
	Vector3D GetPos() const { return pos_; }
	Vector3D GetRot() const { return rot_; }
	Vector3D GetSize() const { return size_; }
	AABB GetAABB() const { return AABB(pos_, size_ * 0.5f); }
	bool ObjectHasTag(int tag) const { return (tag_ & (1 << tag)); }
	void SetDeleteFlag(bool deleteflag) { is_delete_ = deleteflag; }

protected:
	Vector3D pos_;
	Vector3D rot_;
	Vector3D size_;
	
	bool is_delete_;
	bool active_;
private:
	int tag_;

};
