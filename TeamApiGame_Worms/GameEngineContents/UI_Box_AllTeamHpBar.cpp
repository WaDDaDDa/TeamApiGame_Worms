#include "UI_Box_AllTeamHpBar.h"
#include "UI_TeamHpBar.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Player.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "ContentsEnum.h"
#include <algorithm>


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
	// 디버그용
	//CurHpDebugRenderer = CreateUIRenderer(RenderOrder::UI);
	//CurHpDebugRenderer->SetRenderPos({ 100, 600 });

	//CurHpDebugRenderer2 = CreateUIRenderer(RenderOrder::UI);
	//CurHpDebugRenderer2->SetRenderPos({ 100, 620 });

	//CurHpDebugRenderer3 = CreateUIRenderer(RenderOrder::UI);
	//CurHpDebugRenderer3->SetRenderPos({ 100, 640 });

	//CurHpDebugRenderer4 = CreateUIRenderer(RenderOrder::UI);
	//CurHpDebugRenderer4->SetRenderPos({ 100, 660 });

	//CurHpDebugRenderer5 = CreateUIRenderer(RenderOrder::UI);
	//CurHpDebugRenderer5->SetRenderPos({ 100, 680 });

	//CurHpDebugRenderer6 = CreateUIRenderer(RenderOrder::UI);
	//CurHpDebugRenderer6->SetRenderPos({ 100, 700 });

}

bool CompareTeamHp(const UI_Box_AllTeamHpBar::IndexedTeamHpBar& _Left, const UI_Box_AllTeamHpBar::IndexedTeamHpBar& _Right)
{
	return _Left.GetTeamHp() > _Right.GetTeamHp();
}

void UI_Box_AllTeamHpBar::Update(float _Delta)
{
	//CurHpDebugRenderer->SetText(std::to_string(static_cast<int>(GetAllTeamHpBarUI()->GetIndexHpBarUI(0)->GetCurHpBarAmount())));
	//CurHpDebugRenderer2->SetText(std::to_string(static_cast<int>(GetAllTeamHpBarUI()->GetIndexHpBarUI(1)->GetCurHpBarAmount())));
	//CurHpDebugRenderer3->SetText(std::to_string(static_cast<int>(GetAllTeamHpBarUI()->GetIndexHpBarUI(2)->GetCurHpBarAmount())));
	//CurHpDebugRenderer4->SetText(std::to_string(static_cast<int>(GetAllTeamHpBarUI()->GetIndexHpBarUI(3)->GetCurHpBarAmount())));
	//CurHpDebugRenderer5->SetText(std::to_string(static_cast<int>(GetAllTeamHpBarUI()->GetIndexHpBarUI(4)->GetCurHpBarAmount())));
	//CurHpDebugRenderer6->SetText(std::to_string(static_cast<int>(GetAllTeamHpBarUI()->GetIndexHpBarUI(5)->GetCurHpBarAmount())));

	//if (true == GameEngineInput::IsDown(VK_TAB))
	//{

		// HP 값을 비교하기 위해 배열로 저장해줍니다. 
		for (int i = 0; i < (int)AllSortedTeamHpBars.size(); i++)
		{
			AllSortedTeamHpBars[i].m_TeamHp = AllTeamHpBars[AllSortedTeamHpBars[i].m_Index]->GetCurHpBarAmount();
		}

		// 위에서 저장된 배열 안의 HP 값을 비교하여 내림차순으로 HP BAR를 정렬합니다.
		std::sort(AllSortedTeamHpBars.begin(), AllSortedTeamHpBars.end(), CompareTeamHp);

		for (int i = 0; i < (int)AllSortedTeamHpBars.size(); i++)
		{
			// 첫 번째로 정렬된 HpBar가 화면상 가장 위로 가도록 인덱스를 세팅합니다.
			int HpBarIndex = AllSortedTeamHpBars[i].m_Index;

			// 정렬된 HP BAR의 이동 위치를 세팅해줍니다.
			AllTeamHpBars[HpBarIndex]->InitMoveSortedHpbars(AllTeamHpBars[HpBarIndex]->GetPos(), AllTeamHpBarPos[i], 100.0f);

		}
	//}

}


void UI_Box_AllTeamHpBar::AddTeamHpBar()
{
	int AllPlayerCount = static_cast<int>(Player::GetAllPlayer().size());

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
		float4 initPos = { StartPos.X, StartPos.Y + 20 * PlayerIndex };
		AllTeamHpBars[PlayerIndex]->SetPos(initPos);

		// HP바 Sort에 사용할 초기 위치를 저장해줍니다.
		AllTeamHpBarPos.push_back(initPos);


		int InitPlayerHp = Player::GetAllPlayer()[PlayerIndex]->GetHp();

		// 각 HP바의 Hp관련 값들을 초기 Player들의 Hp값으로 초기화 해줍니다.
		AllTeamHpBars[PlayerIndex]->SetMaxPlayerHp(InitPlayerHp);
		AllTeamHpBars[PlayerIndex]->SetCurPlayerHp(InitPlayerHp);

		AllSortedTeamHpBars.push_back({ AllTeamHpBars[PlayerIndex]->GetCurHpBarAmount(), PlayerIndex });

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

void UI_Box_AllTeamHpBar::SortTeamHpBar()
{



}
