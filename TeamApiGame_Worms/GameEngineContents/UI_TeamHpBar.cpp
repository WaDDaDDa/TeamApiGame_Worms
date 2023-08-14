#include "UI_TeamHpBar.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"

UI_TeamHpBar::UI_TeamHpBar()
{
}

UI_TeamHpBar::~UI_TeamHpBar()
{
}

void UI_TeamHpBar::Start()
{
#pragma region 리소스 로딩
#pragma region 플레이어 이름 리소스 로딩

	// 리소스 로딩
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\PlayerInfoUI\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomNameTagR.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomNameTagR.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomNameTagB.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomNameTagB.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomNameTagG.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomNameTagG.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomNameTagY.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomNameTagY.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomNameTagP.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomNameTagP.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomNameTagS.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomNameTagS.bmp"));
	}

#pragma endregion

#pragma region Hp바 & 국기 리소스 로딩

	// HP바
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomHPbarB.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomHPbarB.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomHPbarG.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomHPbarG.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomHPbarP.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomHPbarP.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomHPbarR.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomHPbarR.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomHPbarS.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomHPbarS.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomHPbarY.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomHPbarY.bmp"));
	}

	// 국기 리소스
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomFlagKOR.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomFlagKOR.bmp"));
	}

#pragma endregion
#pragma endregion
	
	TeamFlagRenderer = CreateUIRenderer("UI_BottomFlagKOR.bmp", RenderOrder::UI);
	TeamFlagRenderer->SetRenderScale({ 20, 17 });

	TeamNameRenderer = CreateUIRenderer("UI_BottomNameTagB.bmp", RenderOrder::UI);
	TeamNameRenderer->SetRenderScale({ 38, 17 });
	TeamNameRenderer->SetRenderPos({ -30, 0});

	TeamHpRenderer = CreateUIRenderer("UI_BottomHPbarB.bmp", RenderOrder::UI);
	TeamHpRenderer->SetRenderScale({ 100, 17 });
	TeamHpRenderer->SetRenderPos({ 61, 0 });
}

void UI_TeamHpBar::Update(float _Delta)
{
}
