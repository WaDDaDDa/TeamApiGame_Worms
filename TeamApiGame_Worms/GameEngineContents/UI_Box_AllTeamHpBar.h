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

	static UI_Box_AllTeamHpBar* GetAllTeamHpBarUI()
	{
		return AllTeamHpBarUI;
	}

	UI_TeamHpBar* GetIndexHpBarUI(int _Index)
	{
		return AllTeamHpBars[_Index];
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	static UI_Box_AllTeamHpBar* AllTeamHpBarUI;


	std::vector<UI_TeamHpBar*> AllTeamHpBars;
	bool isEndAllHpBarSetting = false;

};

