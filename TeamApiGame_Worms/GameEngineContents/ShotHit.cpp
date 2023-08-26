#include "ShotHit.h"
#include "Ground.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "PlayLevel.h"
#include "GameTurn.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

ShotHit::ShotHit()
{
}

ShotHit::~ShotHit()
{
}

void ShotHit::Start()
{
	Renderer = CreateRenderer(RenderOrder::Effect);

	if (false == ResourcesManager::GetInst().IsLoadTexture("shothit.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Effects\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("shothit.bmp"), 1, 10);
	}

	Renderer->SetTexture("Blank.bmp");

	SetShotHitRange({ 20.0f, 20.0f });

	Renderer->CreateAnimation("ShotHitEffect", "shothit.bmp", 0, 9, 0.05f, false);

	Renderer->ChangeAnimation("ShotHitEffect");

	
}

void ShotHit::LevelStart()
{

}

void ShotHit::Update(float _Delta)
{
	PlayLevel* CurPlayLevel = dynamic_cast<PlayLevel*>(GetLevel());
	CurPlayLevel->GetGround()->ContactGround(GetPos(), BombRange);

	if (Renderer->IsAnimationEnd())
	{
		Death();
		BombCollision->Off();
	}
}