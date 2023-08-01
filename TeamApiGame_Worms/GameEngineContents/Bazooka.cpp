#include "Bazooka.h"
#include "Ground.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "PlayLevel.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

Bazooka::Bazooka()
{

}

Bazooka::~Bazooka()
{

}

void Bazooka::Start()
{
	Renderer = CreateRenderer(RenderOrder::Weapon);

	if (false == ResourcesManager::GetInst().IsLoadTexture("bullet.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("bullet.bmp"), 1, 32);
		//ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("bullet.bmp"));
	}

	Renderer->SetTexture("bullet.bmp");
	// 90도
	Renderer->CreateAnimation("8_Bazooka_Fly", "bullet.bmp", 0, 0, 0.05f, false);
	// 78.75도
	Renderer->CreateAnimation("7_Bazooka_Fly", "bullet.bmp", 1, 1, 0.05f, false);
	// 67.5도
	Renderer->CreateAnimation("6_Bazooka_Fly", "bullet.bmp", 2, 2, 0.05f, false);
	// 56.25도
	Renderer->CreateAnimation("5_Bazooka_Fly", "bullet.bmp", 3, 3, 0.05f, false);
	// 45 도
	Renderer->CreateAnimation("4_Bazooka_Fly", "bullet.bmp", 4, 4, 0.05f, false);
	// 33.75도
	Renderer->CreateAnimation("3_Bazooka_Fly", "bullet.bmp", 5, 5, 0.05f, false);
	// 22,5도
	Renderer->CreateAnimation("2_Bazooka_Fly", "bullet.bmp", 6, 6, 0.05f, false);
	// 11.25도
	Renderer->CreateAnimation("1_Bazooka_Fly", "bullet.bmp", 7, 7, 0.05f, false);
	// 0도
	Renderer->CreateAnimation("0_Bazooka_Fly", "bullet.bmp", 8, 8, 0.05f, false);
	// -11.25도
	Renderer->CreateAnimation("31_Bazooka_Fly", "bullet.bmp", 9, 9, 0.05f, false);
	// -22.5도
	Renderer->CreateAnimation("30_Bazooka_Fly", "bullet.bmp", 10, 10, 0.05f, false);
	// -33.75도
	Renderer->CreateAnimation("29_Bazooka_Fly", "bullet.bmp", 11, 11, 0.05f, false);
	// -45도
	Renderer->CreateAnimation("28_Bazooka_Fly", "bullet.bmp", 12, 12, 0.05f, false);
	// -56.25도
	Renderer->CreateAnimation("27_Bazooka_Fly", "bullet.bmp", 13, 13, 0.05f, false);
	// -67.5도
	Renderer->CreateAnimation("26_Bazooka_Fly", "bullet.bmp", 14, 14, 0.05f, false);
	// -78.75도
	Renderer->CreateAnimation("25_Bazooka_Fly", "bullet.bmp", 15, 15, 0.05f, false);
	// -90 도
	Renderer->CreateAnimation("24_Bazooka_Fly", "bullet.bmp", 16, 16, 0.05f, false);
	// -101.25 도
	Renderer->CreateAnimation("23_Bazooka_Fly", "bullet.bmp", 17, 17, 0.05f, false);
	// -112.5도
	Renderer->CreateAnimation("22_Bazooka_Fly", "bullet.bmp", 18, 18, 0.05f, false);
	// -123.75도
	Renderer->CreateAnimation("21_Bazooka_Fly", "bullet.bmp", 19, 19, 0.05f, false);
	// -135도
	Renderer->CreateAnimation("20_Bazooka_Fly", "bullet.bmp", 20, 20, 0.05f, false);
	// -146.25도
	Renderer->CreateAnimation("19_Bazooka_Fly", "bullet.bmp", 21, 21, 0.05f, false);
	//-157.5
	Renderer->CreateAnimation("18_Bazooka_Fly", "bullet.bmp", 22, 22, 0.05f, false);
	//-168.75
	Renderer->CreateAnimation("17_Bazooka_Fly", "bullet.bmp", 23, 23, 0.05f, false);
	//-180
	Renderer->CreateAnimation("16_Bazooka_Fly", "bullet.bmp", 24, 24, 0.05f, false);
	//-191.25
	Renderer->CreateAnimation("15_Bazooka_Fly", "bullet.bmp", 25, 25, 0.05f, false);
	//-202.5
	Renderer->CreateAnimation("14_Bazooka_Fly", "bullet.bmp", 26, 26, 0.05f, false);
	//-213.75
	Renderer->CreateAnimation("13_Bazooka_Fly", "bullet.bmp", 27, 27, 0.05f, false);
	//-225
	Renderer->CreateAnimation("12_Bazooka_Fly", "bullet.bmp", 28, 28, 0.05f, false);
	//-236.25
	Renderer->CreateAnimation("11_Bazooka_Fly", "bullet.bmp", 29, 29, 0.05f, false);
	//-247.5
	Renderer->CreateAnimation("10_Bazooka_Fly", "bullet.bmp", 30, 30, 0.05f, false);
	//-258.75
	Renderer->CreateAnimation("9_Bazooka_Fly", "bullet.bmp", 31, 31, 0.05f, false);
	//// -270
	//Renderer->CreateAnimation("Bazooka_Fly", "bullet.bmp", 32, 32, 0.05f, false);

	SetDir(Player::DirPos);

	//GravityDir = float4::UP;
	GravityDir += Dir * 40.0f;

	float Angle = 0.0f;
	float4 AngleVec = { 1.0f, 0.0f };
	SetGravityVector(AngleVec.GetRotationToDegZ(Angle) * 200.0f);

	ChangeState(BazookaState::Fly);

}

void Bazooka::LevelStart()
{


	SetPos(Master->GetPos() + float4{0, -15});

}

void Bazooka::Update(float _Delta)
{
	DirCheck();
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

	//for (float i = 0.0f; CurDir >= i ; i+=11.25f)
	//{
	//	if (CurDir <= i)
	//	{
	//		CurDir /= 11.25f;

	//		Text += std::to_string(static_cast<int>(CurDir));
	//		Text += "_Bazooka_Fly";
	//		Renderer->ChangeAnimation(Text);
	//		return;
	//	}
	//}


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
	Renderer->ChangeAnimation("Bazooka_Fly");
}

void Bazooka::FlyUpdate(float _Delta)
{
	Gravity(_Delta);

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (Color != RGB(255, 255, 255))
		{


			// PlayLevel에서 만 존재하는 것에만 사용할수 있는예제코드
			{
				PlayLevel* CurPlayLevel = dynamic_cast<PlayLevel*>(GetLevel());
				CurPlayLevel->GetGround()->ContactGround(GetPos());

				Off();
			}

		}
	}

}

void Bazooka::BombStart()
{
	Renderer->ChangeAnimation("Bazooka_Boom");
}

void Bazooka::BombUpdate(float _Delta)
{
	if (0.4f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Death();
		}
	}
}
