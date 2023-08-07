#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_Box_Teams : public GameEngineActor
{
public:
	UI_Box_Teams();
	~UI_Box_Teams();

	UI_Box_Teams(const UI_Box_Teams& _Other) = delete;
	UI_Box_Teams(UI_Box_Teams&& _Other) noexcept = delete;
	UI_Box_Teams& operator=(const UI_Box_Teams& _Other) = delete;
	UI_Box_Teams& operator=(UI_Box_Teams&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* MainRenderer = nullptr;

};

