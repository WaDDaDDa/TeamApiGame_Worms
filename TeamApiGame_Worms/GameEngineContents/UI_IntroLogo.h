#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_IntroLogo : public GameEngineActor
{
public:
	UI_IntroLogo();
	~UI_IntroLogo();

	UI_IntroLogo(const UI_IntroLogo& _Other) = delete;
	UI_IntroLogo(UI_IntroLogo&& _Other) noexcept = delete;
	UI_IntroLogo& operator=(const UI_IntroLogo& _Other) = delete;
	UI_IntroLogo& operator=(UI_IntroLogo&& _Other) noexcept = delete;
	
	void ChangeState_Black();
	void ChangeState_Main_Back();
	void ChangeState_Main();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* MainRenderer = nullptr;
};