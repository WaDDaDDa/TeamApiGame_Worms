#pragma once
#include "BombEffect.h"

class FlyEffect : public BombEffect
{
public:
	// constrcuter destructer
	FlyEffect();
	~FlyEffect();

	// delete Function
	FlyEffect(const FlyEffect& _Other) = delete;
	FlyEffect(FlyEffect&& _Other) noexcept = delete;
	FlyEffect& operator=(const FlyEffect& _Other) = delete;
	FlyEffect& operator=(FlyEffect&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;
};

