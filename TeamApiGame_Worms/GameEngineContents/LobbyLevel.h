#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "UI_Terrain_Button.h"

class LobbyLevel : public GameEngineLevel
{
public:
	LobbyLevel();
	~LobbyLevel();

	LobbyLevel(const LobbyLevel& _Other) = delete;
	LobbyLevel(LobbyLevel&& _Other) noexcept = delete;
	LobbyLevel& operator=(const LobbyLevel& _Other) = delete;
	LobbyLevel& operator=(const LobbyLevel&& _Other) noexcept = delete;


protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	class GameStateManager* GameSetting = nullptr;

	float MeteorCreateTimer = 0.0f;

	UI_Terrain_Button* Btn_Terrain = nullptr;

};