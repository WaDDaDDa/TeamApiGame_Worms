#include "GameTurn.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "Player.h"


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
	CameraFocus();

	if (true == GameEngineInput::IsDown('Q'))
	{
		ChangeTurnPlayer();
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
}

void GameTurn::CameraFocus()
{
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	GetLevel()->GetMainCamera()->SetPos(TurnPlayer->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });
}