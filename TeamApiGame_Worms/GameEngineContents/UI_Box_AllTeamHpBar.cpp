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
	// ����׿�
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

		// HP ���� ���ϱ� ���� �迭�� �������ݴϴ�. 
		for (int i = 0; i < (int)AllSortedTeamHpBars.size(); i++)
		{
			AllSortedTeamHpBars[i].m_TeamHp = AllTeamHpBars[AllSortedTeamHpBars[i].m_Index]->GetCurHpBarAmount();
		}

		// ������ ����� �迭 ���� HP ���� ���Ͽ� ������������ HP BAR�� �����մϴ�.
		std::sort(AllSortedTeamHpBars.begin(), AllSortedTeamHpBars.end(), CompareTeamHp);

		for (int i = 0; i < (int)AllSortedTeamHpBars.size(); i++)
		{
			// ù ��°�� ���ĵ� HpBar�� ȭ��� ���� ���� ������ �ε����� �����մϴ�.
			int HpBarIndex = AllSortedTeamHpBars[i].m_Index;

			// ���ĵ� HP BAR�� �̵� ��ġ�� �������ݴϴ�.
			AllTeamHpBars[HpBarIndex]->InitMoveSortedHpbars(AllTeamHpBars[HpBarIndex]->GetPos(), AllTeamHpBarPos[i], 100.0f);

		}
	//}

}


void UI_Box_AllTeamHpBar::AddTeamHpBar()
{
	int AllPlayerCount = static_cast<int>(Player::GetAllPlayer().size());

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
		float4 initPos = { StartPos.X, StartPos.Y + 20 * PlayerIndex };
		AllTeamHpBars[PlayerIndex]->SetPos(initPos);

		// HP�� Sort�� ����� �ʱ� ��ġ�� �������ݴϴ�.
		AllTeamHpBarPos.push_back(initPos);


		int InitPlayerHp = Player::GetAllPlayer()[PlayerIndex]->GetHp();

		// �� HP���� Hp���� ������ �ʱ� Player���� Hp������ �ʱ�ȭ ���ݴϴ�.
		AllTeamHpBars[PlayerIndex]->SetMaxPlayerHp(InitPlayerHp);
		AllTeamHpBars[PlayerIndex]->SetCurPlayerHp(InitPlayerHp);

		AllSortedTeamHpBars.push_back({ AllTeamHpBars[PlayerIndex]->GetCurHpBarAmount(), PlayerIndex });

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

void UI_Box_AllTeamHpBar::SortTeamHpBar()
{



}
