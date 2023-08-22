
#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BackWave :public GameEngineActor
{
public:
	BackWave();
	~BackWave();

	BackWave(const BackWave& _Other) = delete;
	BackWave(BackWave&& _Other) noexcept = delete;
	BackWave& operator=(const BackWave& _Other) = delete;
	BackWave& operator=(const BackWave&& _Other) noexcept = delete;


protected:

private:
	GameEngineRenderer* Renderer1= nullptr;
	GameEngineRenderer* Renderer2= nullptr;

	void Start() override;
	void Update(float _Delta) override;
};

