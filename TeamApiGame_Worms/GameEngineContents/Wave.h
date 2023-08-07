
#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Wave :public GameEngineActor
{
public:
	Wave();
	~Wave();

	Wave(const Wave& _Other) = delete;
	Wave(Wave&& _Other) noexcept = delete;
	Wave& operator=(const Wave& _Other) = delete;
	Wave& operator=(const Wave&& _Other) noexcept = delete;


protected:

private:
	GameEngineRenderer* Renderer1= nullptr;
	GameEngineRenderer* Renderer2= nullptr;

	void Start() override;
	void Update(float _Delta) override;
};

