#include "UI_Box_SchemeOption.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"

UI_Box_SchemeOption::UI_Box_SchemeOption()
{
}

UI_Box_SchemeOption::~UI_Box_SchemeOption()
{
}

void UI_Box_SchemeOption::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_SchemeOption.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\Lobby\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_SchemeOption.bmp"));
	}

	MainRenderer = CreateRenderer(RenderOrder::UI);

	MainRenderer->SetRenderScale({ 530, 250 });

	MainRenderer->SetTexture("UI_SchemeOption.bmp");
}

void UI_Box_SchemeOption::Update(float _Delta)
{
}
