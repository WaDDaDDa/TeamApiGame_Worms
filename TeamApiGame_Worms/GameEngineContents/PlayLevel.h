
#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class PlayLevel :public GameEngineLevel
{
public:
	PlayLevel();
	~PlayLevel();

	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(const PlayLevel&& _Other) noexcept = delete;


protected:

private:
	class BackGround* BackGroundPtr=nullptr;
	void Start() override;
	void Update(float _Delta) override;
	

};
