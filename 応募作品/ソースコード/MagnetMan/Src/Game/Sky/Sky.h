#pragma once

#include <DxLib.h>
#include "Vector/Vector3D.h"

class CSky
{

public:
	CSky(int id);
	~CSky();

public:
	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Delete();
	void Fin();

private:
	int id_;
	int handle_;
	Vector3D pos_;
};
