#pragma once
#include "Weapon.h"

enum class DonkeyState
{
	Idle,
	Fly,
	Jump,
	Bomb,
	Damage, //플레이어가 대미지입고 정리되는 단계
	Max,
};

class Donkey : public Weapon
{
public:
	// constrcuter destructer
	Donkey();
	~Donkey();

	// delete Function
	Donkey(const Donkey& _Other) = delete;
	Donkey(Donkey&& _Other) noexcept = delete;
	Donkey& operator=(const Donkey& _Other) = delete;
	Donkey& operator=(Donkey&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer = nullptr;

	void SetDir(float4& _DirPos)
	{
		Dir = _DirPos;
	}

protected:
	void ChangeState(DonkeyState _State);
	void StateUpdate(float _Delta);


	void IdleStart();
	void IdleUpdate(float _Delta);

	void FlyStart();
	void FlyUpdate(float _Delta);

	void JumpStart();
	void JumpUpdate(float _Delta);

	void BombStart();
	void BombUpdate(float _Delta);
	void DamageStart();
	void DamageUpdate(float _Delta);
	void MaxStart();
	void MaxUpdate(float _Delta);

private:
	float DonkeyDamage = 80.0f;
	float DonkeySpeed = 600.0f;
	
	float4 Dir = float4::ZERO;
	float4 GravityDir = float4::ZERO;
	float4 AngleVec = float4::RIGHT;
	float4 TargetPos = float4::ZERO;

	DonkeyState State = DonkeyState::Max;

	class BombEffect* DonkeyBomb = nullptr;

	GameEngineCollision* BodyCollision = nullptr;

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

