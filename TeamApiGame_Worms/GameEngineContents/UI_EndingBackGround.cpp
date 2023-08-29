#include "UI_EndingBackGround.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"

UI_EndingBackGround::UI_EndingBackGround()
{
}

UI_EndingBackGround::~UI_EndingBackGround()
{
}

void UI_EndingBackGround::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_EndingBackGround.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_EndingBackGround.bmp"));
	}

	MainRenderer = CreateRenderer("UI_EndingBackGround.bmp", RenderOrder::BackGround);

	MainRenderer->SetRenderScale({ 1280, 720 });
	MainRenderer->SetRenderPos({ 640, 360 });

}