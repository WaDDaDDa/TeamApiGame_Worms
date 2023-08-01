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
	Renderer->CreateAnimation("Bazooka_Fly", "bullet.bmp", 0, 15, 0.05f, false);

	SetDir(Player::DirPos);

	//GravityDir = float4::UP;
	GravityDir += Dir * 40.0f;
	SetGravityVector(GravityDir * 10.0f);
	ChangeState(BazookaState::Fly);

}

void Bazooka::Update(float _Delta)
{
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

	// 1초뒤 데스
	if (2.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Death();
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
