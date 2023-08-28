#include "ContentCore.h"

#include "TitleLevel.h"
#include "ModeSelectLevel.h"
#include "LobbyLevel.h"
#include "PlayLevel.h"

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
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");

	// �� ������ ȭ�鿡 ������.
	GameEngineCore::ChangeLevel("ModeSelectLevel");
}

// �ൿ�Ѱ�.
void ContentCore::Update(float _Delta)
{
}

// �׷�����.
void ContentCore::Render(float _Delta)
{
}

// �����ȴ�.
void ContentCore::Release() 
{
}