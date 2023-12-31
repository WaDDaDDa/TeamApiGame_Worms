#include "ContentCore.h"

#include "TitleLevel.h"
#include "ModeSelectLevel.h"
#include "LobbyLevel.h"
#include "LoadingLevel.h"
#include "PlayLevel.h"
#include "EndingLevel.h"

#include <GameEnginePlatform/GameEngineWindow.h>

ContentCore::ContentCore() 
{
}

ContentCore::~ContentCore() 
{
}

void ContentCore::Start() 
{
	GameEngineWindow::MainWindow.SetPosAndScale({50, 50}, { 1280, 720 });

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<ModeSelectLevel>("ModeSelectLevel");
	GameEngineCore::CreateLevel<LobbyLevel>("LobbyLevel");
	GameEngineCore::CreateLevel<LoadingLevel>("LoadingLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");


	// 이 레벨이 화면에 보여라.
	GameEngineCore::ChangeLevel("TitleLevel");
}

// 행동한고.
void ContentCore::Update(float _Delta)
{
}

// 그려지고.
void ContentCore::Render(float _Delta)
{
}

// 정리된다.
void ContentCore::Release() 
{
}