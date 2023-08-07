#pragma once
#include "Weapon.h"

enum class GrenadeState
{
	Idle,
	Fly,
	Bomb,
	Damage, //플레이어가 대미지입고 정리되는 단계
	Max,
};

class Grenade : public Weapon
{
public:
	// constrcuter destructer
	Grenade();
	~Grenade();

	// delete Function
	Grenade(const Grenade& _Other) = delete;
	Grenade(Grenade&& _Other) noexcept = delete;
	Grenade& operator=(const Grenade& _Other) = delete;
	Grenade& operator=(Grenade&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer = nullptr;

	GameEngineCollision* BombCollision = nullptr;

	void SetDir(float4& _DirPos)
	{
		Dir = _DirPos;
	}

protected:
	void ChangeState(GrenadeState _State);
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
	int GrenadeDamage = 50;
	float GrenadeSpeed = 3000.0f;

	float4 Dir = float4::ZERO;
	float4 GravityDir = float4::ZERO;
	float4 AngleVec = float4::RIGHT;

	GrenadeState State = GrenadeState::Max;

	class BombEffect* GrenadeBomb = nullptr;

	void DirCheck();

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

