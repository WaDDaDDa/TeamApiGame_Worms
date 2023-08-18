#pragma once
#include "Weapon.h"

enum class SuperSheepState
{
	Idle,
	Fly,
	SuperFly,
	Jump,
	Bomb,
	Damage, //플레이어가 대미지입고 정리되는 단계
	Max,
};

enum class SuperSheepDir
{
	Right,
	Left,
	Max,
};

class SuperSheep : public Weapon
{
public:
	// constrcuter destructer
	SuperSheep();
	~SuperSheep();

	// delete Function
	SuperSheep(const SuperSheep& _Other) = delete;
	SuperSheep(SuperSheep&& _Other) noexcept = delete;
	SuperSheep& operator=(const SuperSheep& _Other) = delete;
	SuperSheep& operator=(SuperSheep&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer = nullptr;

	void SetDir(float4& _DirPos)
	{
		Dir = _DirPos;
	}

	void Movement(float _Delta);

protected:
	void ChangeState(SuperSheepState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void DirCheck();

	void IdleStart();
	void IdleUpdate(float _Delta);
	void FlyStart();
	void FlyUpdate(float _Delta);
	void SuperFlyStart();
	void SuperFlyUpdate(float _Delta);
	void JumpStart();
	void JumpUpdate(float _Delta);
	void BombStart();
	void BombUpdate(float _Delta);
	void DamageStart();
	void DamageUpdate(float _Delta);
	void MaxStart();
	void MaxUpdate(float _Delta);

	void RotateDir(float _Delta);


private:
	float SuperSheepDamage = 80.0f;
	float SuperSheepSpeed = 200.0f;
	float SuperSheepFlySpeed = 800.0f;
	float SuperSheepJumpPower = 600.0f;

	float4 CheckPos = float4::ZERO;

	// Move 중 벽을 판정해서 막히는 지점
	float4 LeftCheckPos = float4{ -30.0f, -20.0f };
	float4 RightCheckPos = float4{ 30.0f, -20.0f };
	float4 UpCheckPos = float4{ 0 , -20.0f };

	float4 Dir = float4::ZERO;
	SuperSheepDir DirState = SuperSheepDir::Max;
	float4 GravityDir = float4::ZERO;
	float4 AngleVec = float4::RIGHT;

	SuperSheepState State = SuperSheepState::Max;
	std::string CurState = "";

	class BombEffect* SuperSheepBomb = nullptr;

	float EffectTime = 0.0f;
	float EffectInterval = 0.05f;

	bool AniInter = false;
	float InterCheck = 0.0f;

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

