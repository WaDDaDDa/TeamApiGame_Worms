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
		ChangeState(PlayerState::Jump);
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
		//ChangeState(PlayerState::Falling);
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

void Player::JumpStart()
{
	if (PlayerDir::Left == Dir)
	{
		SetGravityVector(float4::UP * PlayerJumpPower + float4::LEFT * 300.0f);
	}
	else if (PlayerDir::Right == Dir)
	{
		SetGravityVector(float4::UP * PlayerJumpPower + float4::RIGHT * 300.0f);
	}
	//ChangeAnimationState("Jump");
}
void Player::JumpUpdate(float _Delta)
{
	Gravity(_Delta);
	DirCheck();

	// �Ӹ��� üũ�� �Ͼ���� �ƴ϶�� Falling���� ������ȯ. = �ٸ������� �ִٸ� Falling
	// �Ӹ��� üũ�� ����̸� Falling,  �������̸� ���.  �̷������� �ϸ� ����ϴ� ������ ������������.
	float4 UpCheck = { 0 , -64 };

	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheck);

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
	//ChangeAnimationState("Falling");
}


void Player::FallingUpdate(float _Delta)
{
	DirCheck();
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