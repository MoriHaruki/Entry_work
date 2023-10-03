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

//	データ読み込み
void CField::LoadData()
{
	handle_ = MV1LoadModel(FIELD_DATA_BASE[TheFieldManager->GetID()].file_path);
	MV1SetupCollInfo(handle_);	// コリジョン情報構築
}

void CField::Step()
{
	//フィールドの座標設定
	MV1SetPosition(handle_, pos_);
}


//		更新処理
bool CField::HitCheck(Vector3D center, float radius, Vector3D* result)
{
	Vector3D	vOut = { 0.0f, 0.0f, 0.0f };	//　物体が背景にめり込んだ距離
	hit_flg_ = false;

	bool isfloor = false;
	bool iswall = false;

	MV1_COLL_RESULT_POLY_DIM	res;	// 当たり判定結果格納構造体
	res = MV1CollCheck_Sphere(handle_, -1, center, radius);	// 当たり判定結果格納

	if (res.HitNum != 0) hit_flg_ = true;
	// 当たったポリゴンの数だけ繰返す
	for (int i = 0; i < res.HitNum; i++)
	{
		//	ヒットしたポリゴンとヒットした物体のめり込んだ距離を求める
		Vector3D	vSub = VSub(res.Dim[i].HitPosition, center);
		float	fLen = VSize(vSub);

		if (res.Dim[i].Normal.y >= 0.5f) //地面0.5より上にいるとジャンプできる
		{
			isfloor = true;
		}
		
		fLen = radius - fLen;
		// めり込んだ距離分だけ外に押し出す　押し出す方向は法線の方向
		Vector3D	vLine = VScale(res.Dim[i].Normal, fLen);
		vOut = VAdd(vOut, vLine);
	}
	// 当たり判定結果を破棄する
	MV1CollResultPolyDimTerminate(res);
	*result = vOut;
	return isfloor && !iswall;
}

//		当たり判定
Vector3D CField::HitCheck(Vector3D start, Vector3D end)
{
	Vector3D	vOut = end;

	MV1_COLL_RESULT_POLY	res;	// 当たり判定結果格納構造体
	res = MV1CollCheck_Line(handle_, -1, start, end);	// 当たり判定結果格納

	// 障害物があった場合
	if (res.HitFlag == 1)
	{
		// 障害物とあたった場所へ移動
		vOut = res.HitPosition;
		// 上方向へ押し出す距離を計算し、加算する
		VECTOR v = VSub(end, res.HitPosition);
		float f = VSize(v);
		vOut.y += f;
	}

	return vOut;
}

//		描画処理
void CField::Draw()
{
	MV1DrawModel(handle_);
}

void CField::Fin()
{
	if (handle_ != -1)
	{
		MV1TerminateCollInfo(handle_);	//コリジョン情報破棄
		MV1DeleteModel(handle_);		//ステージモデル破棄
		handle_ = -1;
	}
}

