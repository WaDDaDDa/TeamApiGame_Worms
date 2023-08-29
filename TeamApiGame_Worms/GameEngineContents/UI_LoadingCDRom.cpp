#include "UI_LoadingCDRom.h"
#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>

UI_LoadingCDRom::UI_LoadingCDRom()
{
}

UI_LoadingCDRom::~UI_LoadingCDRom()
{
}

void UI_LoadingCDRom::Start()
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_cdrom.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("UI_cdrom.bmp"), 1, 25);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_FADE.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_FADE.bmp"));
	}

	MainRenderer = CreateRenderer(RenderOrder::BackGround);
	MainRenderer->SetTexture("UI_FADE.bmp");
	MainRenderer->SetRenderScale({ 1400, 1400 });
	MainRenderer->SetRenderPos({ 700, 400 });

	CDRomRenderer = CreateRenderer(RenderOrder::BackGroundEffect);
	CDRomRenderer->SetRenderPos({ 640, 360 });
	CDRomRenderer->SetRenderScale({ 128, 128 });
	CDRomRenderer->CreateAnimation("CDFill", "UI_cdrom.bmp", 0, 24, 0.02f, false);
	CDRomRenderer->ChangeAnimation("CDFill");
}

void UI_LoadingCDRom::Update(float _Delta)
{
	if (true == CDRomRenderer->IsAnimationEnd())
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}
