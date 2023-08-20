#include "PlayLevel.h"


#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "ContentsEnum.h"
#include "BackGround.h"
#include "BackGroundEffect.h"
#include "Ground.h"
#include "Wave.h"
#include "Wind.h"
#include "UnderWater.h"
#include "Player.h"
#include "GameTurn.h"
#include "MouseObject.h"
#include "Cloud.h"
#include "HealItem.h"

#include "GameStateManager.h"
#include "UI_PlayerInfo.h"

#pragma region UI에서 사용할 헤더 & 함수 전방 선언
#include "UI_Button.h"
#include "UI_Inventory.h"
#include "UI_Wind.h"
#include "UI_Timer.h"


#include "UI_Box_AllTeamHpBar.h"

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






	CreateActor<MouseObject>();
}



void PlayLevel::LevelStart(GameEngineLevel* _NextLevel)
{

	{

		GroundFileName = GameStateManager::GameState->GetStageName() + ".Bmp";
		GroundPixelFileName = GameStateManager::GameState->GetStageName() + "_Ground.Bmp";

	}

	{

		GroundPtr = CreateActor<Ground>(RenderOrder::Ground);
		GroundPtr->Init(GroundFileName, GroundPixelFileName);

		

		BackGroundPtr = CreateActor<BackGround>(RenderOrder::Player);
		
		BackGroundPtr->VerticalPatternInit("gradient.Bmp", {5000.0f,2000.0f});


		
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
		for (size_t i = 0; i < 30; i++)
		{
			GameEngineActor* NewCloud = CreateActor<Cloud>(RenderOrder::BackGroundEffect);
			float RandX = GameEngineRandom::MainRandom.RandomFloat(0.0f, BACKGROUND_SCALE.X);
			float RandY = GameEngineRandom::MainRandom.RandomFloat(PLAY_GROUND_SCALE.hY() - 30.0f, PLAY_GROUND_SCALE.hY() + 30.0f);
			NewCloud->SetPos({ RandX, RandY });
		}
	}

	{
		
		for (size_t i = 0; i < 400; i++)
		{
			GameEngineActor* NewBackEffect = CreateActor<BackGroundEffect>();
			float RandX=GameEngineRandom::MainRandom.RandomFloat(0.0f, BACKGROUND_SCALE.X);
			float RandY = GameEngineRandom::MainRandom.RandomFloat(PLAY_GROUND_SCALE.hY(), 1800.0f);
			NewBackEffect->SetPos({ RandX,RandY });
		}
		
	}

	

	                                     
	// 플레이어 수만큼 랜덤으로 생성
	PlayerSetting(6);

	CreateActor<GameTurn>();

#pragma region UI 세팅
	//CreateActor<UI_Mouse>();

	std::string StageNameTest = GameStateManager::GameState->GetStageName();

	Inven = CreateActor<UI_Inventory>();
	Inven->SetPos({ 1400, 480 }); // UI 렌더러 사용시 초기 위치

	UI_Wind* WindBar = CreateActor<UI_Wind>();
	WindBar->SetPos({ 1180 , 700 });


	UI_Timer* TimerBox = CreateActor<UI_Timer>();
	TimerBox->SetPos({ 40 , 690 });


	UI_Box_AllTeamHpBar* AllTeamHpBar = CreateActor<UI_Box_AllTeamHpBar>();
//	AllTeamHpBar->InitTeamHpBarData();
	AllTeamHpBar->AddTeamHpBar();


	


	//	AllTeamHpBar->SetPos({ 400, 700 });

		//UI_TeamHpBar* TeamHp = CreateActor<UI_TeamHpBar>();

		//TeamHp->SetPos({ 100, 100});


		//// UI 세팅 테스트
		//UI_Button* Btn_StartGame = CreateActor<UI_Button>();
		//Btn_StartGame->InitButtonData("UI_Button_StartGame", float4{ UI_BUTTON_START_WITDH, UI_BUTTON_START_HEIGHT });
		//Btn_StartGame->SetPos({ 400, 1000 });
		//Btn_StartGame->SetClickedCallBack(ChangeLevel, 0, 0);
#pragma endregion



}

void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('J'))
	{
		GameEngineLevel::CollisionDebugRenderSwitch();
		GroundPtr->SwitchRender();
	}

	if (true == GameEngineInput::IsDown(VK_RBUTTON))
	{
		Inven->SwitchActiveState();
	}

	//cloud
	{

		if (0.0f >= CloudRespawn)
		{
			GameEngineActor* NewCloud = CreateActor<Cloud>(RenderOrder::BackGroundEffect);
			CloudRespawn = GameEngineRandom::MainRandom.RandomFloat(0.0f, 4.0f);

		}
		CloudRespawn -= _Delta;
		
	}

	//BackGroundEffect
	{
		
			if (0.0f >= BackGroundEffectRespawn)
			{
				GameEngineActor* NewBackEffect = CreateActor<BackGroundEffect>(RenderOrder::BackGroundEffect);
				float RandX = GameEngineRandom::MainRandom.RandomFloat(0.0f, BACKGROUND_SCALE.X);
				NewBackEffect->SetPos({ RandX,PLAY_GROUND_SCALE.hY() });

				BackGroundEffectRespawn = GameEngineRandom::MainRandom.RandomFloat(0.0f, 0.1f);
			}
		
			BackGroundEffectRespawn -= _Delta;
		
	}

}

void PlayLevel::Release()
{

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void PlayLevel::PlayerSetting(size_t _PlayerCount)
{
	for (size_t i = 0; i < _PlayerCount; i++)
	{
		float PlayerSettingX = GameEngineRandom::MainRandom.RandomFloat(0, GroundPtr->GetPixelGroundTexture()->GetScale().X);
		float PlayerSettingY = GameEngineRandom::MainRandom.RandomFloat(0, GroundPtr->GetPixelGroundTexture()->GetScale().Y);

		float4 CheckPos = { PlayerSettingX , PlayerSettingY };
		unsigned int CheckColor = GroundPtr->GetPixelGroundTexture()->GetColor(RGB(255, 255, 255), CheckPos);

		if (CheckColor == RGB(0, 0, 255))
		{
			Player* TestPlayer = CreateActor<Player>(RenderOrder::Player);
			TestPlayer->SetGroundTexture(GroundPtr->GetPixelGroundTexture());
			TestPlayer->SetPos(float4{ PlayerSettingX, PlayerSettingY });
		}
		else
		{
			while (CheckColor != RGB(0, 0, 255))
			{
				PlayerSettingX = GameEngineRandom::MainRandom.RandomFloat(0, GroundPtr->GetPixelGroundTexture()->GetScale().X);
				PlayerSettingY = GameEngineRandom::MainRandom.RandomFloat(0, GroundPtr->GetPixelGroundTexture()->GetScale().Y);

				CheckPos = { PlayerSettingX , PlayerSettingY };
				CheckColor = GroundPtr->GetPixelGroundTexture()->GetColor(RGB(255, 255, 255), CheckPos);

				if (CheckColor == RGB(0, 0, 255))
				{
					Player* TestPlayer = CreateActor<Player>(RenderOrder::Player);
					TestPlayer->SetGroundTexture(GroundPtr->GetPixelGroundTexture());
					TestPlayer->SetPos(float4{ PlayerSettingX, PlayerSettingY });
				}
			}
		}
	}

	for (size_t i = 0; i < _PlayerCount; i++)
	{
		float PlayerSettingX = GameEngineRandom::MainRandom.RandomFloat(0, GroundPtr->GetPixelGroundTexture()->GetScale().X);
		float PlayerSettingY = GameEngineRandom::MainRandom.RandomFloat(0, GroundPtr->GetPixelGroundTexture()->GetScale().Y);

		float4 CheckPos = { PlayerSettingX , PlayerSettingY };
		unsigned int CheckColor = GroundPtr->GetPixelGroundTexture()->GetColor(RGB(255, 255, 255), CheckPos);

		if (CheckColor == RGB(0, 0, 255))
		{
			HealItem* Hitem = CreateActor<HealItem>(RenderOrder::Item);
			Hitem->SetGroundTexture(GroundPtr->GetPixelGroundTexture());
			Hitem->SetPos(float4{ PlayerSettingX, 1200.0f });
		}
		else
		{
			while (CheckColor != RGB(0, 0, 255))
			{
				PlayerSettingX = GameEngineRandom::MainRandom.RandomFloat(0, GroundPtr->GetPixelGroundTexture()->GetScale().X);
				PlayerSettingY = GameEngineRandom::MainRandom.RandomFloat(0, GroundPtr->GetPixelGroundTexture()->GetScale().Y);

				CheckPos = { PlayerSettingX , PlayerSettingY };
				CheckColor = GroundPtr->GetPixelGroundTexture()->GetColor(RGB(255, 255, 255), CheckPos);

				if (CheckColor == RGB(0, 0, 255))
				{
					HealItem* Hitem = CreateActor<HealItem>(RenderOrder::Item);
					Hitem->SetGroundTexture(GroundPtr->GetPixelGroundTexture());
					Hitem->SetPos(float4{ PlayerSettingX, 1200.0f });
				}
			}
		}
	}
}



#pragma region UI 함수 포인터 등록용 함수


#pragma endregion