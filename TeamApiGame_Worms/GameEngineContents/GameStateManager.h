#pragma once
#include <string>
#include <GameEngineCore/GameEngineActor.h>
#include "GameTurn.h"

class GameStateManager : public GameEngineActor
{
public:
	static GameStateManager* GameState;

	static GameStateManager* GetGameStateManager()
	{
		return GameState;
	}

	GameStateManager();
	~GameStateManager();

	GameStateManager(const GameStateManager& _Other) = delete;
	GameStateManager(GameStateManager&& _Other) noexcept = delete;
	GameStateManager& operator=(const GameStateManager& _Other) = delete;
	GameStateManager& operator=(GameStateManager&& _Other) noexcept = delete;


	// Getter
	float GetRoundTime() const
	{
		return m_fRoundTime;
	}

	float GetTurnTime() const
	{
		return m_fTurnTime;
	}

	int GetWinConditions() const
	{
		return m_iWinConditions;
	}

	int GetWormMaxHp() const
	{
		return m_iWormMaxHp;
	}

	int GetWormSelectMode() const
	{
		return m_iWormSelectMode;
	}

	bool GetUseTeleport() const
	{
		return m_bUseTeleport;
	}

	std::string GetStageName() const
	{
		return StageName;
	}



	// Setter
	void SetRoundTime()
	{

	}

	void SetStageName(std::string _StageName)
	{
		StageName = _StageName;
	}

	void SetTurnTime(float _SetTurnPlayTime)
	{
		m_fTurnTime = _SetTurnPlayTime;
	}


protected:
	void Start() override;
	void Update(float _Delta) override;
	
private:

	GameTurn* Gameturn = nullptr;

	//스테이지 이름은 .bmp를 뺀다. 
	std::string StageName			= "MapBooks";
	float		m_fRoundTime		= 0.0f;
	float		m_fTurnTime			= 20.0f;
	int			m_iWinConditions	= 0;
	int			m_iWormMaxHp		= 0;
	int			m_iWormSelectMode	= 0;	// enum 타입으로 선언하는 거 고려해보기
	bool		m_bUseTeleport		= false;

};
