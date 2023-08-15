#include "BackGroundEffect.h"
#include "ContentsEnum.h"
#include "Wind.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

BackGroundEffect::BackGroundEffect()
{
}

BackGroundEffect::~BackGroundEffect()
{
}

void BackGroundEffect::Start()
{

	GameEngineRenderer* Renderer = CreateRenderer(RenderOrder::BackGroundEffect);


	if (false == ResourcesManager::GetInst().IsLoadTexture("debris.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("debris.Bmp"), 1, 128);

	}
	
	Renderer->CreateAnimation("BackGroundEffect", "debris.Bmp", 0, 127, 0.01f, true);
	Renderer->ChangeAnimation("BackGroundEffect");


}

void BackGroundEffect::Update(float _Delta)
{

	float4 DownPos = float4::DOWN * 150.0f * _Delta;

	float4 Wind = Wind::GetWind()->GetWindVector();

	AddPos(DownPos);
}
