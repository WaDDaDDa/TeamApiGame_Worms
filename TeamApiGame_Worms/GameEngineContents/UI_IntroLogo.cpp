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
	MainRenderer = CreateUIRenderer(RenderOrder::UI);
	MainRenderer->SetRenderScale({ GameEngineWindow::MainWindow.GetScale().X, GameEngineWindow::MainWindow.GetScale().Y });

	// 府家胶 肺爹
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\Title\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Intro_Logo1.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("UI_Intro_Logo1.bmp"), 1, 1);	
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_DefaultBackGround.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("UI_DefaultBackGround.bmp"), 1, 1);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_MainTitle_Backdrop.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("UI_MainTitle_Backdrop.bmp"), 1, 1);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_MainTitle.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("UI_MainTitle.bmp"), 1, 1);
	}

	// 局聪皋捞记 积己
	MainRenderer->CreateAnimation("TITLE_INTRO_LOGO", "UI_Intro_Logo1.bmp", 0, 0, 5.0f, true);
	MainRenderer->CreateAnimation("TITLE_BLACK", "UI_DefaultBackGround.bmp", 0, 0, 5.0f, true);
	MainRenderer->CreateAnimation("TITLE_MAIN_BACK", "UI_MainTitle_Backdrop.bmp", 0, 0, 5.0f, true);
	MainRenderer->CreateAnimation("TITLE_MAIN", "UI_MainTitle.bmp", 0, 0, 5.0f, true);

	MainRenderer->ChangeAnimation("TITLE_INTRO_LOGO");
}

void UI_IntroLogo::Update(float _Delta)
{

}


void UI_IntroLogo::ChangeState_Black()
{
	MainRenderer->ChangeAnimation("TITLE_BLACK");
}

void UI_IntroLogo::ChangeState_Main_Back()
{
	MainRenderer->ChangeAnimation("TITLE_MAIN_BACK");
}

void UI_IntroLogo::ChangeState_Main()
{
	MainRenderer->ChangeAnimation("TITLE_MAIN");
}