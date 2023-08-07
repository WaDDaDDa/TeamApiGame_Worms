#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_Box_SchemeOption : public GameEngineActor
{
public:
	UI_Box_SchemeOption();
	~UI_Box_SchemeOption();

	UI_Box_SchemeOption(const UI_Box_SchemeOption& _Other) = delete;
	UI_Box_SchemeOption(UI_Box_SchemeOption&& _Other) noexcept = delete;
	UI_Box_SchemeOption& operator=(const UI_Box_SchemeOption& _Other) = delete;
	UI_Box_SchemeOption& operator=(UI_Box_SchemeOption&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* MainRenderer = nullptr;

};


