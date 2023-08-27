#include "AirStrikeMissile.h"
#include "Ground.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "PlayLevel.h"
#include "GameTurn.h"
#include "Range25.h"
#include "Range50.h"
#include "Range75.h"
#include "Range100.h"
#include "FlyEffect.h"
#include "Airjet.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEnginecollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

int AirStrikeMissile::CountValue = 0;
Airjet* AirStrikeMissile::AirJet;


AirStrikeMissile::AirStrikeMissile()
{

}

AirStrikeMissile::~AirStrikeMissile()
{

}

void AirStrikeMissile::Start()
{
	Renderer = CreateRenderer(RenderOrder::Weapon);

	if (false == ResourcesManager::GetInst().IsLoadTexture("airmisl.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("airmisl.bmp"), 1, 32);
	}

	// 사운드 로드
	if (nullptr == GameEngineSound::FindSound("WeaponHoming.WAV"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Effects\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("WeaponHoming.WAV"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Rocketrelease.WAV"));
	}
	
	Renderer->SetTexture("Blank.bmp");


	{ // RockOn 이후
	// 90도
		Renderer->CreateAnimation("8_AirStrikeMissile2_Fly", "airmisl.bmp", 0, 0, 0.05f, false);
		// 78.75도								 
		Renderer->CreateAnimation("7_AirStrikeMissile2_Fly", "airmisl.bmp", 1, 1, 0.05f, false);
		// 67.5도								 
		Renderer->CreateAnimation("6_AirStrikeMissile2_Fly", "airmisl.bmp", 2, 2, 0.05f, false);
		// 56.25도								 
		Renderer->CreateAnimation("5_AirStrikeMissile2_Fly", "airmisl.bmp", 3, 3, 0.05f, false);
		// 45 도									 
		Renderer->CreateAnimation("4_AirStrikeMissile2_Fly", "airmisl.bmp", 4, 4, 0.05f, false);
		// 33.75도								 
		Renderer->CreateAnimation("3_AirStrikeMissile2_Fly", "airmisl.bmp", 5, 5, 0.05f, false);
		// 22,5도								 
		Renderer->CreateAnimation("2_AirStrikeMissile2_Fly", "airmisl.bmp", 6, 6, 0.05f, false);
		// 11.25도								 
		Renderer->CreateAnimation("1_AirStrikeMissile2_Fly", "airmisl.bmp", 7, 7, 0.05f, false);
		// 0도									 
		Renderer->CreateAnimation("0_AirStrikeMissile2_Fly", "airmisl.bmp", 8, 8, 0.05f, false);
		// -11.25도								 
		Renderer->CreateAnimation("31_AirStrikeMissile2_Fly", "airmisl.bmp", 9, 9, 0.05f, false);
		// -22.5도								 
		Renderer->CreateAnimation("30_AirStrikeMissile2_Fly", "airmisl.bmp", 10, 10, 0.05f, false);
		// -33.75도								 
		Renderer->CreateAnimation("29_AirStrikeMissile2_Fly", "airmisl.bmp", 11, 11, 0.05f, false);
		// -45도									 
		Renderer->CreateAnimation("28_AirStrikeMissile2_Fly", "airmisl.bmp", 12, 12, 0.05f, false);
		// -56.25도								 
		Renderer->CreateAnimation("27_AirStrikeMissile2_Fly", "airmisl.bmp", 13, 13, 0.05f, false); 
		// -67.5도								 
		Renderer->CreateAnimation("26_AirStrikeMissile2_Fly", "airmisl.bmp", 14, 14, 0.05f, false);//  오른쪽 방향
		// -78.75도								 
		Renderer->CreateAnimation("25_AirStrikeMissile2_Fly", "airmisl.bmp", 15, 15, 0.05f, false);
		// -90 도								 
		Renderer->CreateAnimation("24_AirStrikeMissile2_Fly", "airmisl.bmp", 16, 16, 0.05f, false); // 수직 낙하
		// -101.25 도							 
		Renderer->CreateAnimation("23_AirStrikeMissile2_Fly", "airmisl.bmp", 17, 17, 0.05f, false); 
		// -112.5도								 
		Renderer->CreateAnimation("22_AirStrikeMissile2_Fly", "airmisl.bmp", 18, 18, 0.05f, false);//  왼쪽 방향
		// -123.75도								 
		Renderer->CreateAnimation("21_AirStrikeMissile2_Fly", "airmisl.bmp", 19, 19, 0.05f, false);
		// -135도								 
		Renderer->CreateAnimation("20_AirStrikeMissile2_Fly", "airmisl.bmp", 20, 20, 0.05f, false);
		// -146.25도								 
		Renderer->CreateAnimation("19_AirStrikeMissile2_Fly", "airmisl.bmp", 21, 21, 0.05f, false);
		//-157.5								  
		Renderer->CreateAnimation("18_AirStrikeMissile2_Fly", "airmisl.bmp", 22, 22, 0.05f, false);
		//-168.75								  
		Renderer->CreateAnimation("17_AirStrikeMissile2_Fly", "airmisl.bmp", 23, 23, 0.05f, false);
		//-180									  
		Renderer->CreateAnimation("16_AirStrikeMissile2_Fly", "airmisl.bmp", 24, 24, 0.05f, false);
		//-191.25								  
		Renderer->CreateAnimation("15_AirStrikeMissile2_Fly", "airmisl.bmp", 25, 25, 0.05f, false);
		//-202.5								  
		Renderer->CreateAnimation("14_AirStrikeMissile2_Fly", "airmisl.bmp", 26, 26, 0.05f, false);
		//-213.75								  
		Renderer->CreateAnimation("13_AirStrikeMissile2_Fly", "airmisl.bmp", 27, 27, 0.05f, false);
		//-225									  
		Renderer->CreateAnimation("12_AirStrikeMissile2_Fly", "airmisl.bmp", 28, 28, 0.05f, false);
		//-236.25								  
		Renderer->CreateAnimation("11_AirStrikeMissile2_Fly", "airmisl.bmp", 29, 29, 0.05f, false);
		//-247.5								  
		Renderer->CreateAnimation("10_AirStrikeMissile2_Fly", "airmisl.bmp", 30, 30, 0.05f, false);
		//-258.75								  
		Renderer->CreateAnimation("9_AirStrikeMissile2_Fly", "airmisl.bmp", 31, 31, 0.05f, false);
		//// -270
		//Renderer->CreateAnimation("AirStrikeMissile_Fly", "airmisl.bmp", 32, 32, 0.05f, false);
	}

	{
		//Collision
		BodyCollision = CreateCollision(CollisionOrder::Weapon);
		BodyCollision->SetCollisionScale({ 10, 10 });
		BodyCollision->SetCollisionType(CollisionType::CirCle);
		//GrenadeCollision->SetCollisionPos({ 0, -10 });
		BodyCollision->Off();
	}

	SoundEffect = GameEngineSound::SoundPlay("petrol.WAV");
	//Renderer->ChangeAnimation("24_AirStrikeMissile2_Fly");
	SetWeaponDamage(AirStrikeMissileDamage);
	SetWeaponSpeed(AirStrikeMissileSpeed);

	IsWindOn();

	ChangeState(AirStrikeMissileState::Max);
}

void AirStrikeMissile::LevelStart()
{

}

void AirStrikeMissile::Update(float _Delta)
{
	StateUpdate(_Delta);
}


void AirStrikeMissile::StateUpdate(float _Delta)
{
	switch (State)
	{
	case AirStrikeMissileState::Fly:
		return FlyUpdate(_Delta);
	case AirStrikeMissileState::Idle:
		return IdleUpdate(_Delta);
	case AirStrikeMissileState::Bomb:
		return BombUpdate(_Delta);
	case AirStrikeMissileState::Damage:
		return DamageUpdate(_Delta);
	case AirStrikeMissileState::InWater:
		return InWaterUpdate(_Delta);
	case AirStrikeMissileState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void AirStrikeMissile::ChangeState(AirStrikeMissileState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case AirStrikeMissileState::Fly:
			FlyStart();
			break;
		case AirStrikeMissileState::Idle:
			IdleStart();
			break;
		case AirStrikeMissileState::Bomb:
			BombStart();
			break;
		case AirStrikeMissileState::Damage:
			DamageStart();
			break;
		case AirStrikeMissileState::InWater:
			InWaterStart();
			break;
		case AirStrikeMissileState::Max:
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
void AirStrikeMissile::DirCheck()
{
	
	if (GetGravityVector().X < 0.0f)
	{
		Renderer->ChangeAnimation("22_AirStrikeMissile2_Fly");

	}
	else if (GetGravityVector().X > 0.0f)
	{
		Renderer->ChangeAnimation("26_AirStrikeMissile2_Fly");
	}
	else if (GetGravityVector().X == 0.0f)
	{
		Renderer->ChangeAnimation("24_AirStrikeMissile2_Fly");

	}
}

void AirStrikeMissile::FlyStart()
{
	SetGravityVector(AngleVec.GetRotationToDegZ(Master->GetCurAngle()) * GetChargingSpeed());
	Renderer->On();

}

void AirStrikeMissile::FlyUpdate(float _Delta)
{

	if (CountValue == 0)
	{
		CameraFocus(_Delta);
	}

	DirCheck();
	Gravity(_Delta);

	EffectTime += _Delta;

	if (EffectTime >= EffectInterval)
	{
		CreateBombEffect<FlyEffect>();
		EffectTime = 0.0f;
	}

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (Color != RGB(255, 255, 255))
	{
		ChangeState(AirStrikeMissileState::Bomb);
		return;
	}

	if (GetLiveTime() >= 0.1f)
	{
		BodyCollision->On();
	}

	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollision->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::Rect
		, CollisionType::CirCle
	))
	{
		ChangeState(AirStrikeMissileState::Bomb);
		return;
	}

	// 물에 빠짐
	if (GetPos().Y >= 1875)
	{
		ChangeState(AirStrikeMissileState::InWater);
		return;
	}
}

void AirStrikeMissile::BombStart()
{
	AirStrikeMissileBomb = CreateBombEffect<Range50>();
	SoundEffect = GameEngineSound::SoundPlay("Explosion1.WAV");

	Renderer->Off();
}

void AirStrikeMissile::BombUpdate(float _Delta)
{
	if (true == AirStrikeMissileBomb->GetRenderer()->IsAnimationEnd())
	{
		ChangeState(AirStrikeMissileState::Damage);
		return;
	}
}

void AirStrikeMissile::DamageStart()
{

}

void AirStrikeMissile::DamageUpdate(float _Delta)
{
	size_t PlayerCount = Player::GetAllPlayer().size();
	int PlayerStateCount = 0;
	for (size_t i = 0; i < PlayerCount; i++)
	{
		if (PlayerState::Idle == Player::GetAllPlayer()[i]->GetState() || PlayerState::DeathEnd == Player::GetAllPlayer()[i]->GetState())
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

void AirStrikeMissile::InWaterStart()
{
	SoundEffect = GameEngineSound::SoundPlay("splish.WAV");

	SetGravityVector(float4::DOWN);
	IsWindOff();
	SetGravityPower(100.0f);
	DirCheck();
}

void AirStrikeMissile::InWaterUpdate(float _Delta)
{
	Gravity(_Delta);

	if (GetLiveTime() >= 3.0f)
	{
		size_t PlayerCount = Player::GetAllPlayer().size();
		int PlayerStateCount = 0;
		for (size_t i = 0; i < PlayerCount; i++)
		{
			if (PlayerState::Idle == Player::GetAllPlayer()[i]->GetState() || PlayerState::DeathEnd == Player::GetAllPlayer()[i]->GetState())
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
		return;
	}
}

void AirStrikeMissile::MaxStart()
{

}

void AirStrikeMissile::MaxUpdate(float _Delta)
{
	ChangeState(AirStrikeMissileState::Idle);
	return;
}

void AirStrikeMissile::IdleStart()
{
	TargetPos = Master->GetTargetPos();
	if (CountValue == 0) // 가운데
	{
		AirJet = GetLevel()->CreateActor<Airjet>();
		AirJet->SetMaster(Master);
		if (PlayerDir::Left == Master->GetPlayerDir())
		{
			float ImageX = GetGroundTexture()->GetScale().X - 1280.0f;
			AirJet->SetPos({ ImageX + 500.0f , 700.0f});

		}
		else if (PlayerDir::Right == Master->GetPlayerDir())
		{
			AirJet->SetPos({ 0.0f , 700.0f });
		}
		SetPos({ TargetPos.X, 800.0f });
		CountValue++;
	}
	else if (CountValue == 1) //왼쪽
	{
		SetPos({ TargetPos.X - 100.0f, 800.0f });
		CountValue++;
	}
	else if (CountValue == 2) // 오른쪽
	{
		SetPos({ TargetPos.X + 100.0f, 800.0f });
		CountValue = 0;
	}

}

void AirStrikeMissile::IdleUpdate(float _Delta)
{
	if (CountValue == 0)
	{
		CameraFocus(_Delta);
	}

	if (PlayerDir::Left == Master->GetPlayerDir())
	{
		if (AirJet->GetPos().X <= TargetPos.X)
		{
			SetGravityVector({-100.0f , 0.0f});
			ChangeState(AirStrikeMissileState::Fly);
			return;
		}

	}
	else if (PlayerDir::Right == Master->GetPlayerDir())
	{
		if (AirJet->GetPos().X >= TargetPos.X)
		{
			SetGravityVector({ 100.0f , 0.0f });
			ChangeState(AirStrikeMissileState::Fly);
			return;
		}
	}

	//ChangeState(AirStrikeMissileState::Fly);
	//return;
}