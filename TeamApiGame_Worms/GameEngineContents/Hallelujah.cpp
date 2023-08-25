#include "Hallelujah.h"
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
#include <GameEnginePlatform/GameEngineSound.h>


Hallelujah::Hallelujah()
{

}

Hallelujah::~Hallelujah()
{

}

void Hallelujah::Start()
{
	Renderer = CreateRenderer(RenderOrder::Weapon);

	if (false == ResourcesManager::GetInst().IsLoadTexture("hgrenade.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("hgrenade.bmp"), 1, 32);
	}

	
	Renderer->SetTexture("Blank.bmp");

	Renderer->CreateAnimation("Hallelujah_Fly", "hgrenade.bmp", 0, 31, 0.001f, true);

	// 90도
	Renderer->CreateAnimation("8_Hallelujah_Fly", "hgrenade.bmp", 0, 0, 0.05f, false);
	// 78.75도
	Renderer->CreateAnimation("7_Hallelujah_Fly", "hgrenade.bmp", 1, 1, 0.05f, false);
	// 67.5도
	Renderer->CreateAnimation("6_Hallelujah_Fly", "hgrenade.bmp", 2, 2, 0.05f, false);
	// 56.25도
	Renderer->CreateAnimation("5_Hallelujah_Fly", "hgrenade.bmp", 3, 3, 0.05f, false);
	// 45 도
	Renderer->CreateAnimation("4_Hallelujah_Fly", "hgrenade.bmp", 4, 4, 0.05f, false);
	// 33.75도
	Renderer->CreateAnimation("3_Hallelujah_Fly", "hgrenade.bmp", 5, 5, 0.05f, false);
	// 22,5도
	Renderer->CreateAnimation("2_Hallelujah_Fly", "hgrenade.bmp", 6, 6, 0.05f, false);
	// 11.25도
	Renderer->CreateAnimation("1_Hallelujah_Fly", "hgrenade.bmp", 7, 7, 0.05f, false);
	// 0도
	Renderer->CreateAnimation("0_Hallelujah_Fly", "hgrenade.bmp", 8, 8, 0.05f, false);
	// -11.25도
	Renderer->CreateAnimation("31_Hallelujah_Fly", "hgrenade.bmp", 9, 9, 0.05f, false);
	// -22.5도
	Renderer->CreateAnimation("30_Hallelujah_Fly", "hgrenade.bmp", 10, 10, 0.05f, false);
	// -33.75도
	Renderer->CreateAnimation("29_Hallelujah_Fly", "hgrenade.bmp", 11, 11, 0.05f, false);
	// -45도
	Renderer->CreateAnimation("28_Hallelujah_Fly", "hgrenade.bmp", 12, 12, 0.05f, false);
	// -56.25도
	Renderer->CreateAnimation("27_Hallelujah_Fly", "hgrenade.bmp", 13, 13, 0.05f, false);
	// -67.5도
	Renderer->CreateAnimation("26_Hallelujah_Fly", "hgrenade.bmp", 14, 14, 0.05f, false);
	// -78.75도
	Renderer->CreateAnimation("25_Hallelujah_Fly", "hgrenade.bmp", 15, 15, 0.05f, false);
	// -90 도
	Renderer->CreateAnimation("24_Hallelujah_Fly", "hgrenade.bmp", 16, 16, 0.05f, false);
	// -101.25 도
	Renderer->CreateAnimation("23_Hallelujah_Fly", "hgrenade.bmp", 17, 17, 0.05f, false);
	// -112.5도
	Renderer->CreateAnimation("22_Hallelujah_Fly", "hgrenade.bmp", 18, 18, 0.05f, false);
	// -123.75도
	Renderer->CreateAnimation("21_Hallelujah_Fly", "hgrenade.bmp", 19, 19, 0.05f, false);
	// -135도
	Renderer->CreateAnimation("20_Hallelujah_Fly", "hgrenade.bmp", 20, 20, 0.05f, false);
	// -146.25도
	Renderer->CreateAnimation("19_Hallelujah_Fly", "hgrenade.bmp", 21, 21, 0.05f, false);
	//-157.5
	Renderer->CreateAnimation("18_Hallelujah_Fly", "hgrenade.bmp", 22, 22, 0.05f, false);
	//-168.75
	Renderer->CreateAnimation("17_Hallelujah_Fly", "hgrenade.bmp", 23, 23, 0.05f, false);
	//-180
	Renderer->CreateAnimation("16_Hallelujah_Fly", "hgrenade.bmp", 24, 24, 0.05f, false);
	//-191.25
	Renderer->CreateAnimation("15_Hallelujah_Fly", "hgrenade.bmp", 25, 25, 0.05f, false);
	//-202.5
	Renderer->CreateAnimation("14_Hallelujah_Fly", "hgrenade.bmp", 26, 26, 0.05f, false);
	//-213.75
	Renderer->CreateAnimation("13_Hallelujah_Fly", "hgrenade.bmp", 27, 27, 0.05f, false);
	//-225
	Renderer->CreateAnimation("12_Hallelujah_Fly", "hgrenade.bmp", 28, 28, 0.05f, false);
	//-236.25
	Renderer->CreateAnimation("11_Hallelujah_Fly", "hgrenade.bmp", 29, 29, 0.05f, false);
	//-247.5
	Renderer->CreateAnimation("10_Hallelujah_Fly", "hgrenade.bmp", 30, 30, 0.05f, false);
	//-258.75
	Renderer->CreateAnimation("9_Hallelujah_Fly", "hgrenade.bmp", 31, 31, 0.05f, false);
	//// -270
	//Renderer->CreateAnimation("Hallelujah_Fly", "hgrenade.bmp", 32, 32, 0.05f, false);

	// 사운드 로드
	if (nullptr == GameEngineSound::FindSound("HOLYGRENADE.WAV"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Effects\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("HOLYGRENADE.WAV"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("holygrenadeimpact.WAV"));
	}

	{
		//Collision
		BodyCollision = CreateCollision(CollisionOrder::Weapon);

		BodyCollision->SetCollisionScale({ 10, 10 });
		BodyCollision->SetCollisionType(CollisionType::CirCle);
		// HallelujahCollision->SetCollisionPos({ 0, -10 });
	}

	SoundEffect = GameEngineSound::SoundPlay("THROWRELEASE.WAV");

	SetWeaponDamage(HallelujahDamage);
	SetWeaponSpeed(HallelujahSpeed);

	IsWindOn();

	ChangeState(HallelujahState::Max);
}

void Hallelujah::LevelStart()
{

}

void Hallelujah::Update(float _Delta)
{
	CameraFocus(_Delta);
	StateUpdate(_Delta);
}


void Hallelujah::StateUpdate(float _Delta)
{
	switch (State)
	{
	case HallelujahState::Ready:
		return ReadyUpdate(_Delta);
	case HallelujahState::Idle:
		return IdleUpdate(_Delta);
	case HallelujahState::Fly:
		return FlyUpdate(_Delta);
	case HallelujahState::PrevBomb:
		return PrevBombUpdate(_Delta);
	case HallelujahState::Bomb:
		return BombUpdate(_Delta);
	case HallelujahState::Damage:
		return DamageUpdate(_Delta);
	case HallelujahState::InWater:
		return InWaterUpdate(_Delta);
	case HallelujahState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void Hallelujah::ChangeState(HallelujahState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case HallelujahState::Ready:
			ReadyStart();
			break;
		case HallelujahState::Idle:
			IdleStart();
			break;
		case HallelujahState::Fly:
			FlyStart();
			break;
		case HallelujahState::PrevBomb:
			PrevBombStart();
			break;
		case HallelujahState::Bomb:
			BombStart();
			break;
		case HallelujahState::Damage:
			DamageStart();
			break;
		case HallelujahState::InWater:
			InWaterStart();
			break;
		case HallelujahState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

void Hallelujah::DirCheck()
{
	Dir = GetGravityVector();
	float CurDir = Dir.AngleDeg();

	float CheckDir = CurDir / 11.25f;

	std::string Text = "";

	switch (static_cast<int>(CheckDir))
	{
	case 0:
		Renderer->ChangeAnimation("0_Hallelujah_Fly");
		break;
	case 1:
		Renderer->ChangeAnimation("1_Hallelujah_Fly");
		break;
	case 2:
		Renderer->ChangeAnimation("2_Hallelujah_Fly");
		break;
	case 3:
		Renderer->ChangeAnimation("3_Hallelujah_Fly");
		break;
	case 4:
		Renderer->ChangeAnimation("4_Hallelujah_Fly");
		break;
	case 5:
		Renderer->ChangeAnimation("5_Hallelujah_Fly");
		break;
	case 6:
		Renderer->ChangeAnimation("6_Hallelujah_Fly");
		break;
	case 7:
		Renderer->ChangeAnimation("7_Hallelujah_Fly");
		break;
	case 8:
		Renderer->ChangeAnimation("8_Hallelujah_Fly");
		break;
	case 9:
		Renderer->ChangeAnimation("9_Hallelujah_Fly");
		break;
	case 10:
		Renderer->ChangeAnimation("10_Hallelujah_Fly");
		break;
	case 11:
		Renderer->ChangeAnimation("11_Hallelujah_Fly");
		break;
	case 12:
		Renderer->ChangeAnimation("12_Hallelujah_Fly");
		break;
	case 13:
		Renderer->ChangeAnimation("13_Hallelujah_Fly");
		break;
	case 14:
		Renderer->ChangeAnimation("14_Hallelujah_Fly");
		break;
	case 15:
		Renderer->ChangeAnimation("15_Hallelujah_Fly");
		break;
	case 16:
		Renderer->ChangeAnimation("16_Hallelujah_Fly");
		break;
	case 17:
		Renderer->ChangeAnimation("17_Hallelujah_Fly");
		break;
	case 18:
		Renderer->ChangeAnimation("18_Hallelujah_Fly");
		break;
	case 19:
		Renderer->ChangeAnimation("19_Hallelujah_Fly");
		break;
	case 20:
		Renderer->ChangeAnimation("20_Hallelujah_Fly");
		break;
	case 21:
		Renderer->ChangeAnimation("21_Hallelujah_Fly");
		break;
	case 22:
		Renderer->ChangeAnimation("22_Hallelujah_Fly");
		break;
	case 23:
		Renderer->ChangeAnimation("23_Hallelujah_Fly");
		break;
	case 24:
		Renderer->ChangeAnimation("24_Hallelujah_Fly");
		break;
	case 25:
		Renderer->ChangeAnimation("25_Hallelujah_Fly");
		break;
	case 26:
		Renderer->ChangeAnimation("26_Hallelujah_Fly");
		break;
	case 27:
		Renderer->ChangeAnimation("27_Hallelujah_Fly");
		break;
	case 28:
		Renderer->ChangeAnimation("28_Hallelujah_Fly");
		break;
	case 29:
		Renderer->ChangeAnimation("29_Hallelujah_Fly");
		break;
	case 30:
		Renderer->ChangeAnimation("30_Hallelujah_Fly");
		break;
	case 31:
		Renderer->ChangeAnimation("31_Hallelujah_Fly");
		break;
	default:
		break;
	}
}


void Hallelujah::GroundCheck(float _Delta)
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

void Hallelujah::TongTong(float4 _Pos)
{
	SoundEffect = GameEngineSound::SoundPlay("holygrenadeimpact.WAV");

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

	// CurCravityVector.Y = 0.0f;
	float4 Test = -CurCravityVector;
	Test = Test.GetRotationToDegZ(-(LastDeg + LastDeg));
	SetGravityVector(Test * 0.6f);
	return;
}

void Hallelujah::IdleStart()
{
	//SetGravityVector(-(GetGravityVector() * 0.8f));
}

void Hallelujah::IdleUpdate(float _Delta)
{
	DirCheck();
	Gravity(_Delta);
	//GroundCheck(_Delta);

	float4 Check = DownCheckPos;

	if (RGB(255, 255, 255) != GetGroundColor(RGB(255, 255, 255)))
	{
		ChangeState(HallelujahState::PrevBomb);
		return;
	}


	for (size_t i = 0; i <= 36; i++)
	{
		Check = Check.GetRotationToDegZ(i * 10.0f);

		if (RGB(255, 255, 255) != GetGroundColor(RGB(255, 255, 255), Check))
		{
			TongTong(Check);
			DownCheckPos = { DownCheckPos.X , DownCheckPos.Y - 1 };
			//ChangeState(HallelujahState::Fly);
			return;
		}
	}

	if (GetLiveTime() >= 3.0f)
	{
		ChangeState(HallelujahState::PrevBomb);
		return;
	}

	// 물에 빠짐
	if (GetPos().Y >= 1875)
	{
		ChangeState(HallelujahState::InWater);
		return;
	}
}

void Hallelujah::FlyStart()
{
	//SetGravityVector(AngleVec.GetRotationToDegZ(Master->GetCurAngle()) * GetChargingSpeed());
	Renderer->ChangeAnimation("Hallelujah_Fly");
}

void Hallelujah::FlyUpdate(float _Delta)
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
		//ChangeState(HallelujahState::Idle);
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
			ChangeState(HallelujahState::Idle);
			return;
		}
	}

	if (GetLiveTime() >= 5.0f)
	{
		ChangeState(HallelujahState::Bomb);
		return;
	}

	// 물에 빠짐
	if (GetPos().Y >= 1875)
	{
		ChangeState(HallelujahState::InWater);
		return;
	}
}

void Hallelujah::PrevBombStart()
{
	SoundEffect = GameEngineSound::SoundPlay("HOLYGRENADE.WAV");
}

void Hallelujah::PrevBombUpdate(float _Delta)
{
	//DirCheck();
	GroundCheck(_Delta);

	if (GetLiveTime() >= 2.0f)
	{
		ChangeState(HallelujahState::Bomb);
		return;
	}
}


void Hallelujah::BombStart()
{
	HallelujahBomb = CreateBombEffect<Range100>();
	SoundEffect = GameEngineSound::SoundPlay("Explosion3.WAV");
	Renderer->Off();
}

void Hallelujah::BombUpdate(float _Delta)
{
	if (true == HallelujahBomb->GetRenderer()->IsAnimationEnd())
	{
		ChangeState(HallelujahState::Damage);
		return;
	}
}

void Hallelujah::DamageStart()
{

}

void Hallelujah::DamageUpdate(float _Delta)
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


void Hallelujah::InWaterStart()
{
	SoundEffect = GameEngineSound::SoundPlay("splish.WAV");
	SetGravityVector(float4::DOWN);
	IsWindOff();
	SetGravityPower(100.0f);
	DirCheck();
}

void Hallelujah::InWaterUpdate(float _Delta)
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


void Hallelujah::MaxStart()
{

}

void Hallelujah::MaxUpdate(float _Delta)
{
	ChangeState(HallelujahState::Ready);
	return;
}

void Hallelujah::ReadyStart()
{
	SetGravityVector(AngleVec.GetRotationToDegZ(Master->GetCurAngle()) * GetChargingSpeed());
}

void Hallelujah::ReadyUpdate(float _Delta)
{
	ChangeState(HallelujahState::Fly);
	return;
}

void Hallelujah::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

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
	}
}