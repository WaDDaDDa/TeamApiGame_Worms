
#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BackLand : public GameEngineActor
{
public:
	BackLand();
	~BackLand();

	BackLand(const BackLand& _Other) = delete;
	BackLand(BackLand&& _Other) noexcept = delete;
	BackLand& operator=(const BackLand& _Other) = delete;
	BackLand& operator=(const BackLand&& _Other) noexcept = delete;


protected:
	

private:
	float4 BasicPos = float4::ZERO;

	void Start() override;
	void Update(float _Delta);
};

