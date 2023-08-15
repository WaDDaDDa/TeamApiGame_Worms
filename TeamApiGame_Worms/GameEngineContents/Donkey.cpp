#include "Donkey.h"
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

Donkey::Donkey()
{

}

Donkey::~Donkey()
{

}

void Donkey::Start()
{
	Renderer = CreateRenderer(RenderOrder::Weapon);

	if (false == ResourcesManager::GetInst().IsLoadTexture("donkey.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("donkey.bmp"), 1, 1);
	}

	
	{
		//Collision
		BodyCollision = CreateCollision(CollisionOrder::Weapon);
		BodyCollision->SetCollisionScale({ 10, 10 });
		BodyCollision->SetCollisionType(CollisionType::CirCle);
	}

	Renderer->SetTexture("donkey.bmp");
	Renderer->Off();


	SetWeaponDamage(DonkeyDamage);
	SetWeaponSpeed(DonkeySpeed);


	ChangeState(DonkeyState::Max);
}

void Donkey::LevelStart()
{

}

void Donkey::Update(float _Delta)
{
	CameraFocus(_Delta);
	StateUpdate(_Delta);
}


void Donkey::StateUpdate(float _Delta)
{
	switch (State)
	{
	case DonkeyState::Idle:
		return IdleUpdate(_Delta);
	case DonkeyState::Fly:
		return FlyUpdate(_Delta);
	case DonkeyState::Jump:
		return JumpUpdate(_Delta);
	case DonkeyState::Bomb:
		return BombUpdate(_Delta);
	case DonkeyState::Damage:
		return DamageUpdate(_Delta);
	case DonkeyState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void Donkey::ChangeState(DonkeyState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case DonkeyState::Idle:
			IdleStart();
			break;
		case DonkeyState::Fly:
			FlyStart();
			break;
		case DonkeyState::Jump:
			JumpStart();
			break;
		case DonkeyState::Bomb:
			BombStart();
			break;
		case DonkeyState::Damage:
			DamageStart();
			break;
		case DonkeyState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

void Donkey::FlyStart()
{

}

void Donkey::FlyUpdate(float _Delta)
{
	GroundCheck(_Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (Color == RGB(0, 0, 255))
	{
		ChangeState(DonkeyState::Jump);
		return;
	}

	if (Color != RGB(255, 255, 255))
	{
		ChangeState(DonkeyState::Bomb);
		return;
	}
}

void Donkey::JumpStart()
{
	DonkeyBomb = CreateBombEffect<Range100>();
	SetGravityVector(float4::UP * DonkeySpeed);
	DonkeySpeed -= 120.0;
}
void Donkey::JumpUpdate(float _Delta)
{
	Gravity(_Delta);

	if (GetLiveTime() >= 0.1f)
	{
		ChangeState(DonkeyState::Fly);
	}
}

void Donkey::BombStart()
{
	//DonkeyBomb = CreateBombEffect<Range100>();
	//Renderer->Off();
}

void Donkey::BombUpdate(float _Delta)
{
	Gravity(_Delta);

	if (GetLiveTime() >= 0.2f)
	{
		ChangeState(DonkeyState::Damage);
		return;
	}

}

void Donkey::DamageStart()
{

}

void Donkey::DamageUpdate(float _Delta)
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

void Donkey::MaxStart()
{

}

void Donkey::MaxUpdate(float _Delta)
{
	ChangeState(DonkeyState::Idle);
	return;
}

void Donkey::IdleStart()
{
	TargetPos = Master->GetTargetPos();
	SetPos({ TargetPos.X, 800.0f });
	Renderer->On();
}

void Donkey::IdleUpdate(float _Delta)
{
	ChangeState(DonkeyState::Fly);
	return;
}