#pragma once
#include "UI_Button.h"
#include <GameEnginePlatform/GameEngineSound.h>

class UI_Win_Button : public UI_Button
{
public:
	UI_Win_Button();
	~UI_Win_Button();

	UI_Win_Button(const UI_Win_Button& _Other) = delete;
	UI_Win_Button(UI_Win_Button&& _Other) noexcept = delete;
	UI_Win_Button& operator=(const UI_Win_Button& _Other) = delete;
	UI_Win_Button& operator=(UI_Win_Button&& _Other) noexcept = delete;

	int m_SelectIndex = 0;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

	void HighlighterOn();
	void HighlighterOff();

	void ChangeSelectValue();

	void StateUpdate();
	void CheckButtonCollision();
	void CheckButtonClick();

	void ChangeState(BUTTON_STATE _ButtonState);

	GameEngineSoundPlayer EFFECT_Player_Click;
};

