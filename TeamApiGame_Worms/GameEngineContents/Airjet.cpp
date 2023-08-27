#include "Airjet.h"
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

Airjet::Airjet()
{

}

Airjet::~Airjet()
{

}

void Airjet::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("airjetbLeft.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("airjetbLeft.bmp"), 1, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("airjetbRight.bmp"), 1, 1);

	}

	{
		Renderer = CreateRenderer(RenderOrder::Effect);
		Renderer->CreateAnimation("airjetbLeft", "airjetbLeft.bmp", 0, 0, 0.1f, false);
		Renderer->CreateAnimation("airjetbRight", "airjetbRight.bmp", 0, 0, 0.1f, false);

		Renderer->ChangeAnimation("airjetbRight");
	}
}


void Airjet::LevelStart()
{

}

void Airjet::Update(float _Delta)
{
	if (PlayerDir::Left == Master->GetPlayerDir())
	{
		AddPos(float4::LEFT * 2000.0f * _Delta);

	}
	else if (PlayerDir::Right == Master->GetPlayerDir())
	{
		AddPos(float4::RIGHT * 2000.0f * _Delta);
	}

	if (GetLiveTime() >= 6.0f)
	{
		Death();
	}
}

