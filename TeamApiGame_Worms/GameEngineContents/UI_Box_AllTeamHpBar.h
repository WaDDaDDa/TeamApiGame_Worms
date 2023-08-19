#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
#include "UI_TeamHpBar.h"

class UI_Box_AllTeamHpBar : public GameEngineActor
{
public:
	UI_Box_AllTeamHpBar();
	~UI_Box_AllTeamHpBar();

	UI_Box_AllTeamHpBar(const UI_Box_AllTeamHpBar& _Other) = delete;
	UI_Box_AllTeamHpBar(UI_Box_AllTeamHpBar&& _Other) noexcept = delete;
	UI_Box_AllTeamHpBar& operator=(const UI_Box_AllTeamHpBar& _Other) = delete;
	UI_Box_AllTeamHpBar& operator=(UI_Box_AllTeamHpBar&& _Other) noexcept = delete;

	void AddTeamHpBar();
	void InitTeamHpBarData(int _Playerindex, int PlayerCurHp);
	void SortTeamHpBar();

	static UI_Box_AllTeamHpBar* GetAllTeamHpBarUI()
	{
		return AllTeamHpBarUI;
	}

	UI_TeamHpBar* GetIndexHpBarUI(int _Index)
	{
		return AllTeamHpBars[_Index];
	}

	class IndexedTeamHpBar
	{
	public:
		
		float GetTeamHp() const
		{
			return m_TeamHp;
		}

		float m_TeamHp;
		int m_Index;
	};

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	static UI_Box_AllTeamHpBar* AllTeamHpBarUI;



	std::vector<IndexedTeamHpBar> AllSortedTeamHpBars;


	std::vector<UI_TeamHpBar*> AllTeamHpBars;
	std::vector<float4> AllTeamHpBarPos;
	std::vector<int> AllTeamHpBarHpAmout;

	bool isEndAllHpBarSetting = false;

	bool startSort = false;

	GameEngineRenderer* CurHpDebugRenderer = nullptr;
	GameEngineRenderer* CurHpDebugRenderer2 = nullptr;
	GameEngineRenderer* CurHpDebugRenderer3 = nullptr;
	GameEngineRenderer* CurHpDebugRenderer4 = nullptr;
	GameEngineRenderer* CurHpDebugRenderer5 = nullptr;
	GameEngineRenderer* CurHpDebugRenderer6 = nullptr;

};

