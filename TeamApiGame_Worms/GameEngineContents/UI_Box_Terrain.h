#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_Box_Terrain : public GameEngineActor
{
public:
	UI_Box_Terrain();
	~UI_Box_Terrain();

	UI_Box_Terrain(const UI_Box_Terrain& _Other) = delete;
	UI_Box_Terrain(UI_Box_Terrain&& _Other) noexcept = delete;
	UI_Box_Terrain& operator=(const UI_Box_Terrain& _Other) = delete;
	UI_Box_Terrain& operator=(UI_Box_Terrain&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* MainRenderer = nullptr;

};


