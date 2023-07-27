
#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Ground;
class PlayLevel :public GameEngineLevel
{
public:
	PlayLevel();
	~PlayLevel();

	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(const PlayLevel&& _Other) noexcept = delete;

	Ground* GetGround() const;
	

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	Ground* GroundPtr=nullptr;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	

};

