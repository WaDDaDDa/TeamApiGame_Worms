#pragma once
#include "UI_Button.h"

class UI_RoundTime_Button : public UI_Button
{
public:
	UI_RoundTime_Button();
	~UI_RoundTime_Button();

	UI_RoundTime_Button(const UI_RoundTime_Button& _Other) = delete;
	UI_RoundTime_Button(UI_RoundTime_Button&& _Other) noexcept = delete;
	UI_RoundTime_Button& operator=(const UI_RoundTime_Button& _Other) = delete;
	UI_RoundTime_Button& operator=(UI_RoundTime_Button&& _Other) noexcept = delete;

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


