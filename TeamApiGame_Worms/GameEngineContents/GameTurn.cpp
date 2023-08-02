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
	CameraFocus(_Delta);

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
	ResetLiveTime();
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

//void GameTurn::CameraFocus()
//{
//	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
//	GetLevel()->GetMainCamera()->SetPos(TurnPlayer->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });
//}


void GameTurn::CameraFocus(float _Delta)
{
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();

	int CameraRangeX = GetLevel()->GetMainCamera()->GetPos().iX();
	int CameraRangeY = GetLevel()->GetMainCamera()->GetPos().iY();

	float ImageX = TurnPlayer->GetGroundTexture()->GetScale().X - 1280.0f;
	float ImageY = TurnPlayer->GetGroundTexture()->GetScale().Y - 720.0f;

	GetLevel()->GetMainCamera()->SetPos(TurnPlayer->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });


	// ī�޶� ���� �������� ��������.
	if (0 >= GetLevel()->GetMainCamera()->GetPos().X)
	{
		GetLevel()->GetMainCamera()->SetPos({ 0.0f, GetLevel()->GetMainCamera()->GetPos().Y });
	}
	// ī�޶� ���� ������ �ִ�ġ�� ��������.
	if (ImageX <= GetLevel()->GetMainCamera()->GetPos().X)
	{
		GetLevel()->GetMainCamera()->SetPos({ ImageX, GetLevel()->GetMainCamera()->GetPos().Y });
	}

	if (ImageY <= GetLevel()->GetMainCamera()->GetPos().Y)
	{
		GetLevel()->GetMainCamera()->SetPos({ GetLevel()->GetMainCamera()->GetPos().X, ImageY });
	}
}