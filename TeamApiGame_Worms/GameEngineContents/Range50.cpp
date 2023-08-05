#include "Range50.h"
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

Range50::Range50()
{

}

Range50::~Range50()
{

}

void Range50::Start()
{
	Renderer = CreateRenderer(RenderOrder::Effect);

	if (false == ResourcesManager::GetInst().IsLoadTexture("circle50.bmp"))
	{
		// ÀÌÆåÆ® ·Îµå
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Effects\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("circle50.bmp"), 1, 8);
	}


	Renderer->SetTexture("Blank.bmp");

	SetBombRange({ 100.0f,100.0f });

	Renderer->CreateAnimation("BombRange_50", "circle50.bmp", 0, 7, 0.05f, false);

	Renderer->ChangeAnimation("BombRange_50");

}

void Range50::LevelStart()
{

}

void Range50::Update(float _Delta)
{
	PlayLevel* CurPlayLevel = dynamic_cast<PlayLevel*>(GetLevel());
	CurPlayLevel->GetGround()->ContactGround(GetPos(), BombRange);

	if (Renderer->IsAnimationEnd())
	{
		Death();
	}
}

