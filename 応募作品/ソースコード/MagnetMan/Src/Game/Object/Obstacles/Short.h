#pragma once

#include "Object/Obstacles/Obstacles.h"
#include "Collision/SphereCollision.h"

static constexpr float SHORT_BOX_W = (2.5f);	//” ‚Ì‰¡•
static constexpr float SHORT_BOX_H = (2.5f);	//” ‚Ì‚‚³
static constexpr float SHORT_BOX_D = (2.5f);	//” ‚Ì‰œs‚«
static constexpr float SHORT_BOX_F = (1.25f);	//” ‚Ì‰¡•”¼•ª;

class CShort : public CObstacles
{

public:

	CShort();
	~CShort();
	void Init() override;
	void Load() override;
	void Delete();
	void Step() override;
	void Draw() override;
	void Fin() override;
	CObstacles* Clone() override;
	void OnCollisionEnter(CObject* another) override;
private:
	void CreateCollision();

	float pre_offset_;
	float current_offset_;
};
