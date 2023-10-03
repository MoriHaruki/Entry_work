#pragma once

#include "Singleton/Singleton.h"
#include "Box.h"
#include"MinusBox.h"
#include"PlusBox.h"
#include <list>
#include <vector>
#include "Common.h"

//�C���X�^���X�ւ̃}�N���A�N�Z�X
#define BoxManagerInstance MyLib::Singleton<CBoxManager>
//�C���X�^���X�Ăяo���ȗ���
#define TheBoxManager MyLib::Singleton<CBoxManager>::Get()

class CBoxManager
{
private:
	//�A�N�Z�X�����t�^
	friend MyLib::Singleton<CBoxManager>;

private:
	CBoxManager();
	~CBoxManager();

public:
	static void CreatePrototypes();

	void Init();
	void SetBox();					//BOX���Z�b�g����
	CBox* CreateBOX(int id);	//BOX���쐬����
	void Load();
	void Step();
	void StepAttract();
	void Draw();
	void Delete();
	void Fin();
	void StepChenckChengeBox();		//��ɔ��̎�ނ�ύX�������m�F����
	void StepCheckAttractBoxs();	//�{�b�N�X���m�������񂹂鏈��
	void BoxCollision();			//�����m�̓����蔻��

private:
	static CBox* CreatePrototype(int id);
	std::list<CBox*> boxs_;
	static inline std::vector<CBox*> prototype_box_;
};