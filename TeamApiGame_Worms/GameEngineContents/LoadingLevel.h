#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "UI_LoadingCDRom.h"

class LoadingLevel : public GameEngineLevel
{
public:
	LoadingLevel();
	~LoadingLevel();

	LoadingLevel(const LoadingLevel& _Other) = delete;
	LoadingLevel(LoadingLevel&& _Other) noexcept = delete;
	LoadingLevel& operator=(const LoadingLevel& _Other) = delete;
	LoadingLevel& operator=(const LoadingLevel&& _Other) noexcept = delete;

	

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:

	UI_LoadingCDRom* LoadingUI = nullptr;

	void Start() override;
	void Update(float _Delta) override;

};

