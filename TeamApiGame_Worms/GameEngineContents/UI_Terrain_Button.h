#pragma once
#include "UI_Button.h"

class UI_Terrain_Button : public UI_Button
{
public:
	UI_Terrain_Button();
	~UI_Terrain_Button();

	UI_Terrain_Button(const UI_Terrain_Button& _Other) = delete;
	UI_Terrain_Button(UI_Terrain_Button&& _Other) noexcept = delete;
	UI_Terrain_Button& operator=(const UI_Terrain_Button& _Other) = delete;
	UI_Terrain_Button& operator=(UI_Terrain_Button&& _Other) noexcept = delete;

	

	GameEngineRenderer* GetMainRenderer()
	{
		return MainRenderer;
	}

	int m_SelectIndex = 0;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void ChangeSelectMap();

	void StateUpdate();
	void CheckButtonCollision();
	void CheckButtonClick();
	
	void ChangeState(BUTTON_STATE _ButtonState);

private:

};

