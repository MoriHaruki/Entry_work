#pragma once
#include "DxLib.h"
#include "Field/FieldManager.h"
//BOX関連
namespace BOX
{
	constexpr float BOX_HALF_SIZE = 1.0f;					//箱の半径;
	constexpr float BOX_MOVE_MIN = 1.5f;					// ボックスの移動時間
	constexpr float ACTIVE_DIST = 22.1f;					//引き寄せ範囲
	constexpr float DIST = 10.0f;							//Normalboxの移動範囲
	constexpr float BOX_W = 4.0f;							//箱の横幅
	constexpr float BOX_H = 4.0f;							//箱の高さ
	constexpr float BOX_D = 4.0f;							//箱の奥行き
	constexpr float BOX_F = BOX_W * 0.5f;					//箱の横幅半分;
	constexpr float	STOP_MOVE = 4.1f;						//一定以上近づかないようにするための数値


	constexpr int CREATE_BOX_NUM = 256;
}
struct  BoxParameter
{
	int id;
	VECTOR startpos;
};

enum class BOX_STATE
{
	NONE = -1,
	NORMAL,
	PLUS,
	MINUS,
	NUM
}; 

enum class MOVE_STATE {
	NONE = -1,
	MOVE,
	STOP,
};

constexpr BoxParameter BOX_DATABASE[IFIELD_ID::NUM][BOX::CREATE_BOX_NUM] =
{
	//ステージ１
	{
		//初期
		static_cast<int>(BOX_STATE::PLUS),{16.0f, 3.0f ,0.0f},
		static_cast<int>(BOX_STATE::PLUS),{16.0f,17.0f ,0.0f},

		static_cast<int>(BOX_STATE::NORMAL),{76.5f, 20.15f, 8.0f},
		static_cast<int>(BOX_STATE::PLUS),{98.5f, 20.15f, 8.0f},

		static_cast<int>(BOX_STATE::NORMAL),{122.5f, 32.25f,-4.0f},
		static_cast<int>(BOX_STATE::MINUS),{122.5f, 22.15f,  -4.0f},
		static_cast<int>(BOX_STATE::NONE),{0.0f,0.0f,0.0f},
	},
	
	//ステージ２
	{
		//初期
		static_cast<int>(BOX_STATE::PLUS),{26.0f, 3.0f ,0.0f},
		static_cast<int>(BOX_STATE::PLUS),{26.0f, 21.0f ,0.0f},

		static_cast<int>(BOX_STATE::PLUS),{122.0f, 17.5f, -9.0f},
		static_cast<int>(BOX_STATE::PLUS),{144.0f, 17.5f, -9.0f},

		static_cast<int>(BOX_STATE::MINUS),{265.0f, 36.5f, 0.0f},
		static_cast<int>(BOX_STATE::NORMAL),{280.0f, 38.5f, 0.0f},

		static_cast<int>(BOX_STATE::MINUS),{304.0f, 50.0f, 0.0f},
		static_cast<int>(BOX_STATE::NORMAL),{304.0f, 60.0f, 0.0f},

		
		
		static_cast<int>(BOX_STATE::NONE),{0.0f,0.0f,0.0f},
	},
};