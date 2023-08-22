#pragma once
#include "UI_Button.h"
#include <vector>

class UI_Box_Teams;
class UI_Box_Barracks : public UI_Button
{
	friend UI_Box_Teams;

public:
	UI_Box_Barracks();
	~UI_Box_Barracks();

	UI_Box_Barracks(const UI_Box_Barracks& _Other) = delete;
	UI_Box_Barracks(UI_Box_Barracks&& _Other) noexcept = delete;
	UI_Box_Barracks& operator=(const UI_Box_Barracks& _Other) = delete;
	UI_Box_Barracks& operator=(UI_Box_Barracks&& _Other) noexcept = delete;

	void AddPlayerTeam();
	void ChangePlayerTeamLayout(int _CurPlayerSelectIndex);

	void StateUpdate();
	void CheckButtonCollision();
	void CheckButtonClick();

	void ChangeState(BUTTON_STATE _ButtonState);

	UI_Box_Barracks* GetBoxBarracks() const
	{
		return BoxBarracksUI;
	}

	int m_SelectIndex = 0;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

	static UI_Box_Barracks* BoxBarracksUI;

	std::vector<GameEngineRenderer*> AllTeamRenderers;
	std::vector<float4> AllTeamRenderPos;

	GameEngineCollision* MainCollision = nullptr;

	GameEngineRenderer* MainRenderer = nullptr;

};

