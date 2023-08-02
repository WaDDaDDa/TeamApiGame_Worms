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

	// 머리위 체크가 하얀색이 아니라면 Falling으로 상태전환. = 다른색상이 있다면 Falling
	// 머리위 체크가 녹색이면 Falling,  빨간색이면 통과.  이런식으로 하면 통과하는 발판이 가능해질듯함.
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

	// 천장에 머리 부딪힘 -> Falling으로 전환
	if (ColorCheck != RGB(255, 255, 255))
	{
		SetGravityVector(float4::ZERO);
		ChangeState(PlayerState::Falling);
		return;
	}

	// 점프 최고점 -> Falling 으로 전환
	if (GetGravityVector().iY() >= float4::ZERO.iY())
	{
		ChangeState(PlayerState::Falling);
		return;
	}
	// 점프중 이동
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

	// 땅에 닿으면 기본상태.
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
	//if (true == GameEngineInput::IsDown('1'))
	//{
	//	ChangeState(PlayerState::BazookaOff);
	//	return;
	//}

	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Bazooka);
		return;
	}
}

void Player::BazookaStart()
{
	ChangeAnimationState("Bazooka15");
}
void Player::BazookaUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::BazookaOff);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_UP))
	{
		CurAngle -= (5.625 * _Delta * 4);
		if (CurAngle <= -90.0f)
		{
			CurAngle = -90.0f;
		}
	}
	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		CurAngle += (5.625 * _Delta * 4);
		if (CurAngle >= +90.0f)
		{
			CurAngle = 90.0f;
		}
	}

	int iCurAngle = static_cast<int>(CurAngle);
	switch (iCurAngle)
	{
	case -90:
		ChangeAnimationState("Bazooka31");
		break;
	case -84:
		ChangeAnimationState("Bazooka30");
		break;
	case -78:
		ChangeAnimationState("Bazooka29");
		break;
	case -73:
		ChangeAnimationState("Bazooka28");
		break;
	case -67:
		ChangeAnimationState("Bazooka27");
		break;
	case -61:
		ChangeAnimationState("Bazooka26");
		break;
	case -56:
		ChangeAnimationState("Bazooka25");
		break;
	case -50:
		ChangeAnimationState("Bazooka24");
		break;
	case -45:
		ChangeAnimationState("Bazooka23");
		break;
	case -39:
		ChangeAnimationState("Bazooka22");
		break;
	case -33:
		ChangeAnimationState("Bazooka21");
		break;
	case -28:
		ChangeAnimationState("Bazooka20");
		break;
	case -22:
		ChangeAnimationState("Bazooka19");
		break;
	case -16:
		ChangeAnimationState("Bazooka18");
		break;
	case -11:
		ChangeAnimationState("Bazooka17");
		break;
	case -5:
		ChangeAnimationState("Bazooka16");
		break;
	case 0:
		ChangeAnimationState("Bazooka15");
		break;
	case 5:
		ChangeAnimationState("Bazooka14");
		break;
	case 11:
		ChangeAnimationState("Bazooka13");
		break;
	case 16:
		ChangeAnimationState("Bazooka12");
		break;
	case 22:
		ChangeAnimationState("Bazooka11");
		break;
	case 28:
		ChangeAnimationState("Bazooka10");
		break;
	case 33:
		ChangeAnimationState("Bazooka9");
		break;
	case 39:
		ChangeAnimationState("Bazooka8");
		break;
	case 45:
		ChangeAnimationState("Bazooka7");
		break;
	case 50:
		ChangeAnimationState("Bazooka6");
		break;
	case 56:
		ChangeAnimationState("Bazooka5");
		break;
	case 61:
		ChangeAnimationState("Bazooka4");
		break;
	case 67:
		ChangeAnimationState("Bazooka3");
		break;
	case 73:
		ChangeAnimationState("Bazooka2");
		break;
	case 78:
		ChangeAnimationState("Bazooka1");
		break;
	case 84:
		ChangeAnimationState("Bazooka0");
		break;
	}
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