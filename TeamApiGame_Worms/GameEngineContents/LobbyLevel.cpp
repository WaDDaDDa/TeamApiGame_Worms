#include "LobbyLevel.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>


#include "BackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#pragma region UI에서 사용할 헤더 & 함수 전방 선언
#include "UI_Mouse.h"
#include "UI_Button.h"
#include "UI_Meteor.h"
#include "UI_Box_Barracks.h"
#include "UI_Box_Teams.h"
#include "UI_Box_Terrain.h"
#include "UI_Box_SchemeOption.h"

#include "ContentsDefine.h"
#include "MouseObject.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineRandom.h>


void ExitLobby(DWORD_PTR, DWORD_PTR);
void StartGame(DWORD_PTR, DWORD_PTR);
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


	// 레이아웃 세팅

	UI_Box_Terrain* Box_Terrain = CreateActor<UI_Box_Terrain>();
	Box_Terrain->SetPos({ 350, 140 });

	UI_Box_Teams* Box_Teams = CreateActor<UI_Box_Teams>();
	Box_Teams->SetPos({ 950, 140 });

	UI_Box_SchemeOption* Box_SchemeOption = CreateActor<UI_Box_SchemeOption>();
	Box_SchemeOption->SetPos({ 350, 400 });

	UI_Box_Barracks* Box_Barracks = CreateActor<UI_Box_Barracks>();
	Box_Barracks->SetPos({ 950, 395 });

	// Button 세팅
	UI_Button* Btn_StartGame = CreateActor<UI_Button>();
	Btn_StartGame->InitButtonData("UI_Button_StartGame", float4{ 400, 80 }, true);
	Btn_StartGame->SetPos({ 1065, 570 });
	Btn_StartGame->SetClickedCallBack(StartGame, 0, 0);

	UI_Button* Btn_ExitGame = CreateActor<UI_Button>();
	Btn_ExitGame->InitButtonData("UI_Button_Exit", float4{ 250, 60 }, true);
	Btn_ExitGame->SetPos({ 1140, 670 });
	Btn_ExitGame->SetClickedCallBack(ExitLobby, 0, 0);


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

	// 유성우 효과 적용
	float MeteorPosX = GameEngineRandom::MainRandom.RandomFloat(-800, 1400);
	float MeteorPosY = GameEngineRandom::MainRandom.RandomFloat(-400, 0);

	MeteorCreateTimer += _Delta;

	if (MeteorCreateTimer > 0.2f)
	{
		UI_Meteor* Meteor = CreateActor<UI_Meteor>();
		Meteor->SetPos({ MeteorPosX, MeteorPosY });
		MeteorCreateTimer = 0.0f;
	}

}

void LobbyLevel::Release()
{
}

#pragma region UI 함수 포인터 등록용 함수

void StartGame(DWORD_PTR, DWORD_PTR)
{
	GameEngineCore::ChangeLevel("PlayLevel");
}

void ExitLobby(DWORD_PTR, DWORD_PTR)
{
	GameEngineCore::ChangeLevel("ModeSelectLevel");
}

#pragma endregion