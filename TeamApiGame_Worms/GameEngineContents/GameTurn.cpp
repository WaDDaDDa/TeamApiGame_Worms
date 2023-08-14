#include "GameTurn.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "Player.h"
#include "Wind.h"

#include "UI_Timer.h"

GameTurn GameTurn::MainGameTurn;
float GameTurn::TurnTime = 0.0f;

GameTurn::GameTurn()
{
	
}

GameTurn::~GameTurn()
{

}

void GameTurn::Start()
{
	TurnPlayer = Player::GetAllPlayer()[StartValue];
	TurnPlayer->SwitchIsTurnPlayer();
}

void GameTurn::Update(float _Delta)
{
	TurnTime = TurnPlayTime - GetLiveTime();
	// 턴플레이어인데 무기사용으로 IsTurnPlayer가 false가되면 Turn의 시간을 멈춘다.
	if (TurnPlayer->IsTurnPlayer == false)
	{
		StopLiveTime();
	}
	// 턴의 시간이 멈춘상태에서 무기 사용 종료로 IsTurnPlayer가 True로 돌아오면
	// Turn의시간이 다시 흐르고 Turn플레이어를 변경한다.
	if (GetStopValue() == true && TurnPlayer->IsTurnPlayer == true)
	{
		size_t PlayerCount = Player::GetAllPlayer().size();
		int PlayerStateCount = 0;
		for (size_t i = 0; i < PlayerCount; i++)
		{
			if (PlayerState::Idle == Player::GetAllPlayer()[i]->GetState() || PlayerState::DeathEnd == Player::GetAllPlayer()[i]->GetState())
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
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	std::string Text = "턴 플레이어 현재위치 : ";
	Text += std::to_string(TurnPlayer->GetPos().X);
	Text += ", ";
	Text += std::to_string(TurnPlayer->GetPos().Y);
	Text += "  카메라 현재위치 :";
	Text += std::to_string(GetLevel()->GetMainCamera()->GetPos().X);
	Text += ", ";
	Text += std::to_string(GetLevel()->GetMainCamera()->GetPos().Y);

	Text += "  턴 플레이어 번호 :";
	Text += std::to_string(StartValue);
	Text += "  턴 플레이어 체력 :";
	Text += std::to_string(TurnPlayer->GetHp());

	Text += "  턴 시간 :";
	Text += std::to_string(GetLiveTime());

	Text += "  CurAngle : ";
	Text += std::to_string(static_cast<int>(TurnPlayer->GetCurAngle() * 1000));

	TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));

	
	

	{
		HDC dc2 = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

		std::string Text2 = "WindVector : ";
		Text2 += std::to_string(Wind::GetWind()->GetWindVector().X);

		TextOutA(dc2, 2,20, Text2.c_str(), static_cast<int>(Text2.size()));
	}

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

	// 타이머 UI의 색깔을 현재 TurnPlayer에 맞게 변환
	UI_Timer::GetTimerUI()->ChangeTimerColor(StartValue);

	ResetLiveTime();
	Wind::GetWind()->ChangeWind(_Delta);
}
