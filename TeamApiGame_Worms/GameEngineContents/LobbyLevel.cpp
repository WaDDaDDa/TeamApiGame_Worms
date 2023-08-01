#include "LobbyLevel.h"

#include <GameEngineCore/GameEngineActor.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "BackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#pragma region UI에서 사용할 헤더 & 함수 전방 선언
#include "UI_Mouse.h"
#include "UI_Lobby_SelectTitle.h"
#include "UI_Button.h"
#include "ContentsDefine.h"
#include "MouseObject.h"

void QuitGame(DWORD_PTR, DWORD_PTR);
#pragma endregion

LobbyLevel::LobbyLevel()
{
}

LobbyLevel::~LobbyLevel()
{
}

void LobbyLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<MouseObject>();
	CreateActor<UI_Mouse>();

	UI_Lobby_SelectTitle* SelectTitle = CreateActor<UI_Lobby_SelectTitle>();

	UI_Button* Btn_QuitGame = CreateActor<UI_Button>();
	Btn_QuitGame->InitButtonData("UI_Button_Quit", float4{ 250, 80 });
	Btn_QuitGame->SetPos({ 1000, 650 });
	Btn_QuitGame->SetClickedCallBack(QuitGame, 0, 0);


	//BackGround
	{
		BackGround* BackGroundPtr = CreateActor<BackGround>();
		BackGroundPtr->VerticalPatternInit("Lobby_Backdrop.bmp");

	}
}

void LobbyLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}

void LobbyLevel::Start()
{
}

void LobbyLevel::Update(float _Delta)
{
}

void LobbyLevel::Release()
{
}

#pragma region UI 함수 포인터 등록용 함수

void QuitGame(DWORD_PTR, DWORD_PTR)
{
	DestroyWindow(GameEngineWindow::MainWindow.GetHWND());
}

#pragma endregion