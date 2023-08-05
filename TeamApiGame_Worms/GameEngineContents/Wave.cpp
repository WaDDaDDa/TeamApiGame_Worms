#include "Wave.h"
#include "ContentsEnum.h"

#include<GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

Wave::Wave()
{
}

Wave::~Wave()
{
}

void Wave::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("Water_sprite.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Water_sprite.bmp"), 1, 11);
	}
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("Water_sprite.bmp");

	GameEngineRenderer* Renderer1 = CreateRenderer();
	GameEngineRenderer* Renderer2 = CreateRenderer();
	
	Renderer1->CreateAnimation("Wave", "Water_sprite.Bmp", 0, 10, 0.05f, true);
	Renderer1->ChangeAnimation("Wave");
	
	Renderer2->CreateAnimation("Wave", "Water_sprite.Bmp", 0, 10, 0.05f, true);
	Renderer2->ChangeAnimation("Wave");

	Renderer2->SetRenderPos({ Texture->GetScale().X,0.0f });
}

void Wave::Update(float _Delta)
{
}
