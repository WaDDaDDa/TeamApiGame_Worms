#pragma once
#include <string>

class GameStateManager
{
public:
	static GameStateManager& GetGameStateManager()
	{
		return GameState;
	}

	GameStateManager(const GameStateManager& _Other) = delete;
	GameStateManager(GameStateManager&& _Other) noexcept = delete;
	GameStateManager& operator=(const GameStateManager& _Other) = delete;
	GameStateManager& operator=(GameStateManager&& _Other) noexcept = delete;

	
	
	//스테이지 이름은 .bmp를 뺀다. 
	std::string StageName = "MapBooks";

private:

	GameStateManager();
	~GameStateManager();

	static GameStateManager GameState;

};

