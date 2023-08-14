#include "UI_Box_AllTeamHpBar.h"
#include "UI_TeamHpBar.h"
#include <GameEngineCore/GameEngineLevel.h>

UI_Box_AllTeamHpBar::UI_Box_AllTeamHpBar()
{
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
	UI_TeamHpBar* TeamHpBar = GetLevel()->CreateActor<UI_TeamHpBar>();
	AllTeamHpBars.push_back(TeamHpBar);
}


