#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <vector>

class LobbyLevel :public GameEngineLevel
{
public:
	LobbyLevel();
	~LobbyLevel();

	LobbyLevel(const LobbyLevel& _Other) = delete;
	LobbyLevel(LobbyLevel&& _Other) noexcept = delete;
	LobbyLevel& operator=(const LobbyLevel& _Other) = delete;
	LobbyLevel& operator=(const LobbyLevel&& _Other) noexcept = delete;

	void SetSelectOver()
	{
		IsSelectOver = true;
	}

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	bool IsSelectOver = false;

	void EnterLobby(DWORD_PTR, DWORD_PTR);

	std::vector<GameEngineActor*> AllSelectModeActor;

	float MeteorCreateTimer = 0.0f;

};