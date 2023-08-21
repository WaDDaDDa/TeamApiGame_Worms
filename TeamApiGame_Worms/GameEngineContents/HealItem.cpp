#include "HealItem.h"


#include "GameTurn.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEnginecollision.h>

HealItem::HealItem()
{

}

HealItem::~HealItem()
{

}

void HealItem::Start()
{
	Renderer = CreateRenderer(RenderOrder::Item);

	if (false == ResourcesManager::GetInst().IsLoadTexture("mcrate0.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Misc\\Item\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("mcrate0.bmp"), 1, 61);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("mcrate1.bmp"), 1, 12);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("mcrate2.bmp"), 1, 20);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("mcratev.bmp"), 1, 12);
	}
	Renderer->SetTexture("Blank.bmp");
	Renderer->SetRenderPos({ 0,-8.0f });
	Renderer->CreateAnimation("HealItem_Create", "mcrate0.bmp", 60, 0, 0.05f, false);
	Renderer->CreateAnimation("HealItem_Idle", "mcrate1.bmp", 0, 11, 0.1f, true);
	Renderer->CreateAnimation("HealItem_Fly", "mcrate2.bmp", 0, 19, 0.1f, false);
	Renderer->CreateAnimation("HealItem_RFly", "mcrate2.bmp", 19, 0, 0.1f, false);
	Renderer->CreateAnimation("HealItem_Col", "mcratev.bmp", 0, 11, 0.05f, false);

	{
		//Collision
		BodyCollision = CreateCollision(CollisionOrder::Item);

		BodyCollision->SetCollisionScale({ 30, 30 });
		BodyCollision->SetCollisionType(CollisionType::CirCle);
		BodyCollision->SetCollisionPos({ 0,-8.0f });
	}

	ChangeState(HealItemState::Create);
}

void HealItem::LevelStart()
{

}

void HealItem::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void HealItem::StateUpdate(float _Delta)
{
	switch (State)
	{
	case HealItemState::Create:
		CreateUpdate(_Delta);
		break;
	case HealItemState::Idle:
		IdleUpdate(_Delta);
		break;
	case HealItemState::Fly:
		FlyUpdate(_Delta);
		break;
	case HealItemState::Col:
		ColUpdate(_Delta);
		break;
	case HealItemState::Max:
		MaxUpdate(_Delta);
		break;
	default:
		break;
	}
}

void HealItem::ChangeState(HealItemState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case HealItemState::Create:
			CreateStart();
			break;
		case HealItemState::Idle:
			IdleStart();
			break;
		case HealItemState::Fly:
			FlyStart();
			break;
		case HealItemState::Col:
			ColStart();
			break;
		case HealItemState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}

void HealItem::CreateStart()
{
	Renderer->ChangeAnimation("HealItem_Create");
	GameTurn::MainGameTurn->TurnPlayerAllOff();

	IsTurnPlayer = true;
}

void HealItem::CreateUpdate(float _Delta)
{
	CameraFocus(_Delta);
	GroundCheck(_Delta);
	if (true == Renderer->IsAnimationEnd())
	{
		ChangeState(HealItemState::Idle);
		return;
	}
}

void HealItem::FlyStart()
{
	Renderer->ChangeAnimation("HealItem_Fly");
	IsWindOn();
	SetGravityPower(20.0f);
}

void HealItem::FlyUpdate(float _Delta)
{
	Gravity(_Delta);
	if (Renderer->IsAnimationEnd())
	{
		AniSwitch = !AniSwitch;
		if (true == AniSwitch)
		{
			Renderer->ChangeAnimation("HealItem_Fly");
		}
		else if (false == AniSwitch)
		{
			Renderer->ChangeAnimation("HealItem_RFly");
		}
	}
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (Color != RGB(255, 255, 255))
	{
		ChangeState(HealItemState::Idle);
		return;
	}
}

void HealItem::IdleStart()
{
	IsTurnPlayer = false;

	IsWindOff();
	GravityReset();
	Renderer->ChangeAnimation("HealItem_Idle");
	GameTurn::MainGameTurn->StartTurnPlayer();
}

void HealItem::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);
}

void HealItem::ColStart()
{

}

void HealItem::ColUpdate(float _Delta)
{

}

void HealItem::MaxStart()
{

}

void HealItem::MaxUpdate(float _Delta)
{

}
