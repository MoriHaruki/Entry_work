#pragma once

#include "Vector/Vector3D.h"

// AABB(ボックス)
struct AABB {
	Vector3D	pos;	// 中心点
	Vector3D	half;	// 各軸の辺の長さの半分

	// コンストラクタ
	AABB()
		: pos()
		, half()
	{}

	AABB(const Vector3D& p, const Vector3D& hl)
		: pos(p)
		, half(hl)
	{}
};