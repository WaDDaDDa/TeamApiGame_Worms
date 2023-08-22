#include "FlameEffect.h"
#include "Ground.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "PlayLevel.h"
#include "GameTurn.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEnginecollision.h>

FlameEffect::FlameEffect()
{

}

FlameEffect::~FlameEffect()
{

}

void FlameEffect::Start()
{
	Renderer = CreateRenderer(RenderOrder::BackGroundEffect);

	if (false == ResourcesManager::GetInst().IsLoadTexture("flame1.bmp"))
	{
		// 이펙트 로드
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Effects\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("flame1.bmp"), 1, 32);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("exhaust.bmp"), 1, 30);
	}

	SetBombRange({ 5.0f,5.0f });

	Renderer->SetTexture("Blank.bmp");

	// 90도
	Renderer->CreateAnimation("FlameEffect", "flame1.bmp", 0, 31, 0.2f, false);
	Renderer->CreateAnimation("FlameFireEffect", "exhaust.bmp", 0, 29, 0.1f, false);

	//Renderer->ChangeAnimation("FlameEffect");

	ChangeState(FlameEffectState::Max);
	IsWindOn();

}

void FlameEffect::LevelStart()
{

}


void FlameEffect::StateUpdate(float _Delta)
{
	switch (State)
	{
	case FlameEffectState::Fly:
		return FlyUpdate(_Delta);
	case FlameEffectState::Fire:
		return FireUpdate(_Delta);
	case FlameEffectState::Max:
		return MaxUpdate(_Delta);
	default:
		break;
	}
}

void FlameEffect::ChangeState(FlameEffectState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case FlameEffectState::Fly:
			FlyStart();
			break;
		case FlameEffectState::Fire:
			FireStart();
			break;
		case FlameEffectState::Max:
			MaxStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}


void FlameEffect::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void FlameEffect::FlyStart()
{
	SetDamage(5.0f);

	Renderer->ChangeAnimation("FlameEffect");
}

void FlameEffect::FlyUpdate(float _Delta)
{
	Gravity(_Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (Color != RGB(255, 255, 255) || Renderer->IsAnimationEnd())
	{
		ChangeState(FlameEffectState::Fire);
		return;
	}
}

void FlameEffect::FireStart()
{
	Renderer->ChangeAnimation("FlameFireEffect");
}

void FlameEffect::FireUpdate(float _Delta)
{
	GroundCheck(_Delta);
	static float FireTick = 0.0f;
	FireTick += _Delta;
	if (FireTick >= 1.2f)
	{
		PlayLevel* CurPlayLevel = dynamic_cast<PlayLevel*>(GetLevel());
		CurPlayLevel->GetGround()->ContactGround(GetPos(), BombRange);
		FireTick = 0.0f;
	}

	if (Renderer->IsAnimationEnd())
	{
		Death();
	}
}

void FlameEffect::MaxStart()
{

}

void FlameEffect::MaxUpdate(float _Delta)
{
	ChangeState(FlameEffectState::Fly);
	return;
}
