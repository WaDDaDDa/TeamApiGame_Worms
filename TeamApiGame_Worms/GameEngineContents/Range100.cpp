#include "Range100.h"
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

Range100::Range100()
{

}

Range100::~Range100()
{

}

void Range100::Start()
{
	Renderer = CreateRenderer(RenderOrder::Effect);

	if (false == ResourcesManager::GetInst().IsLoadTexture("circle100.bmp"))
	{
		// ÀÌÆåÆ® ·Îµå
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Effects\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("circle100.bmp"), 1, 4);
	}


	Renderer->SetTexture("Blank.bmp");

	SetBombRange({ 100.0f,100.0f });

	Renderer->CreateAnimation("BombRange_100", "circle100.bmp", 0, 3, 0.05f, false);

	Renderer->ChangeAnimation("BombRange_100");

}

void Range100::LevelStart()
{

}

void Range100::Update(float _Delta)
{
	PlayLevel* CurPlayLevel = dynamic_cast<PlayLevel*>(GetLevel());
	CurPlayLevel->GetGround()->ContactGround(GetPos(), BombRange);

	if (Renderer->IsAnimationEnd())
	{
		Death();
	}
}

