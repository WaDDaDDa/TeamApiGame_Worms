#pragma once

class GameStateManager
{

	static GameStateManager* GetGameStateManager()
	{
		return GameState;
	}



private:
	static GameStateManager* GameState;

};

