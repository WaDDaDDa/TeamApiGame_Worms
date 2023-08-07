#include "UI_Box_Terrain.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"

UI_Box_Terrain::UI_Box_Terrain()
{
}

UI_Box_Terrain::~UI_Box_Terrain()
{
}

void UI_Box_Terrain::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Terrain.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\Lobby\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Terrain.bmp"));
	}

	MainRenderer = CreateRenderer(RenderOrder::UI);

	MainRenderer->SetRenderScale({ 530, 250 });

	MainRenderer->SetTexture("UI_Terrain.bmp");
}

void UI_Box_Terrain::Update(float _Delta)
{
}
