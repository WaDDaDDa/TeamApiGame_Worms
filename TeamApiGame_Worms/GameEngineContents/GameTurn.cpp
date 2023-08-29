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


	// ���÷��̾��ε� ���������� IsTurnPlayer�� false���Ǹ� Turn�� �ð��� �����.
	if (TurnPlayer->IsTurnPlayer == false)
	{
		StopLiveTime();
	}
	// ���� �ð��� ������¿��� ���� ��� ����� IsTurnPlayer�� True�� ���ƿ���
	// Turn�ǽð��� �ٽ� �帣�� Turn�÷��̾ �����Ѵ�.
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
			// �������� ����Ǹ� �ٽ� �÷��̾�� ���ư���.
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

	//std::string Text = "�� �÷��̾� ������ġ : ";
	//Text += std::to_string(TurnPlayer->GetPos().X);
	//Text += ", ";
	//Text += std::to_string(TurnPlayer->GetPos().Y);
	//Text += "  ī�޶� ������ġ :";
	//Text += std::to_string(GetLevel()->GetMainCamera()->GetPos().X);
	//Text += ", ";
	//Text += std::to_string(GetLevel()->GetMainCamera()->GetPos().Y);

	//Text += "  �� �÷��̾� ��ȣ :";
	//Text += std::to_string(StartValue);
	//Text += "  �� �÷��̾� ü�� :";
	//Text += std::to_string(TurnPlayer->GetHp());

	//Text += "  �� �ð� :";
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

	//���� �÷��̾�bool�� false�� ����
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
	TurnPlayer->StartSound = true;

	if (GameEngineRandom::MainRandom.RandomInt(0 , 1) == 1)
	{
		CreateItem();
	}

	// Ÿ�̸� UI�� ������ ���� TurnPlayer�� �°� ��ȯ
	UI_Timer::GetTimerUI()->ChangeTimerColor(StartValue);

	ResetLiveTime();
	Wind::GetWind()->ChangeWind(_Delta);
}

void GameTurn::ChangeTurnPlayer(int _Value)
{
	//���� �÷��̾�bool�� false�� ����
	TurnPlayer->SwitchIsTurnPlayer();

	TurnPlayer = Player::GetAllPlayer()[_Value];
	// ���� �÷��̾� bool�� true�� ����
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
		// �÷��̾� ���� ���
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
		// �÷��̾� �Ѹ� ����.
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
