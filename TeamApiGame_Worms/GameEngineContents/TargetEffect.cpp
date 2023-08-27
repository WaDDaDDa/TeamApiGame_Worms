#include "TargetEffect.h"
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

TargetEffect::TargetEffect()
{

}

TargetEffect::~TargetEffect()
{

}

void TargetEffect::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("markerr.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("markerr.bmp"), 1, 10);

	}

	{
		Renderer = CreateRenderer(RenderOrder::Effect);
		Renderer->CreateAnimation("TargetMarkR", "markerr.bmp", 0, 9, 0.1f, true);
		Renderer->ChangeAnimation("TargetMarkR");
	}
}


void TargetEffect::LevelStart()
{

}

void TargetEffect::Update(float _Delta)
{
	if (false == Master->IsTurnPlayer)
	{
		Death();
	}
}

