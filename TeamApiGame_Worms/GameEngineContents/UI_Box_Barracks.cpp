#include "UI_Box_Barracks.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"

UI_Box_Barracks::UI_Box_Barracks()
{
}

UI_Box_Barracks::~UI_Box_Barracks()
{
}

void UI_Box_Barracks::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Barracks.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\Lobby\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Barracks.bmp"));
	}

	MainRenderer = CreateRenderer(RenderOrder::UI);

	MainRenderer->SetRenderScale({ 530, 250 });

	MainRenderer->SetTexture("UI_Barracks.bmp");


}

void UI_Box_Barracks::Update(float _Delta)
{
}
