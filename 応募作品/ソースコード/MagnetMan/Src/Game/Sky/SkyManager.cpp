#include "SkyManager.h"

CSkyManager::CSkyManager()
{
	sky_ = nullptr;
}

CSkyManager::~CSkyManager()
{
	Fin();
}

void CSkyManager::Init()
{
	
	if (sky_) 
	{
		sky_->Init();
	}
}

void CSkyManager::Load()
{
	if (sky_) 
	{
		sky_->Load();
	}
}

void CSkyManager::Step()
{
	if (sky_) 
	{
		sky_->Step();
	}
}

void CSkyManager::Update()
{
	if (sky_) 
	{
		sky_->Update();
	}
}

void CSkyManager::Draw()
{
	if (sky_) 
	{
		sky_->Draw();
	}
}

void CSkyManager::Delete()
{
	if (sky_) 
	{
		sky_->Delete();
		delete sky_;
		sky_ = nullptr;
	}
}

void CSkyManager::Fin()
{
	Delete();
}
