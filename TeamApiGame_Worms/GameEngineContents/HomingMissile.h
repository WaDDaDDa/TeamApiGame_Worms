#pragma once
#include "Weapon.h"

enum class HomingMissileState
{
	Fly, // 처음 발사될때
	RockOnFly, // 타겟을 향해 날라갈때
	Bomb,
	Damage, //플레이어가 대미지입고 정리되는 단계
	Max,
};

class HomingMissile : public Weapon
{
public:
	// constrcuter destructer
	HomingMissile();
	~HomingMissile();

	// delete Function
	HomingMissile(const HomingMissile& _Other) = delete;
	HomingMissile(HomingMissile&& _Other) noexcept = delete;
	HomingMissile& operator=(const HomingMissile& _Other) = delete;
	HomingMissile& operator=(HomingMissile&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer = nullptr;

	GameEngineCollision* BombCollision = nullptr;

	void SetDir(float4& _DirPos)
	{
		Dir = _DirPos;
	}

protected:
	void ChangeState(HomingMissileState _State);
	void StateUpdate(float _Delta);

	void FlyStart();
	void FlyUpdate(float _Delta);
	void RockOnFlyStart();
	void RockOnFlyUpdate(float _Delta);
	void BombStart();
	void BombUpdate(float _Delta);
	void DamageStart();
	void DamageUpdate(float _Delta);
	void MaxStart();
	void MaxUpdate(float _Delta);

private:
	int HomingMissileDamage = 50;
	float HomingMissileSpeed = 3000.0f;
	float HomingMissileRockOnSpeed = 1500.0f;
	float MissileDir = 0;

	float EffectTime = 0.0f;
	float EffectInterval = 0.02f;

	float4 TargetPos = float4::ZERO;

	float4 Dir = float4::ZERO;
	float4 GravityDir = float4::ZERO;
	float4 AngleVec = float4::RIGHT;

	HomingMissileState State = HomingMissileState::Max;

	class BombEffect* HomingMissileBomb = nullptr;

	void DirCheck();

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

