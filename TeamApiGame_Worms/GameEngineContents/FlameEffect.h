#pragma once
#include "BombEffect.h"

enum class FlameEffectState
{
	Fly,
	Fire,
	Damage, //플레이어가 대미지입고 정리되는 단계
	Max,
};

class FlameEffect : public BombEffect
{
public:
	// constrcuter destructer
	FlameEffect();
	~FlameEffect();

	// delete Function
	FlameEffect(const FlameEffect& _Other) = delete;
	FlameEffect(FlameEffect&& _Other) noexcept = delete;
	FlameEffect& operator=(const FlameEffect& _Other) = delete;
	FlameEffect& operator=(FlameEffect&& _Other) noexcept = delete;

protected:
	void ChangeState(FlameEffectState _State);
	void StateUpdate(float _Delta);

	void FlyStart();
	void FlyUpdate(float _Delta);
	void FireStart();
	void FireUpdate(float _Delta);
	void MaxStart();
	void MaxUpdate(float _Delta);

private:
	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

	FlameEffectState State = FlameEffectState::Max;
};

