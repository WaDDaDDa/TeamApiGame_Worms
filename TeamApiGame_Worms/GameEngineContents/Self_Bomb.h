#pragma once
#include "Weapon.h"

enum class Self_BombState
{
	Fly,
	Bomb,
	Damage, //플레이어가 대미지입고 정리되는 단계
	Max,
};

class Self_Bomb : public Weapon
{
public:
	// constrcuter destructer
	Self_Bomb();
	~Self_Bomb();

	// delete Function
	Self_Bomb(const Self_Bomb& _Other) = delete;
	Self_Bomb(Self_Bomb&& _Other) noexcept = delete;
	Self_Bomb& operator=(const Self_Bomb& _Other) = delete;
	Self_Bomb& operator=(Self_Bomb&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer = nullptr;

	void SetDir(float4& _DirPos)
	{
		Dir = _DirPos;
	}

protected:
	void ChangeState(Self_BombState _State);
	void StateUpdate(float _Delta);

	void FlyStart();
	void FlyUpdate(float _Delta);
	void BombStart();
	void BombUpdate(float _Delta);
	void DamageStart();
	void DamageUpdate(float _Delta);
	void MaxStart();
	void MaxUpdate(float _Delta);

	void CameraFocus(float _Delta) override;


private:
	float Self_BombDamage = 30.0f;
	float Self_BombSpeed = 2000.0f;

	float4 Dir = float4::ZERO;
	float4 GravityDir = float4::ZERO;
	float4 AngleVec = float4::RIGHT;

	Self_BombState State = Self_BombState::Max;

	class BombEffect* Self_BombBomb = nullptr;

	GameEngineCollision* BodyCollision = nullptr;

	void DirCheck();

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

