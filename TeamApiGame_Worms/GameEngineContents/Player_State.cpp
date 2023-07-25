#include "Player.h"
#include "Weapon.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}
void Player::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);

	if (true == GameEngineInput::IsPress(VK_LEFT) && true == IsTurnPlayer
		|| true == GameEngineInput::IsPress(VK_RIGHT) && true == IsTurnPlayer)
	{
		DirCheck();
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::IsDown('A') && true == IsTurnPlayer)
	{
		ChangeState(PlayerState::Fire);
		return;
	}


}

void Player::MoveStart()
{
	ChangeAnimationState("Idle");
}
void Player::MoveUpdate(float _Delta)
{
	//DirCheck();

	float Speed = 100.0f;

	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress(VK_LEFT) && Dir == PlayerDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
	}
	
	if (MovePos == float4::ZERO)
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	AddPos(MovePos);
}

void Player::FireStart()
{
	Weapon* NewWeapon = GetLevel()->CreateActor<Weapon>();
	NewWeapon->SetGroundTexture("TestGroundPixel.bmp");
	
	float4 Pos = GetPos();
	NewWeapon->SetPos(Pos);
}
void Player::FireUpdate(float _Delta)
{
	ChangeState(PlayerState::Idle);
}
