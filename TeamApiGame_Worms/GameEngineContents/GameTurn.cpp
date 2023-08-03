#include "GameTurn.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "Player.h"

GameTurn GameTurn::MainGameTurn;

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
	// ���÷��̾��ε� ���������� IsTurnPlayer�� false���Ǹ� Turn�� �ð��� �����.
	if (TurnPlayer->IsTurnPlayer == false)
	{
		StopLiveTime();
	}
	// ���� �ð��� ������¿��� ���� ��� ����� IsTurnPlayer�� True�� ���ƿ���
	// Turn�ǽð��� �ٽ� �帣�� Turn�÷��̾ �����Ѵ�.
	if (GetStopValue() == true && TurnPlayer->IsTurnPlayer == true)
	{
		GoLiveTime(); 
		ChangeTurnPlayer();
	}

	if (TurnPlayTime <= GetLiveTime())
	{
		ChangeTurnPlayer();
	}

	if (true == GameEngineInput::IsDown('Q'))
	{
		ChangeTurnPlayer();
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
}

void GameTurn::ChangeTurnPlayer()
{
	//���� �÷��̾�bool�� false�� ����
	TurnPlayer->SwitchIsTurnPlayer();

	++StartValue;
	int SIZE = Player::GetAllPlayer().size();
	if (StartValue >= SIZE)
	{
		StartValue = 0;
	}
	TurnPlayer = Player::GetAllPlayer()[StartValue];
	// ���� �÷��̾� bool�� true�� ����
	TurnPlayer->SwitchIsTurnPlayer();

	ResetLiveTime();
}
