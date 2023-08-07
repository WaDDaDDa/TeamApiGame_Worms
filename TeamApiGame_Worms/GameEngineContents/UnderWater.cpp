#include "UnderWater.h"
#include "PlayLevel.h"
#include "Ground.h"

#include"ContentsDefine.h"
#include"ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include<GameEnginePlatform/GameEngineWindowTexture.h>
#include<GameEngineCore/GameEngineRenderer.h>
#include<GameEngineCore/GameEngineLevel.h>

#define UNDER_WATER_COPY_POS_START float4{0.0f,1865.0f }
#define UNDER_WATER_COPY_POS_END PLAY_BACKGROUND_SCALE


UnderWater::UnderWater()
{
}

UnderWater::~UnderWater()
{
}

void UnderWater::DrawAtStage(GameEngineLevel* _Level)
{
	Ground* Stage = dynamic_cast<PlayLevel*>(_Level)->GetGround();


	float4 RenderScale = UNDER_WATER_COPY_POS_END - UNDER_WATER_COPY_POS_START;
	float4 RenderPos = { UNDER_WATER_COPY_POS_END.hX(),(UNDER_WATER_COPY_POS_END.Y + UNDER_WATER_COPY_POS_START.Y) / 2};
	float checkx = RenderPos.X - RenderScale.hX();

	float checky = RenderPos.Y - RenderScale.hY();


	Stage->GetPixelGroundTexture()->TransCopy(Texture, RenderPos, RenderScale, float4::ZERO, Texture->GetScale(), NULL);
	 
	Renderer->SetRenderScale(RenderScale);
	Renderer->SetRenderPos(RenderPos);
}


void UnderWater::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Under_Water.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Under_Water.bmp"));
	}
	 Texture = ResourcesManager::GetInst().FindTexture("Under_Water.Bmp");
	
	 Renderer = CreateRenderer(RenderOrder::BackWave);
	 Renderer->SetTexture("Under_Water.Bmp");
	
}

void UnderWater::Update(float _Delta)
{
}
