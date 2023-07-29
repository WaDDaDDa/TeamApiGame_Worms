#include "UI_IntroLogo.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "ContentsEnum.h"

UI_IntroLogo::UI_IntroLogo()
{
}

UI_IntroLogo::~UI_IntroLogo()
{
}

void UI_IntroLogo::Start()
{
	// 마우스 리소스 로딩
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("UI_Intro_Logo1.bmp");

	if (false == IsResource)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\Title\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Intro_Logo1.bmp"));
	}

	// 렌더러 설정
	MainRenderer = CreateUIRenderer("UI_Intro_Logo1.bmp", RenderOrder::UI);
	MainRenderer->SetRenderScale({ GameEngineWindow::MainWindow.GetScale().X, GameEngineWindow::MainWindow.GetScale().Y});

	MainRenderer->SetAlpha(255);
	
}

void UI_IntroLogo::Update(float _Delta)
{
	//FadeSpeed += 0.5f * _Delta;
	//CurAlpha -= static_cast<int>(FadeSpeed * _Delta);


	//if (0 >= CurAlpha)
	//{
	//	CurAlpha = 0;
	//}

//	MainRenderer->SetAlpha(CurAlpha);

}