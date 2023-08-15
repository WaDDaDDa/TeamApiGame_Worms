#include "Sheep.h"
#include "Ground.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "PlayLevel.h"
#include "GameTurn.h"
#include "Range25.h"
#include "Range50.h"
#include "Range75.h"
#include "Range100.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEnginecollision.h>

Sheep::Sheep()
{

}

Sheep::~Sheep()
{

}

void Sheep::Start()
{
	Renderer = CreateRenderer(RenderOrder::Weapon);

	if (false == ResourcesManager::GetInst().IsLoadTexture("sheepwlk.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("sheepwlk.bmp"), 1, 8);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("sheepwlk2.bmp"), 1, 8);
	}

	
	Renderer->SetTexture("Blank.bmp");
	Renderer->SetScaleRatio(1.2f);

	Renderer->CreateAnimation("Right_Sheep_Fly", "sheepwlk.bmp", 0, 7, 0.1f, true);
	Renderer->CreateAnimation("Left_Sheep_Fly", "sheepwlk2.bmp", 0, 7, 0.1f, true);

	SetWeaponDamage(SheepDamage);
	SetWeaponSpeed(SheepSpeed);

	ChangeState(SheepState::Max);
}

void Sheep::LevelStart()
{

}

void Sheep::Update(float _Delta)
{
	CameraFocus(_Delta);
	StateUpdate(_Delta);
}


void Sheep::StateUpdate(float _Delta)
{
	switch (State)
	{
	case SheepState::Idle:
		return IdleUpdate(_Delta);
	case SheepState::Fly:
		return FlyUpdate(_Delta);
	case SheepState::Jump:
		return JumpUpdate(_Delta);
	case SheepState::Bomb:
		return BombUpdate(_Delta);
	case SheepState::Damage:
		return DamageUpdate(_Delta);
	case SheepState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void Sheep::ChangeState(SheepState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case SheepState::Idle:
			IdleStart();
			break;
		case SheepState::Fly:
			FlyStart();
			break;
		case SheepState::Jump:
			JumpStart();
			break;
		case SheepState::Bomb:
			BombStart();
			break;
		case SheepState::Damage:
			DamageStart();
			break;
		case SheepState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	//ResetLiveTime();

	State = _State;
}


void Sheep::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName;

	switch (DirState)
	{
	case SheepDir::Right:
		AnimationName = "Right_";
		break;
	case SheepDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _State;

	CurState = _State;

	Renderer->ChangeAnimation(AnimationName);
}


void Sheep::Movement(float _Delta)
{
	float4 MovePos1 = float4::ZERO;
	unsigned int Color = 0;

	if (DirState == SheepDir::Left)
	{
		CheckPos = LeftCheckPos;
		MovePos1 = { -SheepSpeed * _Delta, 0.0f };

		Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		if (Color != RGB(255, 255, 255))
		{
			DirState = SheepDir::Right;
			ChangeAnimationState(CurState);
			return;
		}

	}
	else if (DirState == SheepDir::Right)
	{
		CheckPos = RightCheckPos;
		MovePos1 = { SheepSpeed * _Delta, 0.0f };
		// 움직일 곳의 Pos를 MovePos에 담았다.

		Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		if (Color != RGB(255, 255, 255))
		{
			DirState = SheepDir::Left;
			ChangeAnimationState(CurState);
			return;
		}
	}

	// 플레이어가 공중이면
	if (Color == RGB(255, 255, 255))
	{
		// 움직일 예정의 곳도 공중인지 체크한다.
		//if (RGB(255, 255, 255) == GetGroundColor(RGB(255, 255, 255), MovePos1))
		//{
		//	// 움직일 곳 또한 공중이라면
		//	float4 XPos = float4::ZERO;
		//	float4 Dir = MovePos1.X >= 0.0f ? float4::RIGHT : float4::LEFT;
		//	while (RGB(0, 0, 255) != GetGroundColor(RGB(255, 255, 255), MovePos1 + XPos))
		//	{
		//		XPos += Dir;

		//		if (abs(XPos.X) > 20.0f)
		//		{
		//			break;
		//		}
		//	}

		//	float4 YPos = float4::ZERO;
		//	while (RGB(0, 0, 255) != GetGroundColor(RGB(255, 255, 255), MovePos1 + YPos))
		//	{
		//		YPos.Y += 1;

		//		if (YPos.Y > 30.0f)
		//		{
		//			break;
		//		}
		//	}

		//	if (abs(XPos.X) >= YPos.Y)
		//	{
		//		while (RGB(0, 0, 255) != GetGroundColor(RGB(255, 255, 255), MovePos1))
		//		{
		//			MovePos1.Y += 1;
		//		}
		//	}

		//}
		AddPos(MovePos1);
	}
}

void Sheep::IdleStart()
{
	if (Master->GetPlayerDir() == PlayerDir::Right)
	{
		DirState = SheepDir::Right;
	}
	else if (Master->GetPlayerDir() == PlayerDir::Left)
	{
		DirState = SheepDir::Left;
	}
}

void Sheep::IdleUpdate(float _Delta)
{
	ChangeState(SheepState::Fly);
	return;
}

void Sheep::FlyStart()
{
	ChangeAnimationState("Sheep_Fly");
}

void Sheep::FlyUpdate(float _Delta)
{
	GroundCheck(_Delta);

	Movement(_Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (RGB(255, 255, 255) != Color)
	{
		ChangeState(SheepState::Jump);
		return;
	}

	float Test = GetLiveTime();
	bool Test1 = GameEngineInput::IsDown('A');

	if (Test >= 15.0f || true == Test1)
	{
		ChangeState(SheepState::Bomb);
		return;
	}

}

void Sheep::JumpStart()
{
	if (DirState == SheepDir::Right)
	{
		SetGravityVector(float4::UP * SheepJumpPower + float4::RIGHT * SheepSpeed);
	}
	else if (DirState == SheepDir::Left)
	{
		SetGravityVector(float4::UP * SheepJumpPower + float4::LEFT * SheepSpeed);
	}
}

void Sheep::JumpUpdate(float _Delta)
{
	Gravity(_Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheckPos);

	if (RGB(255, 255, 255) != Color)
	{
		GravityReset();
		ChangeState(SheepState::Fly);
		return;
	}

	//천장에 머리 부딪힘 -> Falling으로 전환
	if (ColorCheck != RGB(255, 255, 255))
	{
		GravityReset();
		ChangeState(SheepState::Fly);
		return;
	}

	float Test = GetLiveTime();
	bool Test1 = GameEngineInput::IsDown('A');

	if (Test >= 15.0f || true == Test1)
	{
		ChangeState(SheepState::Bomb);
		return;
	}


}

void Sheep::BombStart()
{
	SheepBomb = CreateBombEffect<Range75>();
	Renderer->Off();
}

void Sheep::BombUpdate(float _Delta)
{
	if (true == SheepBomb->GetRenderer()->IsAnimationEnd())
	{
		ChangeState(SheepState::Damage);
		return;
	}
}

void Sheep::DamageStart()
{

}

void Sheep::DamageUpdate(float _Delta)
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

void Sheep::MaxStart()
{

}

void Sheep::MaxUpdate(float _Delta)
{
	ChangeState(SheepState::Idle);
	return;
}