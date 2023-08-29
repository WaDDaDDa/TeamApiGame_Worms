#pragma once
#include "UI_Button.h"
#include <GameEnginePlatform/GameEngineSound.h>

class UI_WormMaxHp_Button : public UI_Button
{
public:
	UI_WormMaxHp_Button();
	~UI_WormMaxHp_Button();

	UI_WormMaxHp_Button(const UI_WormMaxHp_Button& _Other) = delete;
	UI_WormMaxHp_Button(UI_WormMaxHp_Button&& _Other) noexcept = delete;
	UI_WormMaxHp_Button& operator=(const UI_WormMaxHp_Button& _Other) = delete;
	UI_WormMaxHp_Button& operator=(UI_WormMaxHp_Button&& _Other) noexcept = delete;

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