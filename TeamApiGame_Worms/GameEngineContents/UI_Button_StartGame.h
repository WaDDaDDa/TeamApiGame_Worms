#pragma once
#include "UI_Button.h"
class UI_Button_StartGame : public UI_Button
{
public:
	UI_Button_StartGame();
	~UI_Button_StartGame();

	UI_Button_StartGame(const UI_Button_StartGame& _Other) = delete;
	UI_Button_StartGame(UI_Button_StartGame&& _Other) noexcept = delete;
	UI_Button_StartGame& operator=(const UI_Button_StartGame& _Other) = delete;
	UI_Button_StartGame& operator=(UI_Button_StartGame&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void OnClickEvent();

	//GameEngineRenderer* ButtonRenderer;
	//GameEngineCollision* ButtonCollision;
};