#include "HomingMissile.h"
#include "Ground.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "PlayLevel.h"
#include "GameTurn.h"
#include "Range25.h"
#include "Range50.h"
#include "Range75.h"
#include "Range100.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEnginecollision.h>

HomingMissile::HomingMissile()
{

}

HomingMissile::~HomingMissile()
{

}

void HomingMissile::Start()
{
	Renderer = CreateRenderer(RenderOrder::Weapon);

	if (false == ResourcesManager::GetInst().IsLoadTexture("hmissil1.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("hmissil1.bmp"), 1, 32);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("hmissil2.bmp"), 1, 32);
	}

	
	Renderer->SetTexture("Blank.bmp");

	{ // RockOn 이전
		// 공회전
		Renderer->CreateAnimation("Idle_HomingMissile_Fly", "hmissil1.bmp", 0, 31, 0.005f, true);
	}

	{ // RockOn 이후
	// 90도
		Renderer->CreateAnimation("8_HomingMissile2_Fly", "hmissil2.bmp", 0, 0, 0.05f, false);
		// 78.75도								 
		Renderer->CreateAnimation("7_HomingMissile2_Fly", "hmissil2.bmp", 1, 1, 0.05f, false);
		// 67.5도								 
		Renderer->CreateAnimation("6_HomingMissile2_Fly", "hmissil2.bmp", 2, 2, 0.05f, false);
		// 56.25도								 
		Renderer->CreateAnimation("5_HomingMissile2_Fly", "hmissil2.bmp", 3, 3, 0.05f, false);
		// 45 도									 
		Renderer->CreateAnimation("4_HomingMissile2_Fly", "hmissil2.bmp", 4, 4, 0.05f, false);
		// 33.75도								 
		Renderer->CreateAnimation("3_HomingMissile2_Fly", "hmissil2.bmp", 5, 5, 0.05f, false);
		// 22,5도								 
		Renderer->CreateAnimation("2_HomingMissile2_Fly", "hmissil2.bmp", 6, 6, 0.05f, false);
		// 11.25도								 
		Renderer->CreateAnimation("1_HomingMissile2_Fly", "hmissil2.bmp", 7, 7, 0.05f, false);
		// 0도									 
		Renderer->CreateAnimation("0_HomingMissile2_Fly", "hmissil2.bmp", 8, 8, 0.05f, false);
		// -11.25도								 
		Renderer->CreateAnimation("31_HomingMissile2_Fly", "hmissil2.bmp", 9, 9, 0.05f, false);
		// -22.5도								 
		Renderer->CreateAnimation("30_HomingMissile2_Fly", "hmissil2.bmp", 10, 10, 0.05f, false);
		// -33.75도								 
		Renderer->CreateAnimation("29_HomingMissile2_Fly", "hmissil2.bmp", 11, 11, 0.05f, false);
		// -45도									 
		Renderer->CreateAnimation("28_HomingMissile2_Fly", "hmissil2.bmp", 12, 12, 0.05f, false);
		// -56.25도								 
		Renderer->CreateAnimation("27_HomingMissile2_Fly", "hmissil2.bmp", 13, 13, 0.05f, false);
		// -67.5도								 
		Renderer->CreateAnimation("26_HomingMissile2_Fly", "hmissil2.bmp", 14, 14, 0.05f, false);
		// -78.75도								 
		Renderer->CreateAnimation("25_HomingMissile2_Fly", "hmissil2.bmp", 15, 15, 0.05f, false);
		// -90 도								 
		Renderer->CreateAnimation("24_HomingMissile2_Fly", "hmissil2.bmp", 16, 16, 0.05f, false);
		// -101.25 도							 
		Renderer->CreateAnimation("23_HomingMissile2_Fly", "hmissil2.bmp", 17, 17, 0.05f, false);
		// -112.5도								 
		Renderer->CreateAnimation("22_HomingMissile2_Fly", "hmissil2.bmp", 18, 18, 0.05f, false);
		// -123.75도								 
		Renderer->CreateAnimation("21_HomingMissile2_Fly", "hmissil2.bmp", 19, 19, 0.05f, false);
		// -135도								 
		Renderer->CreateAnimation("20_HomingMissile2_Fly", "hmissil2.bmp", 20, 20, 0.05f, false);
		// -146.25도								 
		Renderer->CreateAnimation("19_HomingMissile2_Fly", "hmissil2.bmp", 21, 21, 0.05f, false);
		//-157.5								  
		Renderer->CreateAnimation("18_HomingMissile2_Fly", "hmissil2.bmp", 22, 22, 0.05f, false);
		//-168.75								  
		Renderer->CreateAnimation("17_HomingMissile2_Fly", "hmissil2.bmp", 23, 23, 0.05f, false);
		//-180									  
		Renderer->CreateAnimation("16_HomingMissile2_Fly", "hmissil2.bmp", 24, 24, 0.05f, false);
		//-191.25								  
		Renderer->CreateAnimation("15_HomingMissile2_Fly", "hmissil2.bmp", 25, 25, 0.05f, false);
		//-202.5								  
		Renderer->CreateAnimation("14_HomingMissile2_Fly", "hmissil2.bmp", 26, 26, 0.05f, false);
		//-213.75								  
		Renderer->CreateAnimation("13_HomingMissile2_Fly", "hmissil2.bmp", 27, 27, 0.05f, false);
		//-225									  
		Renderer->CreateAnimation("12_HomingMissile2_Fly", "hmissil2.bmp", 28, 28, 0.05f, false);
		//-236.25								  
		Renderer->CreateAnimation("11_HomingMissile2_Fly", "hmissil2.bmp", 29, 29, 0.05f, false);
		//-247.5								  
		Renderer->CreateAnimation("10_HomingMissile2_Fly", "hmissil2.bmp", 30, 30, 0.05f, false);
		//-258.75								  
		Renderer->CreateAnimation("9_HomingMissile2_Fly", "hmissil2.bmp", 31, 31, 0.05f, false);
		//// -270
		//Renderer->CreateAnimation("HomingMissile_Fly", "hmissil2.bmp", 32, 32, 0.05f, false);
	}

	SetWeaponDamage(HomingMissileDamage);
	SetWeaponSpeed(HomingMissileSpeed);

	IsWindOn();

	ChangeState(HomingMissileState::Max);
}

void HomingMissile::LevelStart()
{

}

void HomingMissile::Update(float _Delta)
{
	CameraFocus(_Delta);
	StateUpdate(_Delta);
}


void HomingMissile::StateUpdate(float _Delta)
{
	switch (State)
	{
	case HomingMissileState::Fly:
		return FlyUpdate(_Delta);
	case HomingMissileState::RockOnFly:
		return RockOnFlyUpdate(_Delta);
	case HomingMissileState::Bomb:
		return BombUpdate(_Delta);
	case HomingMissileState::Damage:
		return DamageUpdate(_Delta);
	case HomingMissileState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void HomingMissile::ChangeState(HomingMissileState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case HomingMissileState::Fly:
			FlyStart();
			break;
		case HomingMissileState::RockOnFly:
			RockOnFlyStart();
			break;
		case HomingMissileState::Bomb:
			BombStart();
			break;
		case HomingMissileState::Damage:
			DamageStart();
			break;
		case HomingMissileState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

// 타겟 방향으로 날라가는 것.
void HomingMissile::DirCheck()
{
	Dir = TargetPos - GetPos();
	float CurDir = Dir.AngleDeg();

	float CheckDir = CurDir / 11.25f;

	std::string Text = "";

	switch (static_cast<int>(CheckDir))
	{
	case 0:
		Renderer->ChangeAnimation("0_HomingMissile2_Fly");
		break;
	case 1:
		Renderer->ChangeAnimation("1_HomingMissile2_Fly");
		break;
	case 2:
		Renderer->ChangeAnimation("2_HomingMissile2_Fly");
		break;
	case 3:
		Renderer->ChangeAnimation("3_HomingMissile2_Fly");
		break;
	case 4:
		Renderer->ChangeAnimation("4_HomingMissile2_Fly");
		break;
	case 5:
		Renderer->ChangeAnimation("5_HomingMissile2_Fly");
		break;
	case 6:
		Renderer->ChangeAnimation("6_HomingMissile2_Fly");
		break;
	case 7:
		Renderer->ChangeAnimation("7_HomingMissile2_Fly");
		break;
	case 8:
		Renderer->ChangeAnimation("8_HomingMissile2_Fly");
		break;
	case 9:
		Renderer->ChangeAnimation("9_HomingMissile2_Fly");
		break;
	case 10:
		Renderer->ChangeAnimation("10_HomingMissile2_Fly");
		break;
	case 11:
		Renderer->ChangeAnimation("11_HomingMissile2_Fly");
		break;
	case 12:
		Renderer->ChangeAnimation("12_HomingMissile2_Fly");
		break;
	case 13:
		Renderer->ChangeAnimation("13_HomingMissile2_Fly");
		break;
	case 14:
		Renderer->ChangeAnimation("14_HomingMissile2_Fly");
		break;
	case 15:
		Renderer->ChangeAnimation("15_HomingMissile2_Fly");
		break;
	case 16:
		Renderer->ChangeAnimation("16_HomingMissile2_Fly");
		break;
	case 17:
		Renderer->ChangeAnimation("17_HomingMissile2_Fly");
		break;
	case 18:
		Renderer->ChangeAnimation("18_HomingMissile2_Fly");
		break;
	case 19:
		Renderer->ChangeAnimation("19_HomingMissile2_Fly");
		break;
	case 20:
		Renderer->ChangeAnimation("20_HomingMissile2_Fly");
		break;
	case 21:
		Renderer->ChangeAnimation("21_HomingMissile2_Fly");
		break;
	case 22:
		Renderer->ChangeAnimation("22_HomingMissile2_Fly");
		break;
	case 23:
		Renderer->ChangeAnimation("23_HomingMissile2_Fly");
		break;
	case 24:
		Renderer->ChangeAnimation("24_HomingMissile2_Fly");
		break;
	case 25:
		Renderer->ChangeAnimation("25_HomingMissile2_Fly");
		break;
	case 26:
		Renderer->ChangeAnimation("26_HomingMissile2_Fly");
		break;
	case 27:
		Renderer->ChangeAnimation("27_HomingMissile2_Fly");
		break;
	case 28:
		Renderer->ChangeAnimation("28_HomingMissile2_Fly");
		break;
	case 29:
		Renderer->ChangeAnimation("29_HomingMissile2_Fly");
		break;
	case 30:
		Renderer->ChangeAnimation("30_HomingMissile2_Fly");
		break;
	case 31:
		Renderer->ChangeAnimation("31_HomingMissile2_Fly");
		break;
	default:
		break;
	}
}

void HomingMissile::FlyStart()
{
	SetGravityVector(AngleVec.GetRotationToDegZ(Master->GetCurAngle()) * GetChargingSpeed());
	Renderer->ChangeAnimation("Idle_HomingMissile_Fly");
}

void HomingMissile::FlyUpdate(float _Delta)
{
	Gravity(_Delta);

	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(HomingMissileState::RockOnFly);
		return;
	}

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (Color != RGB(255, 255, 255))
	{
		ChangeState(HomingMissileState::Bomb);
		return;
	}
}

void HomingMissile::RockOnFlyStart()
{
	TargetPos = Master->GetTargetPos();
	DirCheck();
	Dir.Normalize();
	MissileDir = Dir.AngleDeg();
}

void HomingMissile::RockOnFlyUpdate(float _Delta)
{
	AddPos(float4::RIGHT.GetRotationToDegZ(-MissileDir) * HomingMissileRockOnSpeed * _Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255) || GetLiveTime() >= 5.0f);
	if (Color != RGB(255, 255, 255))
	{
		ChangeState(HomingMissileState::Bomb);
		return;
	}
}

void HomingMissile::BombStart()
{
	HomingMissileBomb = CreateBombEffect<Range50>();
	Renderer->Off();
}

void HomingMissile::BombUpdate(float _Delta)
{
	if (true == HomingMissileBomb->GetRenderer()->IsAnimationEnd())
	{
		ChangeState(HomingMissileState::Damage);
		return;
	}
}

void HomingMissile::DamageStart()
{

}

void HomingMissile::DamageUpdate(float _Delta)
{
	size_t PlayerCount = Player::GetAllPlayer().size();
	int PlayerStateCount = 0;
	for (size_t i = 0; i < PlayerCount; i++)
	{
		if (PlayerState::Idle == Player::GetAllPlayer()[i]->GetState()/* || PlayerState::Die == Player::GetAllPlayer()[i]->GetState()*/)
		{
			PlayerStateCount++;
		}
	}

	if (PlayerStateCount == PlayerCount)
	{
		// 무기사용이 종료되면 다시 플레이어로 돌아간다.
		Master->SwitchIsTurnPlayer();
		Death();
	}
}

void HomingMissile::MaxStart()
{

}

void HomingMissile::MaxUpdate(float _Delta)
{
	ChangeState(HomingMissileState::Fly);
	return;
}