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

	// 가장 밑부분 위치 메모
	//	float4 StartPos = { 600, 700 };

	// 플레이어가 6명인 경우
	float4 StartPos = { 600, 600 };
	
	// 플레이어의 총 인원만큼 HP바를 생성합니다.
	for (int PlayerIndex = 0; PlayerIndex < AllPlayerCount; PlayerIndex++)
	{
		UI_TeamHpBar* TeamHpBar = GetLevel()->CreateActor<UI_TeamHpBar>();
		AllTeamHpBars.push_back(TeamHpBar);
	}

	for (int PlayerIndex = 0; PlayerIndex < AllTeamHpBars.size(); PlayerIndex++)
	{

		// 각 HP바의 초기지점을 설정해줍니다.
		AllTeamHpBars[PlayerIndex]->SetPos({StartPos.X, StartPos.Y + 20 * PlayerIndex });
		AllTeamHpBars[PlayerIndex]->SetHpBarWidth(StartPos.X);
		AllTeamHpBars[PlayerIndex]->TeamHpRenderer->SetYPivot(StartPos.Y + 20 * PlayerIndex);

		float InitPlayerHp = Player::GetAllPlayer()[PlayerIndex]->GetHp();

		// 각 HP바의 Hp관련 값들을 초기 Player들의 Hp값으로 초기화 해줍니다.
		AllTeamHpBars[PlayerIndex]->SetMaxPlayerHp(InitPlayerHp);
		AllTeamHpBars[PlayerIndex]->SetCurPlayerHp(InitPlayerHp);

		// 각 HP바의 색깔에 맞게 텍스처를 적용합니다.
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