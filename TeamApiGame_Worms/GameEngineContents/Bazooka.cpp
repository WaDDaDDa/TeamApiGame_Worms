#include "Bazooka.h"
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

Bazooka::Bazooka()
{

}

Bazooka::~Bazooka()
{

}

void Bazooka::Start()
{
	Renderer = CreateRenderer(RenderOrder::Weapon);

	if (false == ResourcesManager::GetInst().IsLoadTexture("bazooka.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("bazooka.bmp"), 1, 32);
	}

	
	Renderer->SetTexture("Blank.bmp");

	// 90도
	Renderer->CreateAnimation("8_Bazooka_Fly", "bazooka.bmp", 0, 0, 0.05f, false);
	// 78.75도
	Renderer->CreateAnimation("7_Bazooka_Fly", "bazooka.bmp", 1, 1, 0.05f, false);
	// 67.5도
	Renderer->CreateAnimation("6_Bazooka_Fly", "bazooka.bmp", 2, 2, 0.05f, false);
	// 56.25도
	Renderer->CreateAnimation("5_Bazooka_Fly", "bazooka.bmp", 3, 3, 0.05f, false);
	// 45 도
	Renderer->CreateAnimation("4_Bazooka_Fly", "bazooka.bmp", 4, 4, 0.05f, false);
	// 33.75도
	Renderer->CreateAnimation("3_Bazooka_Fly", "bazooka.bmp", 5, 5, 0.05f, false);
	// 22,5도
	Renderer->CreateAnimation("2_Bazooka_Fly", "bazooka.bmp", 6, 6, 0.05f, false);
	// 11.25도
	Renderer->CreateAnimation("1_Bazooka_Fly", "bazooka.bmp", 7, 7, 0.05f, false);
	// 0도
	Renderer->CreateAnimation("0_Bazooka_Fly", "bazooka.bmp", 8, 8, 0.05f, false);
	// -11.25도
	Renderer->CreateAnimation("31_Bazooka_Fly", "bazooka.bmp", 9, 9, 0.05f, false);
	// -22.5도
	Renderer->CreateAnimation("30_Bazooka_Fly", "bazooka.bmp", 10, 10, 0.05f, false);
	// -33.75도
	Renderer->CreateAnimation("29_Bazooka_Fly", "bazooka.bmp", 11, 11, 0.05f, false);
	// -45도
	Renderer->CreateAnimation("28_Bazooka_Fly", "bazooka.bmp", 12, 12, 0.05f, false);
	// -56.25도
	Renderer->CreateAnimation("27_Bazooka_Fly", "bazooka.bmp", 13, 13, 0.05f, false);
	// -67.5도
	Renderer->CreateAnimation("26_Bazooka_Fly", "bazooka.bmp", 14, 14, 0.05f, false);
	// -78.75도
	Renderer->CreateAnimation("25_Bazooka_Fly", "bazooka.bmp", 15, 15, 0.05f, false);
	// -90 도
	Renderer->CreateAnimation("24_Bazooka_Fly", "bazooka.bmp", 16, 16, 0.05f, false);
	// -101.25 도
	Renderer->CreateAnimation("23_Bazooka_Fly", "bazooka.bmp", 17, 17, 0.05f, false);
	// -112.5도
	Renderer->CreateAnimation("22_Bazooka_Fly", "bazooka.bmp", 18, 18, 0.05f, false);
	// -123.75도
	Renderer->CreateAnimation("21_Bazooka_Fly", "bazooka.bmp", 19, 19, 0.05f, false);
	// -135도
	Renderer->CreateAnimation("20_Bazooka_Fly", "bazooka.bmp", 20, 20, 0.05f, false);
	// -146.25도
	Renderer->CreateAnimation("19_Bazooka_Fly", "bazooka.bmp", 21, 21, 0.05f, false);
	//-157.5
	Renderer->CreateAnimation("18_Bazooka_Fly", "bazooka.bmp", 22, 22, 0.05f, false);
	//-168.75
	Renderer->CreateAnimation("17_Bazooka_Fly", "bazooka.bmp", 23, 23, 0.05f, false);
	//-180
	Renderer->CreateAnimation("16_Bazooka_Fly", "bazooka.bmp", 24, 24, 0.05f, false);
	//-191.25
	Renderer->CreateAnimation("15_Bazooka_Fly", "bazooka.bmp", 25, 25, 0.05f, false);
	//-202.5
	Renderer->CreateAnimation("14_Bazooka_Fly", "bazooka.bmp", 26, 26, 0.05f, false);
	//-213.75
	Renderer->CreateAnimation("13_Bazooka_Fly", "bazooka.bmp", 27, 27, 0.05f, false);
	//-225
	Renderer->CreateAnimation("12_Bazooka_Fly", "bazooka.bmp", 28, 28, 0.05f, false);
	//-236.25
	Renderer->CreateAnimation("11_Bazooka_Fly", "bazooka.bmp", 29, 29, 0.05f, false);
	//-247.5
	Renderer->CreateAnimation("10_Bazooka_Fly", "bazooka.bmp", 30, 30, 0.05f, false);
	//-258.75
	Renderer->CreateAnimation("9_Bazooka_Fly", "bazooka.bmp", 31, 31, 0.05f, false);
	//// -270
	//Renderer->CreateAnimation("Bazooka_Fly", "bazooka.bmp", 32, 32, 0.05f, false);

	SetWeaponDamage(BazookaDamage);
	SetWeaponSpeed(BazookaSpeed);


	ChangeState(BazookaState::Max);
}

void Bazooka::LevelStart()
{

}

void Bazooka::Update(float _Delta)
{
	CameraFocus(_Delta);
	StateUpdate(_Delta);
}


void Bazooka::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BazookaState::Fly:
		return FlyUpdate(_Delta);
	case BazookaState::Bomb:
		return BombUpdate(_Delta);
	case BazookaState::Damage:
		return DamageUpdate(_Delta);
	case BazookaState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void Bazooka::ChangeState(BazookaState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BazookaState::Fly:
			FlyStart();
			break;
		case BazookaState::Bomb:
			BombStart();
			break;
		case BazookaState::Damage:
			DamageStart();
			break;
		case BazookaState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

void Bazooka::DirCheck()
{
	Dir = GetGravityVector();
	float CurDir = Dir.AngleDeg();

	float CheckDir = CurDir / 11.25f;

	std::string Text = "";

	switch (static_cast<int>(CheckDir))
	{
	case 0:
		Renderer->ChangeAnimation("0_Bazooka_Fly");
		break;
	case 1:
		Renderer->ChangeAnimation("1_Bazooka_Fly");
		break;
	case 2:
		Renderer->ChangeAnimation("2_Bazooka_Fly");
		break;
	case 3:
		Renderer->ChangeAnimation("3_Bazooka_Fly");
		break;
	case 4:
		Renderer->ChangeAnimation("4_Bazooka_Fly");
		break;
	case 5:
		Renderer->ChangeAnimation("5_Bazooka_Fly");
		break;
	case 6:
		Renderer->ChangeAnimation("6_Bazooka_Fly");
		break;
	case 7:
		Renderer->ChangeAnimation("7_Bazooka_Fly");
		break;
	case 8:
		Renderer->ChangeAnimation("8_Bazooka_Fly");
		break;
	case 9:
		Renderer->ChangeAnimation("9_Bazooka_Fly");
		break;
	case 10:
		Renderer->ChangeAnimation("10_Bazooka_Fly");
		break;
	case 11:
		Renderer->ChangeAnimation("11_Bazooka_Fly");
		break;
	case 12:
		Renderer->ChangeAnimation("12_Bazooka_Fly");
		break;
	case 13:
		Renderer->ChangeAnimation("13_Bazooka_Fly");
		break;
	case 14:
		Renderer->ChangeAnimation("14_Bazooka_Fly");
		break;
	case 15:
		Renderer->ChangeAnimation("15_Bazooka_Fly");
		break;
	case 16:
		Renderer->ChangeAnimation("16_Bazooka_Fly");
		break;
	case 17:
		Renderer->ChangeAnimation("17_Bazooka_Fly");
		break;
	case 18:
		Renderer->ChangeAnimation("18_Bazooka_Fly");
		break;
	case 19:
		Renderer->ChangeAnimation("19_Bazooka_Fly");
		break;
	case 20:
		Renderer->ChangeAnimation("20_Bazooka_Fly");
		break;
	case 21:
		Renderer->ChangeAnimation("21_Bazooka_Fly");
		break;
	case 22:
		Renderer->ChangeAnimation("22_Bazooka_Fly");
		break;
	case 23:
		Renderer->ChangeAnimation("23_Bazooka_Fly");
		break;
	case 24:
		Renderer->ChangeAnimation("24_Bazooka_Fly");
		break;
	case 25:
		Renderer->ChangeAnimation("25_Bazooka_Fly");
		break;
	case 26:
		Renderer->ChangeAnimation("26_Bazooka_Fly");
		break;
	case 27:
		Renderer->ChangeAnimation("27_Bazooka_Fly");
		break;
	case 28:
		Renderer->ChangeAnimation("28_Bazooka_Fly");
		break;
	case 29:
		Renderer->ChangeAnimation("29_Bazooka_Fly");
		break;
	case 30:
		Renderer->ChangeAnimation("30_Bazooka_Fly");
		break;
	case 31:
		Renderer->ChangeAnimation("31_Bazooka_Fly");
		break;
	default:
		break;
	}
}

void Bazooka::FlyStart()
{
	SetGravityVector(AngleVec.GetRotationToDegZ(Master->GetCurAngle()) * GetChargingSpeed());
	Renderer->ChangeAnimation("0_Bazooka_Fly");
}

void Bazooka::FlyUpdate(float _Delta)
{
	DirCheck();
	Gravity(_Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (Color != RGB(255, 255, 255) || GetLiveTime() >= 5.0f)
	{

		ChangeState(BazookaState::Bomb);
		return;

	}

}

void Bazooka::BombStart()
{
	BazookaBomb = CreateBombEffect<Range50>();
	Renderer->Off();
}

void Bazooka::BombUpdate(float _Delta)
{
	if (true == BazookaBomb->GetRenderer()->IsAnimationEnd())
	{
		ChangeState(BazookaState::Damage);
		return;
	}
}

void Bazooka::DamageStart()
{

}

void Bazooka::DamageUpdate(float _Delta)
{
	size_t PlayerCount = Player::GetAllPlayer().size();
	int PlayerStateCount = 0;
	for (size_t i = 0; i < PlayerCount; i++)
	{
		if (PlayerState::Idle == Player::GetAllPlayer()[i]->GetState()/* || PlayerState::Die == Player::GetAllPlayer()[i]->GetState()*/)
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

void Bazooka::MaxStart()
{

}

void Bazooka::MaxUpdate(float _Delta)
{
	ChangeState(BazookaState::Fly);
	return;
}