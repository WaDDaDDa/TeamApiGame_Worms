#include "Self_Bomb.h"
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

Self_Bomb::Self_Bomb()
{

}

Self_Bomb::~Self_Bomb()
{

}

void Self_Bomb::Start()
{

	SetWeaponDamage(Self_BombDamage);
	SetWeaponSpeed(Self_BombSpeed);

	ChangeState(Self_BombState::Max);
}

void Self_Bomb::LevelStart()
{

}

void Self_Bomb::Update(float _Delta)
{
	CameraFocus(_Delta);
	StateUpdate(_Delta);
}


void Self_Bomb::StateUpdate(float _Delta)
{
	switch (State)
	{
	case Self_BombState::Fly:
		return FlyUpdate(_Delta);
	case Self_BombState::Bomb:
		return BombUpdate(_Delta);
	case Self_BombState::Damage:
		return DamageUpdate(_Delta);
	case Self_BombState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void Self_Bomb::ChangeState(Self_BombState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case Self_BombState::Fly:
			FlyStart();
			break;
		case Self_BombState::Bomb:
			BombStart();
			break;
		case Self_BombState::Damage:
			DamageStart();
			break;
		case Self_BombState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

void Self_Bomb::CameraFocus(float _Delta)
{

}

void Self_Bomb::FlyStart()
{
	// 플레이어 기준 폭발 위치 조정
	AddPos(float4{0.0f, 10.0f});
}

void Self_Bomb::FlyUpdate(float _Delta)
{
	ChangeState(Self_BombState::Bomb);
	return;
}

void Self_Bomb::BombStart()
{
	Self_BombBomb = CreateBombEffect<Range25>();
}

void Self_Bomb::BombUpdate(float _Delta)
{
	if (true == Self_BombBomb->GetRenderer()->IsAnimationEnd())
	{
		ChangeState(Self_BombState::Damage);
		return;
	}
}

void Self_Bomb::DamageStart()
{

}

void Self_Bomb::DamageUpdate(float _Delta)
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

void Self_Bomb::MaxStart()
{

}

void Self_Bomb::MaxUpdate(float _Delta)
{
	ChangeState(Self_BombState::Fly);
	return;
}