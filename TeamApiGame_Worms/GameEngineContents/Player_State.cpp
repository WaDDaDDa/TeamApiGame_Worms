#include "Player.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineBase/GameEngineRandom.h>

void Player::IdleStart()
{
	ChangeAnimationState("Idle");

	// MainRenderer->ChangeAnimation("Right_Idle");
}

void AttStart()
{
	//int Value = GameEngineRandom::MainRandom.RandomInt(0, 3);

	//switch (Value)
	//{
	//case 0:
	//	ChangeAnimationState("Att0");
	//	break;
	//case 1:
	//	ChangeAnimationState("Att1");
	//	break;
	//case 2:
	//	ChangeAnimationState("Att2");
	//	break;
	//default:
	//	break;
	//}
}


void Player::RunStart()
{
	ChangeAnimationState("Run");
	// MainRenderer->ChangeAnimation("Right_Run");
}

void Player::IdleUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		++TestValue;
	}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}


			GravityReset();
		}
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		// 공격
	}

	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChanageState(PlayerState::Run);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_SPACE))
	{
		ChanageState(PlayerState::Jump);
		return;
	}


	// 줄줄이 사탕으로 
	//if (true)
	//{
	//	ChanageState(PlayerState::Idle);
	//}

}


void Player::RunUpdate(float _Delta)
{
	// 중력 적용 
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}

			if (true == GameEngineInput::IsPress(VK_SPACE))
			{
				ChanageState(PlayerState::Jump);
				return;
			}

			GravityReset();
		}

	}


	DirCheck();

	float Speed = 400.0f;

	float4 CheckPos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && Dir == PlayerDir::Left)
	{
		// 귀찮음
		// => 프로그래머의 최악의 
		CheckPos = LeftCheck;
		MovePos += { -Speed * _Delta, 0.0f };
	} 
	else if (true == GameEngineInput::IsPress('D') && Dir == PlayerDir::Right)
	{
		CheckPos = RightCheck;
		MovePos += { Speed * _Delta, 0.0f };
	}

	//if (true == GameEngineInput::IsPress('W'))
	//{
	//	MovePos = { 0.0f, -Speed * _Delta };
	//}
	//if (true == GameEngineInput::IsPress('S'))
	//{
	//	MovePos = { 0.0f, Speed * _Delta };
	//}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChanageState(PlayerState::Idle);
		return;
	}

	{
		//unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		//if (Color == RGB(255, 255, 255))
		//{
		//	// MovePos를 바꿔버리는 방법이 있을것이고.

		//	if (RGB(255, 255, 255) == GetGroundColor(RGB(255, 255, 255), MovePos))
		//	{
		//		float4 XPos = float4::ZERO;
		//		float4 Dir = MovePos.X <= 0.0f ? float4::RIGHT : float4::LEFT;

		//		while (RGB(255, 0, 0) != GetGroundColor(RGB(255, 255, 255), MovePos + XPos))
		//		{
		//			XPos += Dir;

		//			if (abs(XPos.X) > 50.0f)
		//			{
		//				break;
		//			}
		//		}

		//		float4 YPos = float4::ZERO;
		//		while (RGB(255, 0, 0) != GetGroundColor(RGB(255, 255, 255), MovePos + YPos))
		//		{
		//			YPos.Y += 1;

		//			if (YPos.Y > 60.0f)
		//			{
		//				break;
		//			}
		//		}

		//		if (abs(XPos.X) >= YPos.Y)
		//		{
		//			while (RGB(255, 0, 0) != GetGroundColor(RGB(255, 255, 255), MovePos))
		//			{
		//				MovePos.Y += 1;
		//			}
		//		}
		//		
		//	}

		//	// 내가 움직이려는 
		//	// GetGroundColor(RGB(255, 255, 255), MovePos);

		//}

		// 내가 키를 누르지 않고 있을때만 해야한다.
		if (true == GameEngineInput::IsFree('A')
			&& true == GameEngineInput::IsFree('D'))
		{
			MovePos -= MovePos * 0.01f;
		}

		if (MovePos.Size() >= 500.0f)
		{
			MovePos.Normalize();
			MovePos *= 500.0f;
		}

		AddPos(MovePos * _Delta);
	}


}

void Player::JumpStart()
{
	// 애니메이션 해야하는데 귀찮음

	SetGravityVector(float4::UP * 1000.0f);
}

int A = 0;

void Player::JumpUpdate(float _Delta)
{
	Gravity(_Delta);

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		if (Dir	== PlayerDir::Left)
		{
			SetGravityVector((float4::UP + float4::LEFT) * 1000.0f);
		}
		else if (Dir == PlayerDir::Right)
		{
			SetGravityVector((float4::UP + float4::RIGHT) * 1000.0f);
		}
	}


	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) != Color)
		{
			ChanageState(PlayerState::Idle);
			return;
		}
	}

}