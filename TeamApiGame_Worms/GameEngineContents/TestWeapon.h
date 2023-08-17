#pragma once
#include "Weapon.h"

enum class TestWeaponState
{
	Idle,
	Fly,
	Bomb,
	Damage, //플레이어가 대미지입고 정리되는 단계
	Max,
};

class TestWeapon : public Weapon
{
public:
	// constrcuter destructer
	TestWeapon();
	~TestWeapon();

	// delete Function
	TestWeapon(const TestWeapon& _Other) = delete;
	TestWeapon(TestWeapon&& _Other) noexcept = delete;
	TestWeapon& operator=(const TestWeapon& _Other) = delete;
	TestWeapon& operator=(TestWeapon&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer = nullptr;

	GameEngineCollision* BombCollision = nullptr;

	void SetDir(float4& _DirPos)
	{
		Dir = _DirPos;
	}

protected:
	void ChangeState(TestWeaponState _State);
	void StateUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);
	void FlyStart();
	void FlyUpdate(float _Delta);
	void BombStart();
	void BombUpdate(float _Delta);
	void DamageStart();
	void DamageUpdate(float _Delta);
	void MaxStart();
	void MaxUpdate(float _Delta);

private:
	float TestWeaponDamage = 50.0f;
	float TestWeaponSpeed = 3000.0f;

	float4 TargetPos = float4::ZERO;
	float EffectTime = 0.0f;
	float EffectInterval = 0.05f;

	GameEngineCollision* BodyCollision = nullptr;

	float4 Dir = float4::ZERO;
	float4 GravityDir = float4::ZERO;
	float4 AngleVec = float4::RIGHT;

	TestWeaponState State = TestWeaponState::Max;

	class BombEffect* TestWeaponBomb = nullptr;

	void DirCheck();

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

