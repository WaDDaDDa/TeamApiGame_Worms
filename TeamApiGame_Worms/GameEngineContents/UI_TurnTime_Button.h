#pragma once
#include "UI_Button.h"

class UI_TurnTime_Button : public UI_Button
{
public:
	UI_TurnTime_Button();
	~UI_TurnTime_Button();

	UI_TurnTime_Button(const UI_TurnTime_Button& _Other) = delete;
	UI_TurnTime_Button(UI_TurnTime_Button&& _Other) noexcept = delete;
	UI_TurnTime_Button& operator=(const UI_TurnTime_Button& _Other) = delete;
	UI_TurnTime_Button& operator=(UI_TurnTime_Button&& _Other) noexcept = delete;

	int m_SelectIndex = 0;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void ChangeSelectValue();

	void StateUpdate();
	void CheckButtonCollision();
	void CheckButtonClick();

	void ChangeState(BUTTON_STATE _ButtonState);

private:
};

