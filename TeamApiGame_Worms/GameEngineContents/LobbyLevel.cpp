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
#include "UI_Terrain_Button.h"
#include "UI_TurnTime_Button.h"
#include "UI_RoundTime_Button.h"
#include "UI_Win_Button.h"
#include "UI_WormSelect_Button.h"
#include "UI_WormMaxHp_Button.h"
#include "UI_Teleportin_Button.h"

#include "ContentsDefine.h"
#include "MouseObject.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>


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
	Box_Terrain->SetPos({ 370, 140 });

	UI_Box_Teams* Box_Teams = CreateActor<UI_Box_Teams>();
	Box_Teams->SetPos({ 920, 140 });

	UI_Box_SchemeOption* Box_SchemeOption = CreateActor<UI_Box_SchemeOption>();
	Box_SchemeOption->SetPos({ 370, 400 });

	UI_Box_Barracks* Box_Barracks = CreateActor<UI_Box_Barracks>();
	Box_Barracks->SetPos({ 920, 395 });

	// Button 세팅
	Btn_Terrain = CreateActor<UI_Terrain_Button>();
	Btn_Terrain->SetPos({ 380, 140 });


	UI_TurnTime_Button* Btn_TurnTime = CreateActor<UI_TurnTime_Button>();
	Btn_TurnTime->SetPos({ 160, 580 });

	UI_RoundTime_Button* Btn_RoundTime = CreateActor<UI_RoundTime_Button>();
	Btn_RoundTime->SetPos({ 240, 580 });

	UI_Win_Button* Btn_Win = CreateActor<UI_Win_Button>();
	Btn_Win->SetPos({ 320, 580 });
	
	UI_WormSelect_Button* Btn_WormSelect = CreateActor<UI_WormSelect_Button>();
	Btn_WormSelect->SetPos({ 400 , 580});

	UI_WormMaxHp_Button* Btn_WormMaxHp = CreateActor<UI_WormMaxHp_Button>();
	Btn_WormMaxHp->SetPos({ 480 , 580 });

	UI_Teleportin_Button* Btn_Teleportin = CreateActor<UI_Teleportin_Button>();
	Btn_Teleportin->SetPos({ 560, 580 });


	UI_Button* Btn_StartGame = CreateActor<UI_Button>();
	Btn_StartGame->InitButtonData("UI_Button_StartGame", float4{ 400, 80 }, true);
	Btn_StartGame->SetPos({ 1065, 580 });
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
	if (true == GameEngineInput::IsDown('J'))
	{
		GameEngineLevel::CollisionDebugRenderSwitch();
	}








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