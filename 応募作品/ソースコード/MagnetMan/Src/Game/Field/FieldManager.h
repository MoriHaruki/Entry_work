#pragma once

#include "Singleton/Singleton.h"
#include "Field.h"
#include <list>
#include "Common.h"

//�C���X�^���X�ւ̃}�N���A�N�Z�X
#define FieldManagerInstance MyLib::Singleton<CFieldManager>
//�C���X�^���X�Ăяo���ȗ���
#define TheFieldManager MyLib::Singleton<CFieldManager>::Get()

class CFieldManager
{
private:
	//�A�N�Z�X�����t�^
	friend MyLib::Singleton<CFieldManager>;

private:
	 CFieldManager();
	~ CFieldManager();
public:
	void Init();
	void Load();
	void Step();
	void Draw();
	void Fin();
	void StartField(int field_id);			//�X�e�[�W�̋N��
	void ChangeField(int change_id);			//�X�e�[�W�̐؂�ւ�
	CField* GetNowField() { return field_; }	//���݂̃X�e�[�W�f�[�^���擾

	int GetID() const { return id_; }	//ID�擾
	void SetID(int id) { id_ = id; }	//ID�ݒ�


private:
	CField*		field_;	//�t�B�[���h���N���X1�ŊǗ�����
	int			id_;	//�t�B�[���hID
};

