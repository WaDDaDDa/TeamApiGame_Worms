#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "UI_Button.h"
#include <vector>

class UI_Box_Barracks;
class UI_Box_Teams : public UI_Button
{
	friend UI_Box_Barracks;

public:
	UI_Box_Teams();
	~UI_Box_Teams();

	UI_Box_Teams(const UI_Box_Teams& _Other) = delete;
	UI_Box_Teams(UI_Box_Teams&& _Other) noexcept = delete;
	UI_Box_Teams& operator=(const UI_Box_Teams& _Other) = delete;
	UI_Box_Teams& operator=(UI_Box_Teams&& _Other) noexcept = delete;

	void RemovePlayerTeam();
	void ChangePlayerTeamLayout(int _CurPlayerSelectIndex);

	void StateUpdate();
	void CheckButtonCollision();
	void CheckButtonClick();

	void ChangeState(BUTTON_STATE _ButtonState);

	int m_SelectIndex = 0;

	UI_Box_Teams* GetBoxTeamUI() const
	{
		return BoxTeamUI;
	}
	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:

	static UI_Box_Teams* BoxTeamUI;

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineCollision* MainCollision = nullptr;

	std::vector<GameEngineRenderer*> AllSelectedTeamRenderers;
	std::vector<float4> AllSelectedTeamRenderPos;
	
};

