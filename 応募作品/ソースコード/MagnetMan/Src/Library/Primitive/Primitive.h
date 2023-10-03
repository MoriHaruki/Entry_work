#pragma once

#include "Vector/Vector3D.h"

// AABB(�{�b�N�X)
struct AABB {
	Vector3D	pos;	// ���S�_
	Vector3D	half;	// �e���̕ӂ̒����̔���

	// �R���X�g���N�^
	AABB()
		: pos()
		, half()
	{}

	AABB(const Vector3D& p, const Vector3D& hl)
		: pos(p)
		, half(hl)
	{}
};