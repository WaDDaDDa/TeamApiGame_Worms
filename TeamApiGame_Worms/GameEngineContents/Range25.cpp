#include "Range25.h"
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

Range25::Range25()
{

}

Range25::~Range25()
{

}

void Range25::Start()
{
	Renderer = CreateRenderer(RenderOrder::Effect);

	if (false == ResourcesManager::GetInst().IsLoadTexture("circle25.bmp"))
	{
		// 이펙트 로드
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Effects\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("circle25.bmp"), 1, 8);
	}


	Renderer->SetTexture("Blank.bmp");

	SetBombRange({ 50.0f,50.0f });

	// 90도
	Renderer->CreateAnimation("BombRange_25", "circle25.bmp", 0, 7, 0.05f, false);

	Renderer->ChangeAnimation("BombRange_25");

}

void Range25::LevelStart()
{

}

void Range25::Update(float _Delta)
{
	PlayLevel* CurPlayLevel = dynamic_cast<PlayLevel*>(GetLevel());
	CurPlayLevel->GetGround()->ContactGround(GetPos(), BombRange);

	if (Renderer->IsAnimationEnd())
	{
		Death();
	}
}

