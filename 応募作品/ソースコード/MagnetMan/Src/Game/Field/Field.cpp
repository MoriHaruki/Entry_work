#include "field.h"
#include "Field/FieldManager.h"
#include <math.h>

CField::CField() : handle_(-1), hit_flg_(false)
{
	MV1SetPosition(handle_,pos_);
}

CField::~CField()
{
}

void CField::Init()
{
	pos_ = VGet(0.0f, 1.0f, 0.0f);
}          

//	�f�[�^�ǂݍ���
void CField::LoadData()
{
	handle_ = MV1LoadModel(FIELD_DATA_BASE[TheFieldManager->GetID()].file_path);
	MV1SetupCollInfo(handle_);	// �R���W�������\�z
}

void CField::Step()
{
	//�t�B�[���h�̍��W�ݒ�
	MV1SetPosition(handle_, pos_);
}


//		�X�V����
bool CField::HitCheck(Vector3D center, float radius, Vector3D* result)
{
	Vector3D	vOut = { 0.0f, 0.0f, 0.0f };	//�@���̂��w�i�ɂ߂荞�񂾋���
	hit_flg_ = false;

	bool isfloor = false;
	bool iswall = false;

	MV1_COLL_RESULT_POLY_DIM	res;	// �����蔻�茋�ʊi�[�\����
	res = MV1CollCheck_Sphere(handle_, -1, center, radius);	// �����蔻�茋�ʊi�[

	if (res.HitNum != 0) hit_flg_ = true;
	// ���������|���S���̐������J�Ԃ�
	for (int i = 0; i < res.HitNum; i++)
	{
		//	�q�b�g�����|���S���ƃq�b�g�������̂̂߂荞�񂾋��������߂�
		Vector3D	vSub = VSub(res.Dim[i].HitPosition, center);
		float	fLen = VSize(vSub);

		if (res.Dim[i].Normal.y >= 0.5f) //�n��0.5����ɂ���ƃW�����v�ł���
		{
			isfloor = true;
		}
		
		fLen = radius - fLen;
		// �߂荞�񂾋����������O�ɉ����o���@�����o�������͖@���̕���
		Vector3D	vLine = VScale(res.Dim[i].Normal, fLen);
		vOut = VAdd(vOut, vLine);
	}
	// �����蔻�茋�ʂ�j������
	MV1CollResultPolyDimTerminate(res);
	*result = vOut;
	return isfloor && !iswall;
}

//		�����蔻��
Vector3D CField::HitCheck(Vector3D start, Vector3D end)
{
	Vector3D	vOut = end;

	MV1_COLL_RESULT_POLY	res;	// �����蔻�茋�ʊi�[�\����
	res = MV1CollCheck_Line(handle_, -1, start, end);	// �����蔻�茋�ʊi�[

	// ��Q�����������ꍇ
	if (res.HitFlag == 1)
	{
		// ��Q���Ƃ��������ꏊ�ֈړ�
		vOut = res.HitPosition;
		// ������։����o���������v�Z���A���Z����
		VECTOR v = VSub(end, res.HitPosition);
		float f = VSize(v);
		vOut.y += f;
	}

	return vOut;
}

//		�`�揈��
void CField::Draw()
{
	MV1DrawModel(handle_);
}

void CField::Fin()
{
	if (handle_ != -1)
	{
		MV1TerminateCollInfo(handle_);	//�R���W�������j��
		MV1DeleteModel(handle_);		//�X�e�[�W���f���j��
		handle_ = -1;
	}
}

