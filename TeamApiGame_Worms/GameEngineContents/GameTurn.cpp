#include "GameTurn.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Player.h"
#include "Wind.h"
#include "Ground.h"
#include "HealItem.h"
#include "ContentsEnum.h"

#include "UI_Timer.h"
#include "UI_Box_AllTeamHpBar.h"
#include "GameStateManager.h"

GameTurn* GameTurn::MainGameTurn;
float GameTurn::TurnTime = 0.0f;

GameTurn::GameTurn()
{
	
}

GameTurn::~GameTurn()
{

}

void GameTurn::Start()
{
	MainGameTurn = this;
	TurnPlayer = Player::GetAllPlayer()[StartValue];
	TurnPlayer->SwitchIsTurnPlayer();
	Init();
}

void GameTurn::Init()
{
	size_t PlayerCount = Player::GetAllPlayer().size();
	for (size_t i = 0; i < PlayerCount; i++)
	{
		Player::GetAllPlayer()[i]->SetTurnPlayerIndex(static_cast<int>(i));
	}

	TurnPlayTime = GameStateManager::GameState->GetTurnTime();
}

void GameTurn::Update(float _Delta)
{
	//TurnPlayer = Player::GetAllPlayer()[StartValue];
	GameOverCheck(_Delta);

	TurnTime = TurnPlayTime - GetLiveTime();
	size_t PlayerCount = Player::GetAllPlayer().size();


	// 턴플레이어인데 무기사용으로 IsTurnPlayer가 false가되면 Turn의 시간을 멈춘다.
	if (TurnPlayer->IsTurnPlayer == false)
	{
		StopLiveTime();
	}
	// 턴의 시간이 멈춘상태에서 무기 사용 종료로 IsTurnPlayer가 True로 돌아오면
	// Turn의시간이 다시 흐르고 Turn플레이어를 변경한다.
	if (GetStopValue() == true && TurnPlayer->IsTurnPlayer == true)
	{
		for (size_t i = 0; i < PlayerCount; i++)
		{
			if (0 >= Player::GetAllPlayer()[static_cast<int>(i)]->GetHp() && PlayerState::DeathEnd != Player::GetAllPlayer()[static_cast<int>(i)]->GetState())
			{
				ChangeTurnPlayer(static_cast<int>(i));
				return;
			}
		}

		int PlayerStateCount = 0;
		for (size_t i = 0; i < PlayerCount; i++)
		{
			if (PlayerState::Idle == Player::GetAllPlayer()[static_cast<int>(i)]->GetState() || PlayerState::DeathEnd == Player::GetAllPlayer()[static_cast<int>(i)]->GetState())
			{
				PlayerStateCount++;
			}
		}

		if (PlayerStateCount == PlayerCount)
		{
			// 무기사용이 종료되면 다시 플레이어로 돌아간다.
			GoLiveTime();
			ChangeTurnPlayer(_Delta);
		}

	}

	if (TurnPlayer->GetState() == PlayerState::DeathEnd && TurnPlayer->GetIsDiving())
	{
		ChangeTurnPlayer(_Delta);
	}

	if (TurnPlayTime <= GetLiveTime())
	{
		ChangeTurnPlayer(_Delta);
	}

	if (true == GameEngineInput::IsDown('Q'))
	{
		ChangeTurnPlayer(_Delta);
	}

	if (true == GameEngineInput::IsDown(VK_F2))
	{
		GameEngineLevel::CollisionDebugRenderSwitch();
	}
}

void GameTurn::Render(float _Delta)
{
	//HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	//std::string Text = "턴 플레이어 현재위치 : ";
	//Text += std::to_string(TurnPlayer->GetPos().X);
	//Text += ", ";
	//Text += std::to_string(TurnPlayer->GetPos().Y);
	//Text += "  카메라 현재위치 :";
	//Text += std::to_string(GetLevel()->GetMainCamera()->GetPos().X);
	//Text += ", ";
	//Text += std::to_string(GetLevel()->GetMainCamera()->GetPos().Y);

	//Text += "  턴 플레이어 번호 :";
	//Text += std::to_string(StartValue);
	//Text += "  턴 플레이어 체력 :";
	//Text += std::to_string(TurnPlayer->GetHp());

	//Text += "  턴 시간 :";
	//Text += std::to_string(GetLiveTime());

	//Text += "  CurAngle : ";
	//Text += std::to_string(static_cast<int>(TurnPlayer->GetCurAngle() * 1000));

	//TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));

	//
	//

	//{
	//	HDC dc2 = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	//	std::string Text2 = "WindVector : ";
	//	Text2 += std::to_string(Wind::GetWind()->GetWindVector().X);

	//



	//	TextOutA(dc2, 2,20, Text2.c_str(), static_cast<int>(Text2.size()));
	//}

}

void GameTurn::ChangeTurnPlayer(float _Delta)
{

	//원래 플레이어bool값 false로 변경
	TurnPlayer->SwitchIsTurnPlayer();

	++StartValue;

	size_t SIZE = Player::GetAllPlayer().size();

	if (StartValue >= SIZE)
	{
		StartValue = 0;
	}

	if (true == GameOverCheck(_Delta))
	{
		return;
	}
	
	// 플레이어 상태가 죽어있으면 다음 플레이어로.
	while (PlayerState::DeathEnd == Player::GetAllPlayer()[StartValue]->GetState())
	{
		++StartValue;
		if (StartValue >= SIZE)
		{
			StartValue = 0;
		}
	}


	TurnPlayer = Player::GetAllPlayer()[StartValue];
	// 현재 플레이어 bool값 true로 변경
	TurnPlayer->SwitchIsTurnPlayer();
	TurnPlayer->StartSound = true;

	if (GameEngineRandom::MainRandom.RandomInt(0 , 1) == 1)
	{
		CreateItem();
	}

	// 타이머 UI의 색깔을 현재 TurnPlayer에 맞게 변환
	UI_Timer::GetTimerUI()->ChangeTimerColor(StartValue);

	ResetLiveTime();
	Wind::GetWind()->ChangeWind(_Delta);
}

void GameTurn::ChangeTurnPlayer(int _Value)
{
	//원래 플레이어bool값 false로 변경
	TurnPlayer->SwitchIsTurnPlayer();

	TurnPlayer = Player::GetAllPlayer()[_Value];
	// 현재 플레이어 bool값 true로 변경
	TurnPlayer->SwitchIsTurnPlayer();
}

bool GameTurn::GameOverCheck(float _Delta)
{
	size_t Psize = Player::GetAllPlayer().size();
	size_t Value = 0;
	for (size_t i = 0; i < Psize; i++)
	{
		if (PlayerState::DeathEnd == Player::GetAllPlayer()[i]->GetState())
		{
			Value++;
		}
	}

	if (Value == Psize)
	{
		GameOverDelta += _Delta;
		// 플레이어 전원 사망
		if (GameOverDelta >= 5.0f)
		{
			//GameEngineCore::ChangeLevel("TitleLevel");
			DestroyWindow(GameEngineWindow::MainWindow.GetHWND());
			return true;
		}
		return true;
	}
	else if (Value == Psize - 1)
	{
		// 플레이어 한명만 생존.
		for (size_t i = 0; i < Psize; i++)
		{
			for (size_t i = 0; i < Psize; i++)
			{
				if (PlayerState::Idle == Player::GetAllPlayer()[i]->GetState())
				{
					TurnPlayer->IsTurnPlayer = false;
					Player::GetAllPlayer()[i]->IsTurnPlayer = true;
				}
			}

			return true;
		}
	}

	return false;
}

void GameTurn::TurnPlayerAllOff()
{
	StopLiveTime();

	size_t PlayerCount = Player::GetAllPlayer().size();
	for (size_t i = 0; i < PlayerCount; i++)
	{
		Player::GetAllPlayer()[i]->IsTurnPlayer = false;
	}
	TurnPlayer->StartSound = false;
}

void GameTurn::StartTurnPlayer()
{
	GoLiveTime();
	TurnPlayer->IsTurnPlayer = true;
	TurnPlayer->StartSound = true;

}

void GameTurn::CreateItem(size_t _Count)
{
	GameEngineWindowTexture* GTexture = TurnPlayer->GetGroundTexture();
	float PlayerSettingX = GameEngineRandom::MainRandom.RandomFloat(0, GTexture->GetScale().X);
	float PlayerSettingY = GameEngineRandom::MainRandom.RandomFloat(0, GTexture->GetScale().Y);

	float4 CheckPos = { PlayerSettingX , PlayerSettingY };
	unsigned int CheckColor = GTexture->GetColor(RGB(255, 255, 255), CheckPos);

	for (size_t i = 0; i < _Count; i++)
	{
		float PlayerSettingX = GameEngineRandom::MainRandom.RandomFloat(0, GTexture->GetScale().X);
		float PlayerSettingY = GameEngineRandom::MainRandom.RandomFloat(0, GTexture->GetScale().Y);

		float4 CheckPos = { PlayerSettingX , PlayerSettingY };
		unsigned int CheckColor = GTexture->GetColor(RGB(255, 255, 255), CheckPos);

		if (CheckColor == RGB(0, 0, 255))
		{
			Hitem = GetLevel()->CreateActor<HealItem>(RenderOrder::Item);
			Hitem->SetGroundTexture(GTexture);
			Hitem->SetPos(float4{ PlayerSettingX, PlayerSettingY });
		}
		else
		{
			while (CheckColor != RGB(0, 0, 255))
			{
				PlayerSettingX = GameEngineRandom::MainRandom.RandomFloat(0, GTexture->GetScale().X);
				PlayerSettingY = GameEngineRandom::MainRandom.RandomFloat(0, GTexture->GetScale().Y);

				CheckPos = { PlayerSettingX , PlayerSettingY };
				CheckColor = GTexture->GetColor(RGB(255, 255, 255), CheckPos);

				if (CheckColor == RGB(0, 0, 255))
				{
					Hitem = GetLevel()->CreateActor<HealItem>(RenderOrder::Item);
					Hitem->SetGroundTexture(GTexture);
					Hitem->SetPos(float4{ PlayerSettingX, PlayerSettingY });
				}
			}
		}
	}
}
