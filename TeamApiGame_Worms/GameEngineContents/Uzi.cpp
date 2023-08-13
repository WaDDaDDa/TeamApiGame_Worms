#include "Uzi.h"
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

Uzi::Uzi()
{

}

Uzi::~Uzi()
{

}

void Uzi::Start()
{
	Renderer = CreateRenderer(RenderOrder::Weapon);

	if (false == ResourcesManager::GetInst().IsLoadTexture("uzicase.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("uzicase.bmp"), 1, 16);
	}

	
	{
		//Collision
		BodyCollision = CreateCollision(CollisionOrder::Weapon);
		BodyCollision->SetCollisionScale({ 10, 10 });
		BodyCollision->SetCollisionType(CollisionType::CirCle);
		//GrenadeCollision->SetCollisionPos({ 0, -10 });
		BodyCollision->Off();
	}

	Renderer->SetTexture("Blank.bmp");

	Renderer->CreateAnimation("Uzi_Fly", "uzicase.bmp", 0, 15, 0.05f, true);


	SetWeaponDamage(UziDamage);
	SetWeaponSpeed(UziSpeed);


	ChangeState(UziState::Max);
}

void Uzi::LevelStart()
{

}

void Uzi::Update(float _Delta)
{
	CameraFocus(_Delta);
	StateUpdate(_Delta);
}


void Uzi::StateUpdate(float _Delta)
{
	switch (State)
	{
	case UziState::Fly:
		return FlyUpdate(_Delta);
	case UziState::Bomb:
		return BombUpdate(_Delta);
	case UziState::Damage:
		return DamageUpdate(_Delta);
	case UziState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void Uzi::ChangeState(UziState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case UziState::Fly:
			FlyStart();
			break;
		case UziState::Bomb:
			BombStart();
			break;
		case UziState::Damage:
			DamageStart();
			break;
		case UziState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

void Uzi::CameraFocus(float _Delta)
{

}


void Uzi::DirCheck()
{
	Dir = GetGravityVector();
	float CurDir = Dir.AngleDeg();

	float CheckDir = CurDir / 11.25f;

	std::string Text = "";

	switch (static_cast<int>(CheckDir))
	{
	case 0:
		Renderer->ChangeAnimation("0_Uzi_Fly");
		break;
	case 1:
		Renderer->ChangeAnimation("1_Uzi_Fly");
		break;
	case 2:
		Renderer->ChangeAnimation("2_Uzi_Fly");
		break;
	case 3:
		Renderer->ChangeAnimation("3_Uzi_Fly");
		break;
	case 4:
		Renderer->ChangeAnimation("4_Uzi_Fly");
		break;
	case 5:
		Renderer->ChangeAnimation("5_Uzi_Fly");
		break;
	case 6:
		Renderer->ChangeAnimation("6_Uzi_Fly");
		break;
	case 7:
		Renderer->ChangeAnimation("7_Uzi_Fly");
		break;
	case 8:
		Renderer->ChangeAnimation("8_Uzi_Fly");
		break;
	case 9:
		Renderer->ChangeAnimation("9_Uzi_Fly");
		break;
	case 10:
		Renderer->ChangeAnimation("10_Uzi_Fly");
		break;
	case 11:
		Renderer->ChangeAnimation("11_Uzi_Fly");
		break;
	case 12:
		Renderer->ChangeAnimation("12_Uzi_Fly");
		break;
	case 13:
		Renderer->ChangeAnimation("13_Uzi_Fly");
		break;
	case 14:
		Renderer->ChangeAnimation("14_Uzi_Fly");
		break;
	case 15:
		Renderer->ChangeAnimation("15_Uzi_Fly");
		break;
	case 16:
		Renderer->ChangeAnimation("16_Uzi_Fly");
		break;
	case 17:
		Renderer->ChangeAnimation("17_Uzi_Fly");
		break;
	case 18:
		Renderer->ChangeAnimation("18_Uzi_Fly");
		break;
	case 19:
		Renderer->ChangeAnimation("19_Uzi_Fly");
		break;
	case 20:
		Renderer->ChangeAnimation("20_Uzi_Fly");
		break;
	case 21:
		Renderer->ChangeAnimation("21_Uzi_Fly");
		break;
	case 22:
		Renderer->ChangeAnimation("22_Uzi_Fly");
		break;
	case 23:
		Renderer->ChangeAnimation("23_Uzi_Fly");
		break;
	case 24:
		Renderer->ChangeAnimation("24_Uzi_Fly");
		break;
	case 25:
		Renderer->ChangeAnimation("25_Uzi_Fly");
		break;
	case 26:
		Renderer->ChangeAnimation("26_Uzi_Fly");
		break;
	case 27:
		Renderer->ChangeAnimation("27_Uzi_Fly");
		break;
	case 28:
		Renderer->ChangeAnimation("28_Uzi_Fly");
		break;
	case 29:
		Renderer->ChangeAnimation("29_Uzi_Fly");
		break;
	case 30:
		Renderer->ChangeAnimation("30_Uzi_Fly");
		break;
	case 31:
		Renderer->ChangeAnimation("31_Uzi_Fly");
		break;
	default:
		break;
	}
}

void Uzi::FlyStart()
{
	Renderer->ChangeAnimation("0_Uzi_Fly");
}

void Uzi::FlyUpdate(float _Delta)
{
	float4 FireDir = AngleVec.GetRotationToDegZ(Master->GetCurAngle());

	AddPos(FireDir * UziSpeed * _Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (Color != RGB(255, 255, 255) || GetLiveTime() >= 0.2f)
	{
		ChangeState(UziState::Bomb);
		return;

	}

	if (GetLiveTime() >= 0.02f)
	{
		BodyCollision->On();
	}

	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollision->Collision(CollisionOrder::PlayerBody, _Col
		, CollisionType::Rect
		, CollisionType::CirCle
	))
	{
		ChangeState(UziState::Bomb);
		return;
	}

}

void Uzi::BombStart()
{
	UziBomb = CreateBombEffect<Range25>();
	Renderer->Off();
}

void Uzi::BombUpdate(float _Delta)
{
	if (true == UziBomb->GetRenderer()->IsAnimationEnd())
	{
		ChangeState(UziState::Damage);
		return;
	}
}

void Uzi::DamageStart()
{

}

void Uzi::DamageUpdate(float _Delta)
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

void Uzi::MaxStart()
{

}

void Uzi::MaxUpdate(float _Delta)
{
	ChangeState(UziState::Fly);
	return;
}