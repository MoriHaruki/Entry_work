#include "Player.h"
#include "Common.h"
#include "PlayerManager.h"
#include "Input/Input.h"
#include "Object/Bullet/BulletManager.h"
#include "Math/MyMath.h"
#include "Object/Obstacles/ObstaclesManager.h"
#include "Object/Obstacles/Obstacles.h"
#include "Object/Obstacles/GravityPlate.h"
#include "Input/InputManager.h"
#include "Field/FieldManager.h"
#include "Object/Box/BoxManager.h"
#include "Object/Obstacles/Lift.h"
#include "Collision/CollisionManager.h"
#include "Sound/SoundManager.h"

using namespace GAME_INPUT::ACTION;

namespace {
	//バレット
	constexpr Vector3D SMALL_BULLET_POS_OFFSET(0.0f, 1.0f, 1.0f);
	constexpr Vector3D MINUS_BULLET_POS_OFFSET(0.0f, 1.0f, 1.0f);
	const float FIRE_ROT_MAX_X = 0.08f;
	const float FIRE_ROT_MAX_Y = 0.06f;
}

CPlayer::CPlayer()
{
	handle_ = 0;
	memset(&move_, 0, sizeof(VECTOR));
	state_ = PLAYER_STATE_NORMAL;
	SetTag(IObject::PLAYER);
	bullet_timer_ = 0.0f;
	hp_ = 0.0f;
	box_collision_ = nullptr;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	handle_ = 0;
	state_ = PLAYER_STATE_NORMAL;
	plus_bullet_index_ = TheBulletManager->SetupBullet(BULLET_DATABASE[static_cast<int>(BulletID::BULLET_ID_PLAYER_PLUS)].id, BULLET_DATABASE[static_cast<int>(BulletID::BULLET_ID_PLAYER_PLUS)].id);
	minus_bullet_index_ = TheBulletManager->SetupBullet(BULLET_DATABASE[static_cast<int>(BulletID::BULLET_ID_PLAYER_MINUS)].id, BULLET_DATABASE[static_cast<int>(BulletID::BULLET_ID_PLAYER_MINUS)].id);
	hp_ = PLAY_HP;
	size_ = PLAYER_SIZE;
	box_collision_ = static_cast<BoxCollision*>(TheCollisionManager->CreateCollision((int)CollisionShape::COLLISION_SHAPE_BOX, (int)CollisionCategory::COLLISION_CATEGORY_PLAYER));
	box_collision_->SetSize(size_);
	box_collision_->SetOwner(this);
	rot_.y = DegreeToRadian(START_PLAYER_ROT);
}

void CPlayer::Init(Vector3D pos, Vector3D rot)
{
	pos_ = pos;
	rot_ = rot;
	Init();
}

void CPlayer::Load(const char* file_path)
{
	handle_ = MV1LoadModel(file_path);
		pos_ = DEFAULT_POS1;
}

void CPlayer::Delete()
{
	MV1DeleteModel(handle_);
	handle_ = 0;
}

void CPlayer::Step()
{
	CalcForward();

	RotByPad();
	MoveByKeyboard();

	MoveByPad();

	move_.y += ADD_GRAVITY;

	if (move_.y < MAX_GRAVITY)
	{
		move_.y = MAX_GRAVITY;
	}

	pos_ += move_;
	MV1SetRotationXYZ(handle_, rot_);
	MV1SetPosition(handle_, pos_);

	//プレイヤーとフィールド当たり判定
	auto field = TheFieldManager->GetNowField();

	Vector3D vVec(0.0f);
	
	//フィールドと当たっていたらジャンプできる
	if (field->HitCheck(pos_, PLAY_F, &vVec)) {
		if (state_ == PLAYER_STATE_FALL)
		{
			state_ = PLAYER_STATE_NORMAL;
		}
	}
	else 
	{
		state_ = PLAYER_STATE_FALL;
	}

	ReflectCollision(vVec);
}

void CPlayer::StepBullet()
{
	bullet_timer_ += CCommon::GetGameDeltaFrame();
	// バレット発射入力処理
	if (TheGameInputManager->IsKeep("FirePlusBullet"))
	{
		//発射時間になったら生成して発射
		if (bullet_timer_ >= BULLET_DATABASE[static_cast<int>(BulletID::BULLET_ID_PLAYER_PLUS)].bullet_interval)
		{
			PlusBullet();
			bullet_timer_ = 0.0f;
			CSoundManager::PlaySE(SOUND_ID_SE_PLAYER_BULLET_SHOT);
		}	
	}

    else if (TheGameInputManager->IsKeep("FireMinusBullet"))
	{
		if (bullet_timer_ >= BULLET_DATABASE[static_cast<int>(BulletID::BULLET_ID_PLAYER_MINUS)].bullet_interval)
		{
			MinusBullet();
			bullet_timer_ = 0.0f;
			CSoundManager::PlaySE(SOUND_ID_SE_PLAYER_BULLET_SHOT);
		}
	}
}

void CPlayer::PlusBullet()
{
	CBullet* bullet = nullptr;
	// PLUSバレット
	Vector3D pos_offset = SMALL_BULLET_POS_OFFSET;
	Vector3D fire_rot = rot_;
	pos_offset = VecRotation(pos_offset, fire_rot);
	Vector3D fire_pos = pos_ + pos_offset;
	bullet = TheBulletManager->CreateBullet(plus_bullet_index_);
	bullet->Fire(fire_pos, fire_rot, BULLET_DATABASE[static_cast<int>(BulletID::BULLET_ID_PLAYER_PLUS)].bullet_speed, 
		BULLET_DATABASE[static_cast<int>(BulletID::BULLET_ID_PLAYER_PLUS)].bullet_life);
}

void CPlayer::MinusBullet()
{
	CBullet* bullet = nullptr;
	//MINUSバレット
	Vector3D minus_pos_offset = MINUS_BULLET_POS_OFFSET;
	Vector3D minus_fire_rot = rot_;
	minus_pos_offset = VecRotation(minus_pos_offset, minus_fire_rot);
	Vector3D minus_fire_pos = pos_ + minus_pos_offset;
	bullet = TheBulletManager->CreateBullet(minus_bullet_index_);
	bullet->Fire(minus_fire_pos, minus_fire_rot, BULLET_DATABASE[static_cast<int>(BulletID::BULLET_ID_PLAYER_MINUS)].bullet_speed, 
		BULLET_DATABASE[static_cast<int>(BulletID::BULLET_ID_PLAYER_MINUS)].bullet_life);
}

void CPlayer::Draw()
{
	//DrawFormatString(0, 100, 0xffffff, "POS = (%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);
	MV1DrawModel(handle_);
}

void CPlayer::ReflectCollision(Vector3D vAddVec)
{
	//オールゼロなら何もしない
	if (vAddVec.x == 0.0f && vAddVec.y == 0.0f && vAddVec.z == 0.0f) return;
	if (state_ == PLAYER_STATE_NORMAL)
		move_.y = 0.0f;
	Vector3D	vPos = CPlayer::GetPos();
	vPos = VAdd(vPos, vAddVec);
	pos_ = vPos;
	MV1SetPosition(handle_, vPos);
}

//	当たり判定の中心位置取得
Vector3D CPlayer::GetCenter()
{
	Vector3D vCenter = CPlayer::GetPos();
	vCenter.y += 3.0f;
	return vCenter;
}

//		当たり判定の半径取得
float CPlayer::GetRadius()
{
	return 3.0f;
}

void CPlayer::OnCollisionEnter(CObject* another)
{
	//リフト、箱と衝突したら
	if (another->ObjectHasTag(IObject::LIFT))
	{
		//ジャンプを可能にする
		state_ = PLAYER_STATE_NORMAL;
	}

	if (another->ObjectHasTag(IObject::SHORT))
	{
		//ジャンプを可能にする
		state_ = PLAYER_STATE_NORMAL;
	}


	else if (another->ObjectHasTag(IObject::GRAVITY))
	{
		CSoundManager::PlaySE(SOUND_ID_SE_OBJECT_TRAMPOLINE);
		//ジャンプを可能にする
		state_ = PLAYER_STATE_NORMAL;
		//跳ね返り処理
		move_.y += GRAVITY_PLATE_JUMP;
		SetMove(move_);
	}
	
}

void CPlayer::MoveByKeyboard()
{

	if (state_ == PLAYER_STATE_NORMAL)
	{
		if (TheGameInputManager->IsPush(ACTION_NAME[IInputActionKind::JUMP]))
		{
			move_.y = JUMP_VALUE;
			state_ = PLAYER_STATE_FALL;
			CSoundManager::PlaySE(SOUND_ID_SE_PLAYER_JUMP);
		}
	}

	if (TheGameInputManager->IsKeep("MoveForward"))
	{
		Vector3D move(0.0f);
		move.x = sinf(rot_.y);
		move.z = cosf(rot_.y);
		pos_.x += move.x * -0.3f;
		pos_.z += move.z * -0.3f;
	}

	if (TheGameInputManager->IsKeep("MoveBack"))
	{
		Vector3D move(0.0f);
		move.x = sinf(rot_.y);
		move.z = cosf(rot_.y);
		pos_.x += move.x * 0.2f;
		pos_.z += move.z * 0.2f;
	}

	if (TheGameInputManager->IsKeep(ACTION_NAME[IInputActionKind::MOVE_LEFT]))
	{
		rot_.y -= DegreeToRadian(PLAYER_ROT);
	}

	if (TheGameInputManager->IsKeep(ACTION_NAME[IInputActionKind::MOVE_RIGHT]))
	{
		rot_.y +=  DegreeToRadian(PLAYER_ROT);
	}


}
//前進後退
void CPlayer::MoveByPad()
{
	CInputPad* pad = TheGameInputManager->GetInputPad();
	// 移動用のスティックコードを取得(右スティックを使用)
	Stick stick = TheGameInputManager->GetStickActionCode(GAME_INPUT::STICK::ACTION_NAME[static_cast<int>(GAME_INPUT::STICK::Kind::MOVE)]);
	if (pad->StickDir3D(stick).IsNearlyZero()) 
	{
		return;
	}

	float angle = pad->StickAngle(Vector::_3D, stick);
	Vector3D move = Matrix::GetYawMat(angle) * forward_*0.295f;
	//POSの移動
	pos_ -= move;
}
//パッドの左右操作
void CPlayer::RotByPad()
{
	CInputPad* pad = TheGameInputManager->GetInputPad();
	// 移動用のスティックコードを取得(右スティックを使用)
	Stick stick = TheGameInputManager->GetStickActionCode(GAME_INPUT::STICK::ACTION_NAME[static_cast<int>(GAME_INPUT::STICK::Kind::ROT)]);

	if (pad->StickDir3D(stick).IsNearlyZero())
	{
		return;
	}

	Vector2D rot = pad->StickDir2D(stick) * 0.05f;
	rot_.y += rot.x;
}

void CPlayer::CalcForward()
{
	Vector3D f;
	f.x = sinf(rot_.y );
	f.z = cosf(rot_.y ) ;
	forward_ = f;
}

void CPlayer::Fin()
{
	if (handle_ != 0)
	{
		Delete();
	}

	CSoundManager::DeleteSound(SOUND_GROUP_PLAY);
}