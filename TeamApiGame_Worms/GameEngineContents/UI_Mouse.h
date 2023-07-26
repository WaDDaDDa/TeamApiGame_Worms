#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_Mouse : public GameEngineActor
{
public:
	UI_Mouse();
	~UI_Mouse();

	UI_Mouse(const UI_Mouse& _Other) = delete;
	UI_Mouse(UI_Mouse&& _Other) noexcept = delete;
	UI_Mouse& operator=(const UI_Mouse& _Other) = delete;
	UI_Mouse& operator=(UI_Mouse&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineCollision* MainCollision = nullptr;

};

