#include "PlayLevel.h"


#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>

#include "ContentsEnum.h"
#include "BackGround.h"
#include "Ground.h"
#include "Wave.h"
#include "Wind.h"
#include "UnderWater.h"
#include "Player.h"
#include "GameTurn.h"
#include "MouseObject.h"

#pragma region UI에서 사용할 헤더 & 함수 전방 선언
#include "UI_Mouse.h"
#include "UI_Button.h"
#include "ContentsDefine.h"

void ChangeLevel(DWORD_PTR, DWORD_PTR);
#pragma endregion

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

Ground* PlayLevel::GetGround() const
{
	if (nullptr == GroundPtr)
	{
		MsgBoxAssert("Ground가 설정되지 않은채로 사용되려했습니다.");
		return nullptr;
	}
	
	return GroundPtr;
}

void PlayLevel::Start()
{
	//나중에 LobbyLevel에서 받아올것
	{
		GroundFileName = "MapBooks.Bmp";
		GroundPixelFileName = "MapBooks_Ground.Bmp";

	}



	CreateActor<MouseObject>();
}



void PlayLevel::LevelStart(GameEngineLevel* _NextLevel)
{
#pragma region UI 세팅
	CreateActor<UI_Mouse>();

	//// UI 세팅 테스트
	//UI_Button* Btn_StartGame = CreateActor<UI_Button>();
	//Btn_StartGame->InitButtonData("UI_Button_StartGame", float4{ UI_BUTTON_START_WITDH, UI_BUTTON_START_HEIGHT });
	//Btn_StartGame->SetPos({ 400, 1000 });
	//Btn_StartGame->SetClickedCallBack(ChangeLevel, 0, 0);
#pragma endregion


	{

		GroundPtr = CreateActor<Ground>(RenderOrder::Ground);
		GroundPtr->Init(GroundFileName, GroundPixelFileName);

		

		BackGroundPtr = CreateActor<BackGround>(RenderOrder::Player);
		BackGroundPtr->Init("Back.bmp", PLAY_BACKGROUND_SCALE);


		
		Wave* Wave1 = CreateActor<Wave>(RenderOrder::BackWave);
		Wave1->SetPos({ 0.0f,1775.0f });
		GameEngineActor* Wave2 = CreateActor<Wave>(RenderOrder::BackWave);
		
		Wave2->SetPos({ -30.0f,1800.0f });
		GameEngineActor* Wave3 = CreateActor<Wave>(RenderOrder::BackWave);
		Wave3->SetPos({ -60.0f,1825.0f});
		GameEngineActor* Wave4 = CreateActor<Wave>(RenderOrder::FrontWave);
		Wave4->SetPos({ -90.0f,1850.0f});
		GameEngineActor* Wave5 = CreateActor<Wave>(RenderOrder::FrontWave);
		Wave5->SetPos({ -120.0f,1875.0f });
		UnderWater* NewUnderWater = CreateActor<UnderWater>();
		NewUnderWater->DrawAtStage(this);


		
	}

	{
		Wind* PlayWind = CreateActor<Wind>();
		
	}



	{
		Player* TestPlayer = CreateActor<Player>(RenderOrder::Player);
		TestPlayer->SetGroundTexture(GroundPtr->GetPixelGroundTexture());
		TestPlayer->SetPos(float4{ 100, 100 });
	}

	{
		Player* TestPlayer = CreateActor<Player>(RenderOrder::Player);
		TestPlayer->SetGroundTexture(GroundPtr->GetPixelGroundTexture());
		TestPlayer->SetPos(float4{ 400, 100 });
	}

	{
		Player* TestPlayer = CreateActor<Player>(RenderOrder::Player);
		TestPlayer->SetGroundTexture(GroundPtr->GetPixelGroundTexture());
		TestPlayer->SetPos(float4{ 700, 100 });
	}

	{
		Player* TestPlayer = CreateActor<Player>(RenderOrder::Player);
		TestPlayer->SetGroundTexture(GroundPtr->GetPixelGroundTexture());
		TestPlayer->SetPos(float4{ 1000, 100 });
	}

	CreateActor<GameTurn>();
}

void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('J'))
	{
		GameEngineLevel::CollisionDebugRenderSwitch();
		GroundPtr->SwitchRender();
	}
}

void PlayLevel::Release()
{

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}


#pragma region UI 함수 포인터 등록용 함수


#pragma endregion