#include "SuperSheepEffect.h"
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

SuperSheepEffect::SuperSheepEffect()
{

}

SuperSheepEffect::~SuperSheepEffect()
{

}

void SuperSheepEffect::Start()
{
	Renderer = CreateRenderer(RenderOrder::BackGroundEffect);

	if (false == ResourcesManager::GetInst().IsLoadTexture("kamismk.bmp"))
	{
		// 이펙트 로드
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Effects\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("kamismk.bmp"), 1, 10);
	}


	Renderer->SetTexture("Blank.bmp");

	// 90도
	Renderer->CreateAnimation("SuperSheepEffect", "kamismk.bmp", 0, 9, 0.1f, false);

	Renderer->ChangeAnimation("SuperSheepEffect");

}

void SuperSheepEffect::LevelStart()
{
	
}

void SuperSheepEffect::Update(float _Delta)
{
	if (Renderer->IsAnimationEnd())
	{
		Death();
	}
}

