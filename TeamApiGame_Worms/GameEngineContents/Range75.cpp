#include "Range75.h"
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

Range75::Range75()
{

}

Range75::~Range75()
{

}

void Range75::Start()
{
	Renderer = CreateRenderer(RenderOrder::Effect);

	if (false == ResourcesManager::GetInst().IsLoadTexture("circle75.bmp"))
	{
		// ÀÌÆåÆ® ·Îµå
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Effects\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("circle75.bmp"), 1, 4);
	}


	Renderer->SetTexture("Blank.bmp");

	SetBombRange({ 75.0f,75.0f });

	Renderer->CreateAnimation("BombRange_75", "circle75.bmp", 0, 3, 0.05f, false);

	Renderer->ChangeAnimation("BombRange_75");

}

void Range75::LevelStart()
{

}

void Range75::Update(float _Delta)
{
	PlayLevel* CurPlayLevel = dynamic_cast<PlayLevel*>(GetLevel());
	CurPlayLevel->GetGround()->ContactGround(GetPos(), BombRange);

	if (Renderer->IsAnimationEnd())
	{
		Death();
	}
}

