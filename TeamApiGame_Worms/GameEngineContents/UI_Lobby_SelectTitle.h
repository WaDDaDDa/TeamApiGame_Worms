#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_Lobby_SelectTitle : public GameEngineActor
{
public:
	UI_Lobby_SelectTitle();
	~UI_Lobby_SelectTitle();

	UI_Lobby_SelectTitle(const UI_Lobby_SelectTitle& _Other) = delete;
	UI_Lobby_SelectTitle(UI_Lobby_SelectTitle&& _Other) noexcept = delete;
	UI_Lobby_SelectTitle& operator=(const UI_Lobby_SelectTitle& _Other) = delete;
	UI_Lobby_SelectTitle& operator=(UI_Lobby_SelectTitle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* MainRenderer = nullptr;

};

