#include "Cloud.h"
#include "Wind.h"
#include "ContentsEnum.h"
#include "ContentsDefine.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/ResourcesManager.h>



Cloud::Cloud()
{
}

Cloud::~Cloud()
{
}

void Cloud::Start()
{
	int CloudTypeRand = GameEngineRandom::MainRandom.RandomInt(0, 2);

	GameEngineRenderer* Renderer = CreateRenderer(RenderOrder::BackGroundEffect);

	switch (CloudTypeRand)
	{
	case 0:
		if (false == ResourcesManager::GetInst().IsLoadTexture("clouds.Bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			GameEnginePath FolderPath = FilePath;

			FilePath.MoveChild("ContentsResources\\Texture\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("clouds.Bmp"), 1, 20);

		}
		Type = CloudType::Small;

		

		Renderer->SetSprite("clouds.Bmp");
		Renderer->CreateAnimation("CloudMove", "clouds.Bmp", 0, 19, 0.05f, true);

		break;
	case 1:
		if (false == ResourcesManager::GetInst().IsLoadTexture("cloudm.Bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			GameEnginePath FolderPath = FilePath;

			FilePath.MoveChild("ContentsResources\\Texture\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("cloudm.Bmp"), 1, 20);


		}
		Type = CloudType::Middle;

		Renderer->SetSprite("cloudm.Bmp");
		Renderer->CreateAnimation("CloudMove", "cloudm.Bmp", 0, 19, 0.05f, true);
		



		break;

	case 2:
		if (false == ResourcesManager::GetInst().IsLoadTexture("cloudl.Bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			GameEnginePath FolderPath = FilePath;

			FilePath.MoveChild("ContentsResources\\Texture\\");

			ResourcesManager::GetInst().CreateSpriteSheet( FilePath.PlusFilePath("cloudl.Bmp"), 1, 20);

		}
		
		Type = CloudType::Large;

		Renderer->SetSprite("cloudl.Bmp");
		Renderer->CreateAnimation("CloudMove", "cloudl.Bmp", 0, 19, 0.05f, true);
		break;

		
	default:
		break;
	}
	
	Renderer->ChangeAnimation("CloudMove");
	
	
	Dir = Wind::GetWind()->GetWindDir();
	if (float4::ZERO == Dir)
	{
		int DirRand	= GameEngineRandom::MainRandom.RandomInt(0,1);

		if (0 == DirRand)
		{
			Dir = float4::LEFT;
		}
		else
		{
			Dir = float4::RIGHT;
		}

	}


	float YRandom = GameEngineRandom::MainRandom.RandomFloat(PLAY_GROUND_SCALE.hY() - 30.0f, PLAY_GROUND_SCALE.hY() + 30.0f);

	if (float4::LEFT == Dir)
	{
		SetPos({ BACKGROUND_SCALE.X+20.0f,YRandom });
	}
	else if (float4::RIGHT == Dir)
	{
		SetPos({ -20.0f,YRandom });

	}

	Speed = GameEngineRandom::MainRandom.RandomFloat(80.0f, 120.0f);

}

void Cloud::Update(float _Delta)
{
	if (GetPos().X <= (-40.0f) || GetPos().X >= BACKGROUND_SCALE.X + 40.0f)
	{
		Death();
	}
	
	float4 WindVector = { Wind::GetWind()->GetWindVector().X/5.0f,0.0f };

	AddPos((Dir*Speed *_Delta)+WindVector);

}
