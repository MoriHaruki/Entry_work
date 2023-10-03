#pragma once
// ボックスの当たり判定（AABB）

#include "Collision.h"
#include "Primitive/Primitive.h"

class BoxCollision : public Collision {
public:
	BoxCollision();
	virtual ~BoxCollision();

public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Fin() override;
	Collision* Clone() override;

	bool CheckCollision(Collision* another) override;

public:
	Vector3D GetSize() const { return size_; }

	void SetSize(Vector3D size) { size_(size); }
	void SetSize(float width, float height, float depth) { size_(width, height, depth); }

private:
	Vector3D size_;
};
