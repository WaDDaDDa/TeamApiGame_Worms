
#pragma once
#include <GameEngineCore/GameEngineActor.h>

class FrontWave :public GameEngineActor
{
public:
	FrontWave();
	~FrontWave();

	FrontWave(const FrontWave& _Other) = delete;
	FrontWave(FrontWave&& _Other) noexcept = delete;
	FrontWave& operator=(const FrontWave& _Other) = delete;
	FrontWave& operator=(const FrontWave&& _Other) noexcept = delete;


protected:

private:
	GameEngineRenderer* Renderer1 = nullptr;
	GameEngineRenderer* Renderer2 = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};

