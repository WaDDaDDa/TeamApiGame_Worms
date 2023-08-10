#pragma once
#include <string>
#include <GameEngineCore/GameEngineActor.h>

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

protected:
	void Start() override;
	void Update(float _Delta) override;
	
private:



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

	//�������� �̸��� .bmp�� ����. 
	std::string StageName			= "MapBooks";
	float		m_fRoundTime		= 0.0f;
	float		m_fTurnTime			= 0.0f;
	int			m_iWinConditions	= 0;
	int			m_iWormMaxHp		= 0;
	int			m_iWormSelectMode	= 0;	// enum Ÿ������ �����ϴ� �� ����غ���
	bool		m_bUseTeleport		= false;

};

