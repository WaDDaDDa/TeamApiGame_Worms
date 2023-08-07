#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_Box_Barracks : public GameEngineActor
{
public:
	UI_Box_Barracks();
	~UI_Box_Barracks();

	UI_Box_Barracks(const UI_Box_Barracks& _Other) = delete;
	UI_Box_Barracks(UI_Box_Barracks&& _Other) noexcept = delete;
	UI_Box_Barracks& operator=(const UI_Box_Barracks& _Other) = delete;
	UI_Box_Barracks& operator=(UI_Box_Barracks&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* MainRenderer = nullptr;

};

