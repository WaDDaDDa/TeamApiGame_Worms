
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
	

	void Start() override;
	void Update(float _Delta) override;

};

