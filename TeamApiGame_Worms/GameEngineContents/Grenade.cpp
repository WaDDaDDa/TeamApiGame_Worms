#include "Grenade.h"
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
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEnginecollision.h>

Grenade::Grenade()
{

}

Grenade::~Grenade()
{

}

void Grenade::Start()
{
	Renderer = CreateRenderer(RenderOrder::Weapon);

	if (false == ResourcesManager::GetInst().IsLoadTexture("grenade.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("grenade.bmp"), 1, 32);
	}

	// 사운드 로드
	if (nullptr == GameEngineSound::FindSound("Grenadeimpact.WAV"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Effects\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Grenadeimpact.WAV"));
	}

	SoundEffect = GameEngineSound::SoundPlay("THROWRELEASE.WAV");

	
	Renderer->SetTexture("Blank.bmp");

	Renderer->CreateAnimation("Grenade_Fly", "grenade.bmp", 0, 31, 0.001f, true);

	// 90도
	Renderer->CreateAnimation("8_Grenade_Fly", "grenade.bmp", 0, 0, 0.05f, false);
	// 78.75도
	Renderer->CreateAnimation("7_Grenade_Fly", "grenade.bmp", 1, 1, 0.05f, false);
	// 67.5도
	Renderer->CreateAnimation("6_Grenade_Fly", "grenade.bmp", 2, 2, 0.05f, false);
	// 56.25도
	Renderer->CreateAnimation("5_Grenade_Fly", "grenade.bmp", 3, 3, 0.05f, false);
	// 45 도
	Renderer->CreateAnimation("4_Grenade_Fly", "grenade.bmp", 4, 4, 0.05f, false);
	// 33.75도
	Renderer->CreateAnimation("3_Grenade_Fly", "grenade.bmp", 5, 5, 0.05f, false);
	// 22,5도
	Renderer->CreateAnimation("2_Grenade_Fly", "grenade.bmp", 6, 6, 0.05f, false);
	// 11.25도
	Renderer->CreateAnimation("1_Grenade_Fly", "grenade.bmp", 7, 7, 0.05f, false);
	// 0도
	Renderer->CreateAnimation("0_Grenade_Fly", "grenade.bmp", 8, 8, 0.05f, false);
	// -11.25도
	Renderer->CreateAnimation("31_Grenade_Fly", "grenade.bmp", 9, 9, 0.05f, false);
	// -22.5도
	Renderer->CreateAnimation("30_Grenade_Fly", "grenade.bmp", 10, 10, 0.05f, false);
	// -33.75도
	Renderer->CreateAnimation("29_Grenade_Fly", "grenade.bmp", 11, 11, 0.05f, false);
	// -45도
	Renderer->CreateAnimation("28_Grenade_Fly", "grenade.bmp", 12, 12, 0.05f, false);
	// -56.25도
	Renderer->CreateAnimation("27_Grenade_Fly", "grenade.bmp", 13, 13, 0.05f, false);
	// -67.5도
	Renderer->CreateAnimation("26_Grenade_Fly", "grenade.bmp", 14, 14, 0.05f, false);
	// -78.75도
	Renderer->CreateAnimation("25_Grenade_Fly", "grenade.bmp", 15, 15, 0.05f, false);
	// -90 도
	Renderer->CreateAnimation("24_Grenade_Fly", "grenade.bmp", 16, 16, 0.05f, false);
	// -101.25 도
	Renderer->CreateAnimation("23_Grenade_Fly", "grenade.bmp", 17, 17, 0.05f, false);
	// -112.5도
	Renderer->CreateAnimation("22_Grenade_Fly", "grenade.bmp", 18, 18, 0.05f, false);
	// -123.75도
	Renderer->CreateAnimation("21_Grenade_Fly", "grenade.bmp", 19, 19, 0.05f, false);
	// -135도
	Renderer->CreateAnimation("20_Grenade_Fly", "grenade.bmp", 20, 20, 0.05f, false);
	// -146.25도
	Renderer->CreateAnimation("19_Grenade_Fly", "grenade.bmp", 21, 21, 0.05f, false);
	//-157.5
	Renderer->CreateAnimation("18_Grenade_Fly", "grenade.bmp", 22, 22, 0.05f, false);
	//-168.75
	Renderer->CreateAnimation("17_Grenade_Fly", "grenade.bmp", 23, 23, 0.05f, false);
	//-180
	Renderer->CreateAnimation("16_Grenade_Fly", "grenade.bmp", 24, 24, 0.05f, false);
	//-191.25
	Renderer->CreateAnimation("15_Grenade_Fly", "grenade.bmp", 25, 25, 0.05f, false);
	//-202.5
	Renderer->CreateAnimation("14_Grenade_Fly", "grenade.bmp", 26, 26, 0.05f, false);
	//-213.75
	Renderer->CreateAnimation("13_Grenade_Fly", "grenade.bmp", 27, 27, 0.05f, false);
	//-225
	Renderer->CreateAnimation("12_Grenade_Fly", "grenade.bmp", 28, 28, 0.05f, false);
	//-236.25
	Renderer->CreateAnimation("11_Grenade_Fly", "grenade.bmp", 29, 29, 0.05f, false);
	//-247.5
	Renderer->CreateAnimation("10_Grenade_Fly", "grenade.bmp", 30, 30, 0.05f, false);
	//-258.75
	Renderer->CreateAnimation("9_Grenade_Fly", "grenade.bmp", 31, 31, 0.05f, false);
	//// -270
	//Renderer->CreateAnimation("Grenade_Fly", "grenade.bmp", 32, 32, 0.05f, false);



	{
		//Collision
		BodyCollision = CreateCollision(CollisionOrder::Weapon);

		BodyCollision->SetCollisionScale({ 10, 10 });
		BodyCollision->SetCollisionType(CollisionType::CirCle);
		//GrenadeCollision->SetCollisionPos({ 0, -10 });
	}

	SetWeaponDamage(GrenadeDamage);
	SetWeaponSpeed(GrenadeSpeed);

	IsWindOn();

	ChangeState(GrenadeState::Max);
}

void Grenade::LevelStart()
{

}

void Grenade::Update(float _Delta)
{
	CameraFocus(_Delta);
	StateUpdate(_Delta);
}


void Grenade::StateUpdate(float _Delta)
{
	switch (State)
	{
	case GrenadeState::Ready:
		return ReadyUpdate(_Delta);
	case GrenadeState::Idle:
		return IdleUpdate(_Delta);
	case GrenadeState::Fly:
		return FlyUpdate(_Delta);
	case GrenadeState::PrevBomb:
		return PrevBombUpdate(_Delta);
	case GrenadeState::Bomb:
		return BombUpdate(_Delta);
	case GrenadeState::Damage:
		return DamageUpdate(_Delta);
	case GrenadeState::InWater:
		return InWaterUpdate(_Delta);
	case GrenadeState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void Grenade::ChangeState(GrenadeState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case GrenadeState::Ready:
			ReadyStart();
			break;
		case GrenadeState::Idle:
			IdleStart();
			break;
		case GrenadeState::Fly:
			FlyStart();
			break;
		case GrenadeState::PrevBomb:
			PrevBombStart();
			break;
		case GrenadeState::Bomb:
			BombStart();
			break;
		case GrenadeState::Damage:
			DamageStart();
			break;
		case GrenadeState::InWater:
			InWaterStart();
			break;
		case GrenadeState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

void Grenade::DirCheck()
{
	Dir = GetGravityVector();
	float CurDir = Dir.AngleDeg();

	float CheckDir = CurDir / 11.25f;

	std::string Text = "";

	switch (static_cast<int>(CheckDir))
	{
	case 0:
		Renderer->ChangeAnimation("0_Grenade_Fly");
		break;
	case 1:
		Renderer->ChangeAnimation("1_Grenade_Fly");
		break;
	case 2:
		Renderer->ChangeAnimation("2_Grenade_Fly");
		break;
	case 3:
		Renderer->ChangeAnimation("3_Grenade_Fly");
		break;
	case 4:
		Renderer->ChangeAnimation("4_Grenade_Fly");
		break;
	case 5:
		Renderer->ChangeAnimation("5_Grenade_Fly");
		break;
	case 6:
		Renderer->ChangeAnimation("6_Grenade_Fly");
		break;
	case 7:
		Renderer->ChangeAnimation("7_Grenade_Fly");
		break;
	case 8:
		Renderer->ChangeAnimation("8_Grenade_Fly");
		break;
	case 9:
		Renderer->ChangeAnimation("9_Grenade_Fly");
		break;
	case 10:
		Renderer->ChangeAnimation("10_Grenade_Fly");
		break;
	case 11:
		Renderer->ChangeAnimation("11_Grenade_Fly");
		break;
	case 12:
		Renderer->ChangeAnimation("12_Grenade_Fly");
		break;
	case 13:
		Renderer->ChangeAnimation("13_Grenade_Fly");
		break;
	case 14:
		Renderer->ChangeAnimation("14_Grenade_Fly");
		break;
	case 15:
		Renderer->ChangeAnimation("15_Grenade_Fly");
		break;
	case 16:
		Renderer->ChangeAnimation("16_Grenade_Fly");
		break;
	case 17:
		Renderer->ChangeAnimation("17_Grenade_Fly");
		break;
	case 18:
		Renderer->ChangeAnimation("18_Grenade_Fly");
		break;
	case 19:
		Renderer->ChangeAnimation("19_Grenade_Fly");
		break;
	case 20:
		Renderer->ChangeAnimation("20_Grenade_Fly");
		break;
	case 21:
		Renderer->ChangeAnimation("21_Grenade_Fly");
		break;
	case 22:
		Renderer->ChangeAnimation("22_Grenade_Fly");
		break;
	case 23:
		Renderer->ChangeAnimation("23_Grenade_Fly");
		break;
	case 24:
		Renderer->ChangeAnimation("24_Grenade_Fly");
		break;
	case 25:
		Renderer->ChangeAnimation("25_Grenade_Fly");
		break;
	case 26:
		Renderer->ChangeAnimation("26_Grenade_Fly");
		break;
	case 27:
		Renderer->ChangeAnimation("27_Grenade_Fly");
		break;
	case 28:
		Renderer->ChangeAnimation("28_Grenade_Fly");
		break;
	case 29:
		Renderer->ChangeAnimation("29_Grenade_Fly");
		break;
	case 30:
		Renderer->ChangeAnimation("30_Grenade_Fly");
		break;
	case 31:
		Renderer->ChangeAnimation("31_Grenade_Fly");
		break;
	default:
		break;
	}
}


void Grenade::GroundCheck(float _Delta)
{
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));

	// 위치가 흰색이면 중력작용.
	// 모두 흰색이면 공중이다.
	if (RGB(255, 255, 255) == Color)
	{
		Gravity(_Delta);
	}
	else // 모두흰색이 아니다 = 땅에닿아있다.
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

		// 체크중 어느하나라도  흰색이 아니라면 한칸올리기 반복한다.
		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			AddPos(float4::UP);
		}
		//TongTong();
	}
}

void Grenade::TongTong(float4 _Pos)
{
	SoundEffect = GameEngineSound::SoundPlay("Grenadeimpact.WAV");

	unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255));

	float4 CurCravityVector = GetGravityVector();
	float4 ReflectionDeg = float4::ZERO;

	ReflectionDeg = -CurCravityVector;
	ReflectionDeg.Normalize();
	ReflectionDeg *= 100.0f;
	// 현재 벡터의 각도
	float CurDeg = ReflectionDeg.AngleDeg();

	CheckColor = GetGroundColor(RGB(255, 255, 255), _Pos + ReflectionDeg);

	// 오른쪽 각도
	while (CheckColor == RGB(255, 255, 255))
	{
		ReflectionDeg = ReflectionDeg.GetRotationToDegZ(1.0f);
		CheckColor = GetGroundColor(RGB(255, 255, 255), _Pos + ReflectionDeg);
	}
	// 오른쪽으로 돌았을때의 제일 처음 픽셀 충돌되는 각도
	float4 RightDir = ReflectionDeg;
	float RightDeg = ReflectionDeg.AngleDeg();


	ReflectionDeg = -CurCravityVector;
	ReflectionDeg.Normalize();
	ReflectionDeg *= 100.0f;

	CheckColor = GetGroundColor(RGB(255, 255, 255), _Pos + ReflectionDeg);

	// 왼쪽 각도
	while (CheckColor == RGB(255, 255, 255))
	{
		ReflectionDeg = ReflectionDeg.GetRotationToDegZ(-1.0f);
		CheckColor = GetGroundColor(RGB(255, 255, 255), _Pos + ReflectionDeg);
	}
	// 왼쪽으로 돌았을때의 제일 처음 픽셀 충돌되는 각도
	float4 LeftDir = ReflectionDeg;
	float LeftDeg = ReflectionDeg.AngleDeg();

	float4 LastDir = RightDir - LeftDir;
	float LastDeg = LastDir.AngleDeg();

	if (LastDeg <= 1.0f || LastDeg >= 359.0f)
	{
		float4 Test = CurCravityVector;
		Test.Y = -Test.Y;
		SetGravityVector(Test * 0.6f);
		return;
	}

	//if (LastDeg <= 181.0f || LastDeg >= 179.0f)
	//{
	//	float4 Test = CurCravityVector;
	//	Test.Y = -Test.Y;
	//	SetGravityVector(Test * 0.6f);
	//	return;
	//}

	//if (LastDeg <= 91.0f || LastDeg >= 89.0f)
	//{
 //		float4 Test = CurCravityVector;
	//	Test.X = -Test.X;
	//	SetGravityVector(Test * 0.6f);
	//	return;
	//}

	// CurCravityVector.Y = 0.0f;
	float4 Test = -CurCravityVector;
	Test = Test.GetRotationToDegZ(-(LastDeg + LastDeg));
	SetGravityVector(Test * 0.6f);
	return;
}

void Grenade::IdleStart()
{
	//SetGravityVector(-(GetGravityVector() * 0.8f));
}

void Grenade::IdleUpdate(float _Delta)
{
	DirCheck();
	Gravity(_Delta);
	//GroundCheck(_Delta);

	float4 Check = DownCheckPos;

	if (RGB(255, 255, 255) != GetGroundColor(RGB(255, 255, 255)))
	{
		ChangeState(GrenadeState::PrevBomb);
		return;
	}


	for (size_t i = 0; i <= 36; i++)
	{
		Check = Check.GetRotationToDegZ(i * 10.0f);

		if (RGB(255, 255, 255) != GetGroundColor(RGB(255, 255, 255), Check))
		{
			TongTong(Check);
			DownCheckPos = { DownCheckPos.X , DownCheckPos.Y - 1 };
			//ChangeState(GrenadeState::Fly);
			return;
		}
	}

	if (GetLiveTime() >= 3.0f)
	{
		ChangeState(GrenadeState::Bomb);
		return;
	}

	// 물에 빠짐
	if (GetPos().Y >= 1875)
	{
		ChangeState(GrenadeState::InWater);
		return;
	}
}

void Grenade::FlyStart()
{
	//SetGravityVector(AngleVec.GetRotationToDegZ(Master->GetCurAngle()) * GetChargingSpeed());
	Renderer->ChangeAnimation("Grenade_Fly");
}

void Grenade::FlyUpdate(float _Delta)
{
	//GroundCheck(_Delta);
	//DirCheck();
	Gravity(_Delta);

	// 튕기는걸 세부화 해야함. 보류();
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	unsigned int DownColor = GetGroundColor(RGB(255, 255, 255), DownCheckPos);

	float4 CurCravityVector = GetGravityVector();
	float YVector = CurCravityVector.Y;

	if (RGB(255, 255, 255) != Color)
	{
		//ChangeState(GrenadeState::Idle);
		//return;
	}

	// 위치가 흰색이면 중력작용.
	// 모두 흰색이면 공중이다.
	float4 Check = DownCheckPos;
	for (size_t i = 0; i <= 36; i++)
	{
		Check = Check.GetRotationToDegZ(i * 10.0f);

		if (RGB(255, 255, 255) != GetGroundColor(RGB(255, 255, 255), Check))
		{
			TongTong(Check);
			ChangeState(GrenadeState::Idle);
			return;
		}
	}

	if (GetLiveTime() >= 5.0f)
	{
		ChangeState(GrenadeState::Bomb);
		return;
	}

	// 물에 빠짐
	if (GetPos().Y >= 1875)
	{
		ChangeState(GrenadeState::InWater);
		return;
	}
}

void Grenade::PrevBombStart()
{

}

void Grenade::PrevBombUpdate(float _Delta)
{
	//DirCheck();
	GroundCheck(_Delta);

	if (GetLiveTime() >= 3.0f)
	{
		ChangeState(GrenadeState::Bomb);
		return;
	}
}



void Grenade::BombStart()
{
	GrenadeBomb = CreateBombEffect<Range75>();
	SoundEffect = GameEngineSound::SoundPlay("Explosion2.WAV");
	Renderer->Off();
}

void Grenade::BombUpdate(float _Delta)
{
	if (true == GrenadeBomb->GetRenderer()->IsAnimationEnd())
	{
		ChangeState(GrenadeState::Damage);
		return;
	}
}

void Grenade::DamageStart()
{

}

void Grenade::DamageUpdate(float _Delta)
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


void Grenade::InWaterStart()
{
	SoundEffect = GameEngineSound::SoundPlay("splish.WAV");

	SetGravityVector(float4::DOWN);
	IsWindOff();
	SetGravityPower(100.0f);
	DirCheck();
}

void Grenade::InWaterUpdate(float _Delta)
{
	Gravity(_Delta);

	if (GetLiveTime() >= 3.0f)
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
		return;
	}
}

void Grenade::MaxStart()
{

}

void Grenade::MaxUpdate(float _Delta)
{
	ChangeState(GrenadeState::Ready);
	return;
}

void Grenade::ReadyStart()
{
	SetGravityVector(AngleVec.GetRotationToDegZ(Master->GetCurAngle()) * GetChargingSpeed());
}

void Grenade::ReadyUpdate(float _Delta)
{
	ChangeState(GrenadeState::Fly);
	return;
}

void Grenade::Render(float _Delta)
{
	/*HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	{
		CollisionData Data;

		Data.Pos = ActorCameraPos();

		Data.Scale = { 5,5 };

		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}

	{
		CollisionData Data;

		Data.Pos = ActorCameraPos() + LeftCheckPos;

		Data.Scale = { 5,5 };

		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}

	{
		CollisionData Data;

		Data.Pos = ActorCameraPos() + RightCheckPos;

		Data.Scale = { 5,5 };

		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}

	{
		CollisionData Data;

		Data.Pos = ActorCameraPos() + UpCheckPos;

		Data.Scale = { 5,5 };

		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}

	{
		CollisionData Data;

		Data.Pos = ActorCameraPos() + DownCheckPos;

		Data.Scale = { 5,5 };

		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}

	{
		HDC dc2 = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

		std::string Text2 = "GravityVector : ";
		Text2 += std::to_string(GetGravityVector().AngleDeg());
		Text2 += "  , ";
		Text2 += std::to_string(GetGravityVector().iX());
		Text2 += "  , ";
		Text2 += std::to_string(GetGravityVector().iY());

		TextOutA(dc2, 2, 40, Text2.c_str(), static_cast<int>(Text2.size()));
	}*/
}