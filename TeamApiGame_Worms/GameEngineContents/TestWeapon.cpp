#include "TestWeapon.h"
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
#include "FlameEffect.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEnginecollision.h>
#include <GameEngineBase/GameEngineRandom.h>

TestWeapon::TestWeapon()
{

}

TestWeapon::~TestWeapon()
{

}

void TestWeapon::Start()
{
	Renderer = CreateRenderer(RenderOrder::Weapon);
	
	Renderer->SetTexture("Blank.bmp");

	{
		//Collision
		BodyCollision = CreateCollision(CollisionOrder::Weapon);

		BodyCollision->SetCollisionScale({ 10, 10 });
		BodyCollision->SetCollisionType(CollisionType::CirCle);
		//GrenadeCollision->SetCollisionPos({ 0, -10 });
		BodyCollision->Off();
	}

	SetWeaponDamage(TestWeaponDamage);
	SetWeaponSpeed(TestWeaponSpeed);

	IsWindOn();

	ChangeState(TestWeaponState::Max);
}

void TestWeapon::LevelStart()
{

}

void TestWeapon::Update(float _Delta)
{
	CameraFocus(_Delta);
	StateUpdate(_Delta);
}


void TestWeapon::StateUpdate(float _Delta)
{
	switch (State)
	{
	case TestWeaponState::Idle:
		return IdleUpdate(_Delta);
	case TestWeaponState::Fly:
		return FlyUpdate(_Delta);
	case TestWeaponState::Bomb:
		return BombUpdate(_Delta);
	case TestWeaponState::Damage:
		return DamageUpdate(_Delta);
	case TestWeaponState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void TestWeapon::ChangeState(TestWeaponState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case TestWeaponState::Idle:
			IdleStart();
			break;
		case TestWeaponState::Fly:
			FlyStart();
			break;
		case TestWeaponState::Bomb:
			BombStart();
			break;
		case TestWeaponState::Damage:
			DamageStart();
			break;
		case TestWeaponState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

void TestWeapon::FlyStart()
{
	for (size_t i = 0; i < 100; i++)
	{
		BombEffect* Flame = CreateBombEffect<FlameEffect>();
		float FireX = GameEngineRandom::MainRandom.RandomFloat(0.0f, 200.0f);
		float FireY = -(GameEngineRandom::MainRandom.RandomFloat(0.0f, 200.0f));
		Flame->SetGravityVector({ FireX, FireY });
	}
}

void TestWeapon::FlyUpdate(float _Delta)
{

	if (GetLiveTime() >= 5.0f)
	{
		ChangeState(TestWeaponState::Bomb);
		return;
	}

}

void TestWeapon::BombStart()
{

}

void TestWeapon::BombUpdate(float _Delta)
{
	if (true)
	{
		ChangeState(TestWeaponState::Damage);
		return;
	}
}

void TestWeapon::DamageStart()
{

}

void TestWeapon::DamageUpdate(float _Delta)
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

void TestWeapon::MaxStart()
{

}

void TestWeapon::MaxUpdate(float _Delta)
{
	ChangeState(TestWeaponState::Idle);
	return;
}

void TestWeapon::IdleStart()
{
	TargetPos = Master->GetTargetPos();
	SetPos(TargetPos);
	Renderer->On();
}

void TestWeapon::IdleUpdate(float _Delta)
{
	ChangeState(TestWeaponState::Fly);
	return;
}