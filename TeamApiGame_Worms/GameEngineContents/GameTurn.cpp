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
	// ���÷��̾��ε� ���������� IsTurnPlayer�� false���Ǹ� Turn�� �ð��� �����.
	if (TurnPlayer->IsTurnPlayer == false)
	{
		StopLiveTime();
	}
	// ���� �ð��� ������¿��� ���� ��� ����� IsTurnPlayer�� True�� ���ƿ���
	// Turn�ǽð��� �ٽ� �帣�� Turn�÷��̾ �����Ѵ�.
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
			// �������� ����Ǹ� �ٽ� �÷��̾�� ���ư���.
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

	std::string Text = "�� �÷��̾� ������ġ : ";
	Text += std::to_string(TurnPlayer->GetPos().X);
	Text += ", ";
	Text += std::to_string(TurnPlayer->GetPos().Y);
	Text += "  ī�޶� ������ġ :";
	Text += std::to_string(GetLevel()->GetMainCamera()->GetPos().X);
	Text += ", ";
	Text += std::to_string(GetLevel()->GetMainCamera()->GetPos().Y);

	Text += "  �� �÷��̾� ��ȣ :";
	Text += std::to_string(StartValue);
	Text += "  �� �÷��̾� ü�� :";
	Text += std::to_string(TurnPlayer->GetHp());

	Text += "  �� �ð� :";
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
	//���� �÷��̾�bool�� false�� ����
	TurnPlayer->SwitchIsTurnPlayer();

	++StartValue;
	size_t SIZE = Player::GetAllPlayer().size();

	if (StartValue >= SIZE)
	{
		StartValue = 0;
	}
	
	// �÷��̾� ���°� �׾������� ���� �÷��̾��.
	while (PlayerState::DeathEnd == Player::GetAllPlayer()[StartValue]->GetState())
	{
		++StartValue;
		if (StartValue >= SIZE)
		{
			StartValue = 0;
		}
	}


	TurnPlayer = Player::GetAllPlayer()[StartValue];
	// ���� �÷��̾� bool�� true�� ����
	TurnPlayer->SwitchIsTurnPlayer();

	// Ÿ�̸� UI�� ������ ���� TurnPlayer�� �°� ��ȯ
	UI_Timer::GetTimerUI()->ChangeTimerColor(StartValue);

	ResetLiveTime();
	Wind::GetWind()->ChangeWind(_Delta);
}
