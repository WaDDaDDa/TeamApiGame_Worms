#pragma once
#include "Weapon.h"

enum class BazookaState
{
	Fly,
	Bomb,
	Damage, //플레이어가 대미지입고 정리되는 단계
	InWater,
	Max,
};

class Bazooka : public Weapon
{
public:
	// constrcuter destructer
	Bazooka();
	~Bazooka();

	// delete Function
	Bazooka(const Bazooka& _Other) = delete;
	Bazooka(Bazooka&& _Other) noexcept = delete;
	Bazooka& operator=(const Bazooka& _Other) = delete;
	Bazooka& operator=(Bazooka&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer = nullptr;

	GameEngineCollision* BombCollision = nullptr;

	void SetDir(float4& _DirPos)
	{
		Dir = _DirPos;
	}

protected:
	void ChangeState(BazookaState _State);
	void StateUpdate(float _Delta);

	void FlyStart();
	void FlyUpdate(float _Delta);
	void BombStart();
	void BombUpdate(float _Delta);
	void DamageStart();
	void DamageUpdate(float _Delta);
	void InWaterStart();
	void InWaterUpdate(float _Delta);
	void MaxStart();
	void MaxUpdate(float _Delta);

private:
	float BazookaDamage = 50.0f;
	float BazookaSpeed = 3000.0f;

	float EffectTime = 0.0f;
	float EffectInterval = 0.05f;

	GameEngineCollision* BodyCollision = nullptr;

	float4 Dir = float4::ZERO;
	float4 GravityDir = float4::ZERO;
	float4 AngleVec = float4::RIGHT;

	BazookaState State = BazookaState::Max;

	class BombEffect* BazookaBomb = nullptr;

	void DirCheck();

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

