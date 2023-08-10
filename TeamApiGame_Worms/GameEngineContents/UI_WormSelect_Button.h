#pragma once
#include "UI_Button.h"

class UI_WormSelect_Button : public UI_Button
{
public:
	UI_WormSelect_Button();
	~UI_WormSelect_Button();

	UI_WormSelect_Button(const UI_WormSelect_Button& _Other) = delete;
	UI_WormSelect_Button(UI_WormSelect_Button&& _Other) noexcept = delete;
	UI_WormSelect_Button& operator=(const UI_WormSelect_Button& _Other) = delete;
	UI_WormSelect_Button& operator=(UI_WormSelect_Button&& _Other) noexcept = delete;

	int m_SelectIndex = 0;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void ChangeSelectValue();

	void StateUpdate();
	void CheckButtonCollision();
	void CheckButtonClick();

	void ChangeState(BUTTON_STATE _ButtonState);



};