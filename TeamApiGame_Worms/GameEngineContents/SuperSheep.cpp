#include "SuperSheep.h"
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
#include <GameEnginePlatform/GameEngineWindowTexture.h>

SuperSheep::SuperSheep()
{

}

SuperSheep::~SuperSheep()
{

}

void SuperSheep::Start()
{
	Renderer = CreateRenderer(RenderOrder::Weapon);

	if (false == ResourcesManager::GetInst().IsLoadTexture("Sheepwlk.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Sheepwlk.bmp"), 1, 8);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Sheepwlk2.bmp"), 1, 8);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("aquashp1.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("aquashp1.bmp"), 1, 32);
	}

	
	Renderer->SetTexture("Blank.bmp");
	Renderer->SetScaleRatio(1.2f);

	Renderer->CreateAnimation("Right_SuperSheep_Fly", "Sheepwlk.bmp", 0, 7, 0.1f, true);
	Renderer->CreateAnimation("Left_SuperSheep_Fly", "Sheepwlk2.bmp", 0, 7, 0.1f, true);

	{
		Renderer->CreateAnimation("8_SuperSheep_Fly", "aquashp1.bmp", 0, 0, 0.05f, false);
		// 78.75도
		Renderer->CreateAnimation("7_SuperSheep_Fly", "aquashp1.bmp", 1, 1, 0.05f, false);
		// 67.5도
		Renderer->CreateAnimation("6_SuperSheep_Fly", "aquashp1.bmp", 2, 2, 0.05f, false);
		// 56.25도
		Renderer->CreateAnimation("5_SuperSheep_Fly", "aquashp1.bmp", 3, 3, 0.05f, false);
		// 45 도
		Renderer->CreateAnimation("4_SuperSheep_Fly", "aquashp1.bmp", 4, 4, 0.05f, false);
		// 33.75도
		Renderer->CreateAnimation("3_SuperSheep_Fly", "aquashp1.bmp", 5, 5, 0.05f, false);
		// 22,5도
		Renderer->CreateAnimation("2_SuperSheep_Fly", "aquashp1.bmp", 6, 6, 0.05f, false);
		// 11.25도
		Renderer->CreateAnimation("1_SuperSheep_Fly", "aquashp1.bmp", 7, 7, 0.05f, false);
		// 0도
		Renderer->CreateAnimation("0_SuperSheep_Fly", "aquashp1.bmp", 8, 8, 0.05f, false);
		// -11.25도
		Renderer->CreateAnimation("31_SuperSheep_Fly", "aquashp1.bmp", 9, 9, 0.05f, false);
		// -22.5도
		Renderer->CreateAnimation("30_SuperSheep_Fly", "aquashp1.bmp", 10, 10, 0.05f, false);
		// -33.75도
		Renderer->CreateAnimation("29_SuperSheep_Fly", "aquashp1.bmp", 11, 11, 0.05f, false);
		// -45도
		Renderer->CreateAnimation("28_SuperSheep_Fly", "aquashp1.bmp", 12, 12, 0.05f, false);
		// -56.25도
		Renderer->CreateAnimation("27_SuperSheep_Fly", "aquashp1.bmp", 13, 13, 0.05f, false);
		// -67.5도
		Renderer->CreateAnimation("26_SuperSheep_Fly", "aquashp1.bmp", 14, 14, 0.05f, false);
		// -78.75도
		Renderer->CreateAnimation("25_SuperSheep_Fly", "aquashp1.bmp", 15, 15, 0.05f, false);
		// -90 도
		Renderer->CreateAnimation("24_SuperSheep_Fly", "aquashp1.bmp", 16, 16, 0.05f, false);
		// -101.25 도
		Renderer->CreateAnimation("23_SuperSheep_Fly", "aquashp1.bmp", 17, 17, 0.05f, false);
		// -112.5도
		Renderer->CreateAnimation("22_SuperSheep_Fly", "aquashp1.bmp", 18, 18, 0.05f, false);
		// -123.75도
		Renderer->CreateAnimation("21_SuperSheep_Fly", "aquashp1.bmp", 19, 19, 0.05f, false);
		// -135도
		Renderer->CreateAnimation("20_SuperSheep_Fly", "aquashp1.bmp", 20, 20, 0.05f, false);
		// -146.25도
		Renderer->CreateAnimation("19_SuperSheep_Fly", "aquashp1.bmp", 21, 21, 0.05f, false);
		//-157.5
		Renderer->CreateAnimation("18_SuperSheep_Fly", "aquashp1.bmp", 22, 22, 0.05f, false);
		//-168.75
		Renderer->CreateAnimation("17_SuperSheep_Fly", "aquashp1.bmp", 23, 23, 0.05f, false);
		//-180
		Renderer->CreateAnimation("16_SuperSheep_Fly", "aquashp1.bmp", 24, 24, 0.05f, false);
		//-191.25
		Renderer->CreateAnimation("15_SuperSheep_Fly", "aquashp1.bmp", 25, 25, 0.05f, false);
		//-202.5
		Renderer->CreateAnimation("14_SuperSheep_Fly", "aquashp1.bmp", 26, 26, 0.05f, false);
		//-213.75
		Renderer->CreateAnimation("13_SuperSheep_Fly", "aquashp1.bmp", 27, 27, 0.05f, false);
		//-225
		Renderer->CreateAnimation("12_SuperSheep_Fly", "aquashp1.bmp", 28, 28, 0.05f, false);
		//-236.25
		Renderer->CreateAnimation("11_SuperSheep_Fly", "aquashp1.bmp", 29, 29, 0.05f, false);
		//-247.5
		Renderer->CreateAnimation("10_SuperSheep_Fly", "aquashp1.bmp", 30, 30, 0.05f, false);
		//-258.75
		Renderer->CreateAnimation("9_SuperSheep_Fly", "aquashp1.bmp", 31, 31, 0.05f, false);
	}

	SetWeaponDamage(SuperSheepDamage);
	SetWeaponSpeed(SuperSheepSpeed);

	ChangeState(SuperSheepState::Max);
}

void SuperSheep::LevelStart()
{

}

void SuperSheep::Update(float _Delta)
{
	CameraFocus(_Delta);
	StateUpdate(_Delta);
}


void SuperSheep::DirCheck()
{
	//Dir = float4::UP;
	float CurDir = Dir.AngleDeg();

	float CheckDir = CurDir / 11.25f;

	std::string Text = "";

	switch (static_cast<int>(CheckDir))
	{
	case 0:
		Renderer->ChangeAnimation("0_SuperSheep_Fly");
		break;
	case 1:
		Renderer->ChangeAnimation("1_SuperSheep_Fly");
		break;
	case 2:
		Renderer->ChangeAnimation("2_SuperSheep_Fly");
		break;
	case 3:
		Renderer->ChangeAnimation("3_SuperSheep_Fly");
		break;
	case 4:
		Renderer->ChangeAnimation("4_SuperSheep_Fly");
		break;
	case 5:
		Renderer->ChangeAnimation("5_SuperSheep_Fly");
		break;
	case 6:
		Renderer->ChangeAnimation("6_SuperSheep_Fly");
		break;
	case 7:
		Renderer->ChangeAnimation("7_SuperSheep_Fly");
		break;
	case 8:
		Renderer->ChangeAnimation("8_SuperSheep_Fly");
		break;
	case 9:
		Renderer->ChangeAnimation("9_SuperSheep_Fly");
		break;
	case 10:
		Renderer->ChangeAnimation("10_SuperSheep_Fly");
		break;
	case 11:
		Renderer->ChangeAnimation("11_SuperSheep_Fly");
		break;
	case 12:
		Renderer->ChangeAnimation("12_SuperSheep_Fly");
		break;
	case 13:
		Renderer->ChangeAnimation("13_SuperSheep_Fly");
		break;
	case 14:
		Renderer->ChangeAnimation("14_SuperSheep_Fly");
		break;
	case 15:
		Renderer->ChangeAnimation("15_SuperSheep_Fly");
		break;
	case 16:
		Renderer->ChangeAnimation("16_SuperSheep_Fly");
		break;
	case 17:
		Renderer->ChangeAnimation("17_SuperSheep_Fly");
		break;
	case 18:
		Renderer->ChangeAnimation("18_SuperSheep_Fly");
		break;
	case 19:
		Renderer->ChangeAnimation("19_SuperSheep_Fly");
		break;
	case 20:
		Renderer->ChangeAnimation("20_SuperSheep_Fly");
		break;
	case 21:
		Renderer->ChangeAnimation("21_SuperSheep_Fly");
		break;
	case 22:
		Renderer->ChangeAnimation("22_SuperSheep_Fly");
		break;
	case 23:
		Renderer->ChangeAnimation("23_SuperSheep_Fly");
		break;
	case 24:
		Renderer->ChangeAnimation("24_SuperSheep_Fly");
		break;
	case 25:
		Renderer->ChangeAnimation("25_SuperSheep_Fly");
		break;
	case 26:
		Renderer->ChangeAnimation("26_SuperSheep_Fly");
		break;
	case 27:
		Renderer->ChangeAnimation("27_SuperSheep_Fly");
		break;
	case 28:
		Renderer->ChangeAnimation("28_SuperSheep_Fly");
		break;
	case 29:
		Renderer->ChangeAnimation("29_SuperSheep_Fly");
		break;
	case 30:
		Renderer->ChangeAnimation("30_SuperSheep_Fly");
		break;
	case 31:
		Renderer->ChangeAnimation("31_SuperSheep_Fly");
		break;
	default:
		break;
	}
}


void SuperSheep::StateUpdate(float _Delta)
{
	switch (State)
	{
	case SuperSheepState::Idle:
		return IdleUpdate(_Delta);
	case SuperSheepState::Fly:
		return FlyUpdate(_Delta);
	case SuperSheepState::SuperFly:
		return SuperFlyUpdate(_Delta);
	case SuperSheepState::Jump:
		return JumpUpdate(_Delta);
	case SuperSheepState::Bomb:
		return BombUpdate(_Delta);
	case SuperSheepState::Damage:
		return DamageUpdate(_Delta);
	case SuperSheepState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void SuperSheep::ChangeState(SuperSheepState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case SuperSheepState::Idle:
			IdleStart();
			break;
		case SuperSheepState::Fly:
			FlyStart();
			break;
		case SuperSheepState::SuperFly:
			SuperFlyStart();
			break;
		case SuperSheepState::Jump:
			JumpStart();
			break;
		case SuperSheepState::Bomb:
			BombStart();
			break;
		case SuperSheepState::Damage:
			DamageStart();
			break;
		case SuperSheepState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	//ResetLiveTime();

	State = _State;
}


void SuperSheep::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName;

	switch (DirState)
	{
	case SuperSheepDir::Right:
		AnimationName = "Right_";
		break;
	case SuperSheepDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _State;

	CurState = _State;

	Renderer->ChangeAnimation(AnimationName);
}


void SuperSheep::Movement(float _Delta)
{
	float4 MovePos1 = float4::ZERO;
	unsigned int Color = 0;

	if (DirState == SuperSheepDir::Left)
	{
		CheckPos = LeftCheckPos;
		MovePos1 = { -SuperSheepSpeed * _Delta, 0.0f };

		Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		if (Color != RGB(255, 255, 255))
		{
			DirState = SuperSheepDir::Right;
			ChangeAnimationState(CurState);
			return;
		}

	}
	else if (DirState == SuperSheepDir::Right)
	{
		CheckPos = RightCheckPos;
		MovePos1 = { SuperSheepSpeed * _Delta, 0.0f };
		// 움직일 곳의 Pos를 MovePos에 담았다.

		Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		if (Color != RGB(255, 255, 255))
		{
			DirState = SuperSheepDir::Left;
			ChangeAnimationState(CurState);
			return;
		}
	}

	if (Color == RGB(255, 255, 255))
	{
		AddPos(MovePos1);
	}
}

void SuperSheep::IdleStart()
{
	if (Master->GetPlayerDir() == PlayerDir::Right)
	{
		DirState = SuperSheepDir::Right;
	}
	else if (Master->GetPlayerDir() == PlayerDir::Left)
	{
		DirState = SuperSheepDir::Left;
	}
}

void SuperSheep::IdleUpdate(float _Delta)
{
	ChangeState(SuperSheepState::Fly);
	return;
}

void SuperSheep::FlyStart()
{
	ChangeAnimationState("SuperSheep_Fly");
}

void SuperSheep::FlyUpdate(float _Delta)
{
	GroundCheck(_Delta);

	Movement(_Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (RGB(255, 255, 255) != Color)
	{
		ChangeState(SuperSheepState::Jump);
		return;
	}

	float Test = GetLiveTime();
	bool Test1 = GameEngineInput::IsDown('A');

	if (Test >= 15.0f || true == Test1)
	{
		ChangeState(SuperSheepState::Bomb);
		return;
	}

}

void SuperSheep::RotateDir(float _Delta)
{
	if (true == GameEngineInput::IsFree(VK_LEFT) && true == GameEngineInput::IsFree(VK_RIGHT))
	{
		return;
	}

	if (true == GameEngineInput::IsDown(VK_LEFT) || true == GameEngineInput::IsFree(VK_RIGHT))
	{
		Dir = Dir.GetRotationToDegZ(-360 * _Delta);
		return;
	}

	if (true == GameEngineInput::IsFree(VK_LEFT) || true == GameEngineInput::IsDown(VK_RIGHT))
	{
		Dir = Dir.GetRotationToDegZ(360 * _Delta);
		return;
	}
}

void SuperSheep::SuperFlyStart()
{
	Dir = float4::UP;
}

void SuperSheep::SuperFlyUpdate(float _Delta)
{
	DirCheck();

	RotateDir(_Delta);

	if (true == GameEngineInput::IsDown(VK_LEFT))
	{
		Dir = Dir.GetRotationToDegZ(-270 * _Delta);
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT))
	{
		Dir = Dir.GetRotationToDegZ(270 * _Delta);
	}

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheckPos);

	if (RGB(255, 255, 255) != Color)
	{
		ChangeState(SuperSheepState::Bomb);
		return;
	}

	float ImageX = GetGroundTexture()->GetScale().X;
	float ImageY = GetGroundTexture()->GetScale().Y;

	// 양 맵의 왼쪽으로 못나가게.
	if (0.0f >= GetPos().X)
	{
		ChangeState(SuperSheepState::Bomb);
		return;
	}
	// 양 맵의 오른쪽 최대치를 못나가게.
	if (ImageX <= GetPos().X)
	{
		ChangeState(SuperSheepState::Bomb);
		return;
	}
	// 양 맵의 아래 최대치를 못나가게.
	if (ImageY <= GetPos().Y)
	{
		ChangeState(SuperSheepState::Bomb);
		return;
	}
	// 양 맵의 위 최대치를 못나가게.
	if (0.0f >= GetPos().Y)
	{
		ChangeState(SuperSheepState::Bomb);
		return;
	}

	AddPos(Dir * SuperSheepFlySpeed * _Delta);
}


void SuperSheep::JumpStart()
{
	if (DirState == SuperSheepDir::Right)
	{
		SetGravityVector(float4::UP * SuperSheepJumpPower + float4::RIGHT * SuperSheepSpeed);
	}
	else if (DirState == SuperSheepDir::Left)
	{
		SetGravityVector(float4::UP * SuperSheepJumpPower + float4::LEFT * SuperSheepSpeed);
	}
}

void SuperSheep::JumpUpdate(float _Delta)
{
	Gravity(_Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheckPos);

	if (RGB(255, 255, 255) != Color)
	{
		GravityReset();
		ChangeState(SuperSheepState::Fly);
		return;
	}

	//천장에 머리 부딪힘 -> Falling으로 전환
	if (ColorCheck != RGB(255, 255, 255))
	{
		GravityReset();
		ChangeState(SuperSheepState::Fly);
		return;
	}

	float Test = GetLiveTime();
	bool Test1 = GameEngineInput::IsDown('A');

	if (Test >= 15.0f || true == Test1)
	{
		ChangeState(SuperSheepState::SuperFly);
		return;
	}


}

void SuperSheep::BombStart()
{
	SuperSheepBomb = CreateBombEffect<Range75>();
	Renderer->Off();
}

void SuperSheep::BombUpdate(float _Delta)
{
	if (true == SuperSheepBomb->GetRenderer()->IsAnimationEnd())
	{
		ChangeState(SuperSheepState::Damage);
		return;
	}
}

void SuperSheep::DamageStart()
{

}

void SuperSheep::DamageUpdate(float _Delta)
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

void SuperSheep::MaxStart()
{

}

void SuperSheep::MaxUpdate(float _Delta)
{
	ChangeState(SuperSheepState::Idle);
	return;
}