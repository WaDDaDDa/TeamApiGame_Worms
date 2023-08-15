#include "UI_Box_AllTeamHpBar.h"
#include "UI_TeamHpBar.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Player.h"

#include <GameEnginePlatform/GameEngineInput.h>

UI_Box_AllTeamHpBar* UI_Box_AllTeamHpBar::AllTeamHpBarUI = nullptr;
UI_Box_AllTeamHpBar::UI_Box_AllTeamHpBar()
{
	AllTeamHpBarUI = this;
}

UI_Box_AllTeamHpBar::~UI_Box_AllTeamHpBar()
{
}

void UI_Box_AllTeamHpBar::Start()
{

}

void UI_Box_AllTeamHpBar::Update(float _Delta)
{

}

void UI_Box_AllTeamHpBar::AddTeamHpBar()
{
	int AllPlayerCount = Player::GetAllPlayer().size();

	// ���� �غκ� ��ġ �޸�
	//	float4 StartPos = { 600, 700 };

	// �÷��̾ 6���� ���
	float4 StartPos = { 600, 600 };
	
	// �÷��̾��� �� �ο���ŭ HP�ٸ� �����մϴ�.
	for (int PlayerIndex = 0; PlayerIndex < AllPlayerCount; PlayerIndex++)
	{
		UI_TeamHpBar* TeamHpBar = GetLevel()->CreateActor<UI_TeamHpBar>();
		AllTeamHpBars.push_back(TeamHpBar);
	}

	for (int PlayerIndex = 0; PlayerIndex < AllTeamHpBars.size(); PlayerIndex++)
	{

		// �� HP���� �ʱ������� �������ݴϴ�.
		AllTeamHpBars[PlayerIndex]->SetPos({StartPos.X, StartPos.Y + 20 * PlayerIndex });
		AllTeamHpBars[PlayerIndex]->SetHpBarWidth(StartPos.X);
		AllTeamHpBars[PlayerIndex]->TeamHpRenderer->SetYPivot(StartPos.Y + 20 * PlayerIndex);

		float InitPlayerHp = Player::GetAllPlayer()[PlayerIndex]->GetHp();

		// �� HP���� Hp���� ������ �ʱ� Player���� Hp������ �ʱ�ȭ ���ݴϴ�.
		AllTeamHpBars[PlayerIndex]->SetMaxPlayerHp(InitPlayerHp);
		AllTeamHpBars[PlayerIndex]->SetCurPlayerHp(InitPlayerHp);

		// �� HP���� ���� �°� �ؽ�ó�� �����մϴ�.
		switch (PlayerIndex)
		{
		case 0:
			AllTeamHpBars[PlayerIndex]->TeamNameRenderer->SetTexture("UI_BottomNameTagR.bmp");
			AllTeamHpBars[PlayerIndex]->TeamHpRenderer->SetTexture("UI_BottomHPbarR.bmp");
			break;

		case 1:
			AllTeamHpBars[PlayerIndex]->TeamNameRenderer->SetTexture("UI_BottomNameTagB.bmp");
			AllTeamHpBars[PlayerIndex]->TeamHpRenderer->SetTexture("UI_BottomHPbarB.bmp");
			break;

		case 2:
			AllTeamHpBars[PlayerIndex]->TeamNameRenderer->SetTexture("UI_BottomNameTagG.bmp");
			AllTeamHpBars[PlayerIndex]->TeamHpRenderer->SetTexture("UI_BottomHPbarG.bmp");
			break;

		case 3:
			AllTeamHpBars[PlayerIndex]->TeamNameRenderer->SetTexture("UI_BottomNameTagY.bmp");
			AllTeamHpBars[PlayerIndex]->TeamHpRenderer->SetTexture("UI_BottomHPbarY.bmp");
			break;

		case 4:
			AllTeamHpBars[PlayerIndex]->TeamNameRenderer->SetTexture("UI_BottomNameTagP.bmp");
			AllTeamHpBars[PlayerIndex]->TeamHpRenderer->SetTexture("UI_BottomHPbarP.bmp");
			break;

		case 5:
			AllTeamHpBars[PlayerIndex]->TeamNameRenderer->SetTexture("UI_BottomNameTagS.bmp");
			AllTeamHpBars[PlayerIndex]->TeamHpRenderer->SetTexture("UI_BottomHPbarS.bmp");
			
			break;

		default:
			break;
		}
	}

	isEndAllHpBarSetting = true;

}

void UI_Box_AllTeamHpBar::InitTeamHpBarData(int _Playerindex, int PlayerCurHp)
{
	AllTeamHpBars[_Playerindex]->InitDecreaseHpBar(PlayerCurHp);
}