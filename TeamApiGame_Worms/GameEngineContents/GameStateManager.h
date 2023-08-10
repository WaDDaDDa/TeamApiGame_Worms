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

		

	// Setter
	// �Ű������� enum�� �޴°� �� ���� ����
	void SetRoundTime()
	{
	
	}






	//class GameSettingData
	//{
	float	m_fRoundTime = 0.0f;
	float	m_fTurnTime = 0.0f;
	int		m_iWinConditions = 0;
	int		m_iWormMaxHp = 0;
	int		m_iWormSelectMode = 0;	// enum Ÿ������ �����ϴ� �� ����غ���
	bool	m_bUseTeleport = false;
	//};

};

