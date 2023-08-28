#include "ModeSelectLevel.h"
#include "LobbyLevel.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "BackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>


#pragma region UI에서 사용할 헤더 & 함수 전방 선언
#include "UI_Mouse.h"
#include "UI_Lobby_SelectTitle.h"
#include "UI_Button.h"
#include "UI_Meteor.h"

#include "ContentsDefine.h"
#include "MouseObject.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineRandom.h>


void QuitGame(DWORD_PTR, DWORD_PTR);
void ChangeLevel(DWORD_PTR, DWORD_PTR);
void ChageSelectedModeText(const std::string& _NewText);

#pragma endregion

ModeSelectLevel::ModeSelectLevel()
{
}

ModeSelectLevel::~ModeSelectLevel()
{
}


void ModeSelectLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

	CreateActor<MouseObject>();
	CreateActor<UI_Mouse>();

	// SelectMode 오브젝트
	{

		UI_Lobby_SelectTitle* SelectTitle = CreateActor<UI_Lobby_SelectTitle>();

		UI_Button* Btn_QuitGame = CreateActor<UI_Button>();
		Btn_QuitGame->InitButtonData("UI_Button_Quit", float4{ 250, 60 }, true);
		Btn_QuitGame->SetPos({ 915, 670 });
		Btn_QuitGame->SetClickedCallBack(QuitGame, 0, 0);
		Btn_QuitGame->SetTextValue("Quit the game and return to the real world.");
		Btn_QuitGame->SetHoverCallBackString(ChageSelectedModeText);


		UI_Button* Btn_1UpGame = CreateActor<UI_Button>();
		Btn_1UpGame->InitButtonData("UI_1up", float4{ 400, 200 }, true);
		Btn_1UpGame->SetPos({ 420, 300 });
		Btn_1UpGame->SetTextValue("Go to the single player menu.");
		Btn_1UpGame->SetHoverCallBackString(ChageSelectedModeText);
		
		UI_Button* Btn_MultiGame = CreateActor<UI_Button>();
		Btn_MultiGame->InitButtonData("UI_multi", float4{ 400, 200 }, true);
		Btn_MultiGame->SetPos({ 840, 300 });
		Btn_MultiGame->SetTextValue("Create a single or multi-player game.");
		Btn_MultiGame->SetHoverCallBackString(ChageSelectedModeText);
		Btn_MultiGame->SetClickedCallBack(ChangeLevel, 0, 0);

		UI_Button* Btn_NetGame = CreateActor<UI_Button>();
		Btn_NetGame->InitButtonData("UI_net", float4{ 400, 200 }, true);
		Btn_NetGame->SetPos({ 420, 510 });
		Btn_NetGame->SetTextValue("Play over local area network or the Internet.");
		Btn_NetGame->SetHoverCallBackString(ChageSelectedModeText);

		UI_Button* Btn_OptionsGame = CreateActor<UI_Button>();
		Btn_OptionsGame->InitButtonData("UI_options", float4{ 400, 200 }, true);
		Btn_OptionsGame->SetPos({ 840, 510 });
		Btn_OptionsGame->SetTextValue("Go to the options menu.");
		Btn_OptionsGame->SetHoverCallBackString(ChageSelectedModeText);
	}


	//BackGround
	{
		BackGround* BackGroundPtr = CreateActor<BackGround>();
		BackGroundPtr->VerticalPatternInit("Lobby_Backdrop.bmp");

	}

	{
		if (nullptr == GameEngineSound::FindSound("Stats.wav"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Sound\\Effects\\");
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("Stats.wav"));
		}

		BGMPlayer = GameEngineSound::SoundPlay("Stats.wav", 100);
	}
}

void ModeSelectLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	
	dynamic_cast<LobbyLevel*>(_NextLevel)->SetBGMPlayer(BGMPlayer);
}

void ModeSelectLevel::Start()
{
	
}

void ModeSelectLevel::Update(float _Delta)
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

//void ModeSelectLevel::SetBGMPlayer(GameEngineSoundPlayer& _BGMPlayer)
//{
//	BGMPlayer = _BGMPlayer;
//}
#pragma region UI 함수 포인터 등록용 함수

void QuitGame(DWORD_PTR, DWORD_PTR)
{
	DestroyWindow(GameEngineWindow::MainWindow.GetHWND());
}

void ChangeLevel(DWORD_PTR, DWORD_PTR)
{
	GameEngineCore::ChangeLevel("LobbyLevel");
}

void ChageSelectedModeText(const std::string& _NewText)
{
	UI_Lobby_SelectTitle::GetLobbyTitle()->GetMainTextRenderer()->SetText(_NewText, 28, RGB(0, 255, 255));
}

#pragma endregion