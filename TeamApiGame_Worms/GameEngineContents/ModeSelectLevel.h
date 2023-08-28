#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>



class ModeSelectLevel : public GameEngineLevel
{
public:
	ModeSelectLevel();
	~ModeSelectLevel();

	ModeSelectLevel(const ModeSelectLevel& _Other) = delete;
	ModeSelectLevel(ModeSelectLevel&& _Other) noexcept = delete;
	ModeSelectLevel& operator=(const ModeSelectLevel& _Other) = delete;
	ModeSelectLevel& operator=(const ModeSelectLevel&& _Other) noexcept = delete;

	
	

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	class GameEngineSoundPlayer BGMPlayer;

	void Start() override;
	void Update(float _Delta) override;

	float MeteorCreateTimer = 0.0f;

};