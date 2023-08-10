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

	
	
	//�������� �̸��� .bmp�� ����. 
	std::string StageName = "MapBooks";

private:

	GameStateManager();
	~GameStateManager();

	static GameStateManager GameState;

};

