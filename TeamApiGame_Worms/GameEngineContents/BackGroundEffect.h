
#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BackGroundEffect : public GameEngineActor
{
public:
	BackGroundEffect();
	~BackGroundEffect();

	BackGroundEffect(const BackGroundEffect& _Other) = delete;
	BackGroundEffect(BackGroundEffect&& _Other) noexcept = delete;
	BackGroundEffect& operator=(const BackGroundEffect& _Other) = delete;
	BackGroundEffect& operator=(const BackGroundEffect&& _Other) noexcept = delete;


protected:

private:
	float4 Dir = float4::RIGHT;
	float4 WindCheck = float4::ZERO;
	float WindPower = 0.0f;
	float WindRatio = 0.0f;

	float DownPower = 0.0f;
	float HorizonPower = 0.0f;
	float4 HorizonVector = float4::ZERO;
	
	float4 BoomVector = float4::ZERO;
	float CurTime = 0.0f;
	
	class GameEngineCollision* Collision = nullptr;
	bool inBoom = false;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
};

