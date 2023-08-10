#include "GameStateManager.h"

GameStateManager* GameStateManager::GameState = nullptr;

GameStateManager::GameStateManager()
{

}

GameStateManager::~GameStateManager()
{

}

void GameStateManager::Start()
{
	GameState = this;
}

void GameStateManager::Update(float _Delta)
{

}