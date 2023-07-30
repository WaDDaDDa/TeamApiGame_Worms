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

	if (true == GameEngineInput::IsPress(VK_LEFT)
		|| true == GameEngineInput::IsPress(VK_RIGHT))
	{
		if (true != IsTurnPlayer)
		{
			return;
		}

		DirCheck();
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::IsDown('A'))
	{
		if (true != IsTurnPlayer)
		{
			return;
		}

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
	DirCheck();

	GroundCheck(_Delta);

	Movement(_Delta);

	
	if (true == GameEngineInput::IsFree(VK_LEFT) && true == GameEngineInput::IsFree(VK_RIGHT))
	{
		ChangeState(PlayerState::Idle);
	}
	unsigned int Color = GetGroundColor(RGB(255, 255, 255), float4::DOWN);

	if ((RGB(255, 255, 255) == Color))
	{
		//ChangeState(KirbyState::Falling);
		return;
	}

}

void Player::FireStart()
{
	Weapon* NewWeapon = GetLevel()->CreateActor<Weapon>();
	NewWeapon->SetGroundTexture(GetGroundTexture());
	
	float4 Pos = GetPos();
	Pos.Y -= 15.0f;
	NewWeapon->SetPos(Pos);
}
void Player::FireUpdate(float _Delta)
{
	ChangeState(PlayerState::Idle);
}
