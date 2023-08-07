#include "UI_Box_Teams.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"

UI_Box_Teams::UI_Box_Teams()
{
}

UI_Box_Teams::~UI_Box_Teams()
{
}

void UI_Box_Teams::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Teams.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\Lobby\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Teams.bmp"));
	}

	MainRenderer = CreateRenderer(RenderOrder::UI);

	MainRenderer->SetRenderScale({ 530, 250 });

	MainRenderer->SetTexture("UI_Teams.bmp");


}

void UI_Box_Teams::Update(float _Delta)
{
}
