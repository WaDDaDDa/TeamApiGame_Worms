#pragma once
#include "UI_Button.h"

class UI_Teleportin_Button : public UI_Button
{
public:
	UI_Teleportin_Button();
	~UI_Teleportin_Button();

	UI_Teleportin_Button(const UI_Teleportin_Button& _Other) = delete;
	UI_Teleportin_Button(UI_Teleportin_Button&& _Other) noexcept = delete;
	UI_Teleportin_Button& operator=(const UI_Teleportin_Button& _Other) = delete;
	UI_Teleportin_Button& operator=(UI_Teleportin_Button&& _Other) noexcept = delete;

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