#pragma once
#include "Weapon.h"

enum class SheepState
{
	Idle,
	Fly,
	Jump,
	Bomb,
	Damage, //플레이어가 대미지입고 정리되는 단계
	InWater,
	Max,
};

enum class SheepDir
{
	Right,
	Left,
	Max,
};

class Sheep : public Weapon
{
public:
	// constrcuter destructer
	Sheep();
	~Sheep();

	// delete Function
	Sheep(const Sheep& _Other) = delete;
	Sheep(Sheep&& _Other) noexcept = delete;
	Sheep& operator=(const Sheep& _Other) = delete;
	Sheep& operator=(Sheep&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer = nullptr;

	void SetDir(float4& _DirPos)
	{
		Dir = _DirPos;
	}

	void Movement(float _Delta);

protected:
	void ChangeState(SheepState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);


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
	void InWaterStart();
	void InWaterUpdate(float _Delta);
	void MaxStart();
	void MaxUpdate(float _Delta);

private:
	float SheepDamage = 80.0f;
	float SheepSpeed = 200.0f;
	float SheepJumpPower = 600.0f;

	float4 CheckPos = float4::ZERO;

	// Move 중 벽을 판정해서 막히는 지점
	float4 LeftCheckPos = float4{ -30.0f, -20.0f };
	float4 RightCheckPos = float4{ 30.0f, -20.0f };
	float4 UpCheckPos = float4{ 0 , -20.0f };

	float4 Dir = float4::ZERO;
	SheepDir DirState = SheepDir::Max;
	float4 GravityDir = float4::ZERO;
	float4 AngleVec = float4::RIGHT;

	SheepState State = SheepState::Max;
	std::string CurState = "";

	class BombEffect* SheepBomb = nullptr;

	//void DirCheck();

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

