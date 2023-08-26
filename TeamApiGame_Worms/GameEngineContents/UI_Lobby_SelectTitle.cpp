#include "UI_Lobby_SelectTitle.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"


UI_Lobby_SelectTitle* UI_Lobby_SelectTitle::LobbyTitleUI = nullptr;
UI_Lobby_SelectTitle::UI_Lobby_SelectTitle()
{
	LobbyTitleUI = this;
}

UI_Lobby_SelectTitle::~UI_Lobby_SelectTitle()
{
}

void UI_Lobby_SelectTitle::Start()
{
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("UI_MenuSel_Title.bmp");

	if (false == IsResource)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\Lobby\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_MenuSel_Title.bmp"));
	}

	// ·»´õ·¯ ¼³Á¤
	MainRenderer = CreateUIRenderer("UI_MenuSel_Title.bmp", RenderOrder::UI);
	MainRenderer->SetRenderScale({ 640, 200 });
	MainRenderer->SetRenderPos({ 640, 100 });

	MainTextRenderer = CreateUIRenderer(RenderOrder::UI);
	MainTextRenderer->SetText(" ", 28, RGB(0, 255, 255));
	MainTextRenderer->SetRenderPos({ 200, 650 });

}

void UI_Lobby_SelectTitle::Update(float _Delta)
{
}
