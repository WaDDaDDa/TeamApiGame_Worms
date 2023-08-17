#include "FlyEffect.h"
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

FlyEffect::FlyEffect()
{

}

FlyEffect::~FlyEffect()
{

}

void FlyEffect::Start()
{
	Renderer = CreateRenderer(RenderOrder::BackGroundEffect);

	if (false == ResourcesManager::GetInst().IsLoadTexture("hexhaust.bmp"))
	{
		// 이펙트 로드
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Effects\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("hexhaust.bmp"), 1, 28);
	}


	Renderer->SetTexture("Blank.bmp");

	// 90도
	Renderer->CreateAnimation("FlyEffect", "hexhaust.bmp", 0, 27, 0.01f, false);

	Renderer->ChangeAnimation("FlyEffect");

}

void FlyEffect::LevelStart()
{
	
}

void FlyEffect::Update(float _Delta)
{
	if (Renderer->IsAnimationEnd())
	{
		Death();
	}
}

