#include "FrontWave.h"
#include "ContentsEnum.h"

#include<GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

FrontWave::FrontWave()
{
}

FrontWave::~FrontWave()
{
}

void FrontWave::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("Water_sprite_surfice.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Water_sprite_surfice.bmp"), 1, 11);
	}
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("Water_sprite_surfice.bmp");

	Renderer1 = CreateRenderer();
	Renderer2 = CreateRenderer();

	Renderer1->CreateAnimation("FrontWave", "Water_sprite_surfice.Bmp", 0, 10, 0.05f, true);
	Renderer1->ChangeAnimation("FrontWave");

	Renderer2->CreateAnimation("FrontWave", "Water_sprite_surfice.Bmp", 0, 10, 0.05f, true);
	Renderer2->ChangeAnimation("FrontWave");

	Renderer2->SetRenderPos({ Texture->GetScale().X,0.0f });
	Renderer1->SetOrder(GetOrder());
	Renderer2->SetOrder(GetOrder());

}

void FrontWave::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('J'))
	{
		if (Renderer1->IsUpdate())
		{
			Renderer1->Off();
			Renderer2->Off();
		}
		else
		{
			Renderer1->On();
			Renderer2->On();
		}

	}

}
