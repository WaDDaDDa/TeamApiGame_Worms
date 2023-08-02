#include "Player.h"
#include "Weapon.h"
#include "Bazooka.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>

void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}
void Player::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);

	if (true != IsTurnPlayer)
	{
		return;
	}

	if (true == GameEngineInput::IsPress(VK_LEFT)
		|| true == GameEngineInput::IsPress(VK_RIGHT))
	{
		DirCheck();
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::IsDown('A'))
	{
		ChangeState(PlayerState::Fire);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		//ChangeState(PlayerState::Jump);
		ChangeState(PlayerState::JumpReady);
		return;
	}

	if (true == GameEngineInput::IsDown('2'))
	{
		ChangeState(PlayerState::BazookaOn);
		return;
	}

}

void Player::MoveStart()
{
	ChangeAnimationState("Move");
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

	unsigned int Color = GetGroundColor(RGB(255, 255, 255), float4::DOWN * 20.0f);

	if ((RGB(255, 255, 255) == Color))
	{
		ChangeState(PlayerState::Falling);
		return;
	}

}

void Player::FireStart()
{
	Weapon* NewWeapon = GetLevel()->CreateActor<Bazooka>();
	NewWeapon->SetGroundTexture(GetGroundTexture());
	NewWeapon->SetMaster(this);

	float4 Pos = GetPos();
	Pos.Y -= 15.0f;
	NewWeapon->SetPos(Pos);
}
void Player::FireUpdate(float _Delta)
{
	ChangeState(PlayerState::Idle);
}

void Player::JumpReadyStart()
{
	ChangeAnimationState("JumpReady");
}
void Player::JumpReadyUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Jump);
	}
	
}

void Player::JumpStart()
{
	ChangeAnimationState("Jump");
	if (PlayerDir::Left == Dir)
	{
		SetGravityVector(float4::UP * PlayerJumpPower + float4::LEFT * 300.0f);
	}
	else if (PlayerDir::Right == Dir)
	{
		SetGravityVector(float4::UP * PlayerJumpPower + float4::RIGHT * 300.0f);
	}
	
}
void Player::JumpUpdate(float _Delta)
{
	Gravity(_Delta);
	//DirCheck();

	// �Ӹ��� üũ�� �Ͼ���� �ƴ϶�� Falling���� ������ȯ. = �ٸ������� �ִٸ� Falling
	// �Ӹ��� üũ�� ����̸� Falling,  �������̸� ���.  �̷������� �ϸ� ����ϴ� ������ ������������.
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheckPos);
	unsigned int LeftColorCheck = GetGroundColor(RGB(255, 255, 255), LeftCheckPos);
	unsigned int RightColorCheck = GetGroundColor(RGB(255, 255, 255), RightCheckPos);

	if (PlayerDir::Left == Dir && LeftColorCheck != RGB(255, 255, 255))
	{
		SetGravityVector(float4::ZERO);
		ChangeState(PlayerState::Falling);
		return;
	}
	else if (PlayerDir::Right == Dir && RightColorCheck != RGB(255, 255, 255))
	{
		SetGravityVector(float4::ZERO);
		ChangeState(PlayerState::Falling);
		return;
	}

	// õ�忡 �Ӹ� �ε��� -> Falling���� ��ȯ
	if (ColorCheck != RGB(255, 255, 255))
	{
		SetGravityVector(float4::ZERO);
		ChangeState(PlayerState::Falling);
		return;
	}

	// ���� �ְ��� -> Falling ���� ��ȯ
	if (GetGravityVector().iY() >= float4::ZERO.iY())
	{
		ChangeState(PlayerState::Falling);
		return;
	}
	// ������ �̵�
	//Movement(_Delta);
}

void Player::FallingStart()
{
	ChangeAnimationState("Falling");
}


void Player::FallingUpdate(float _Delta)
{
	//DirCheck();
	Gravity(_Delta);

	// ���� ������ �⺻����.
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));

	if (RGB(255, 255, 255) != Color)
	{
		GravityReset();
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::BazookaOnStart()
{
	ChangeAnimationState("BazookaOn");
}
void Player::BazookaOnUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::BazookaOff);
		return;
	}
}

void Player::BazookaStart()
{

}
void Player::BazookaUpdate(float _Delta)
{

}

void Player::BazookaOffStart()
{
	ChangeAnimationState("BazookaOff");
}
void Player::BazookaOffUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}