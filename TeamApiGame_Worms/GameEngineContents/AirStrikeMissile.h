#pragma once
#include "Weapon.h"

enum class AirStrikeMissileState
{
	Idle,
	Fly, // 처음 발사될때
	Bomb,
	Damage, //플레이어가 대미지입고 정리되는 단계
	InWater,
	Max,
};

class AirStrikeMissile : public Weapon
{
public:
	// constrcuter destructer
	AirStrikeMissile();
	~AirStrikeMissile();

	// delete Function
	AirStrikeMissile(const AirStrikeMissile& _Other) = delete;
	AirStrikeMissile(AirStrikeMissile&& _Other) noexcept = delete;
	AirStrikeMissile& operator=(const AirStrikeMissile& _Other) = delete;
	AirStrikeMissile& operator=(AirStrikeMissile&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer = nullptr;


	void SetDir(float4& _DirPos)
	{
		Dir = _DirPos;
	}

protected:
	void ChangeState(AirStrikeMissileState _State);
	void StateUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);
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
	float AirStrikeMissileDamage = 50.0f;
	float AirStrikeMissileSpeed = 3000.0f;
	float AirStrikeMissileRockOnSpeed = 1500.0f;
	float MissileDir = 0;

	float EffectTime = 0.0f;
	float EffectInterval = 0.04f;

	float4 TargetPos = float4::ZERO;

	float4 Dir = float4::ZERO;
	float4 GravityDir = float4::ZERO;
	float4 AngleVec = float4::RIGHT;

	AirStrikeMissileState State = AirStrikeMissileState::Max;
	static class Airjet* AirJet;
	class BombEffect* AirStrikeMissileBomb = nullptr;

	GameEngineCollision* BodyCollision = nullptr;
	static int CountValue;

	void DirCheck();

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

