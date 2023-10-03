#include "Object.h"

CObject::CObject()
{
	active_ = true;
	pos_ = Vector3D::ZEROVec();
	rot_ = Vector3D::ZEROVec();
	size_ = Vector3D::ZEROVec();
	tag_ = 0;
	is_delete_ = false;
}

CObject::~CObject()
{
}

void CObject::OnCollisionEnter(CObject* another)
{

}