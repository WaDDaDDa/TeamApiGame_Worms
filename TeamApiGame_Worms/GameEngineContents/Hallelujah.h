#pragma once
#include "Weapon.h"

enum class HallelujahState
{
	Ready,
	Idle,
	Fly,
	PrevBomb,
	Bomb,
	Damage, //플레이어가 대미지입고 정리되는 단계
	InWater,
	Max,
};

class Hallelujah : public Weapon
{
public:
	// constrcuter destructer
	Hallelujah();
	~Hallelujah();

	// delete Function
	Hallelujah(const Hallelujah& _Other) = delete;
	Hallelujah(Hallelujah&& _Other) noexcept = delete;
	Hallelujah& operator=(const Hallelujah& _Other) = delete;
	Hallelujah& operator=(Hallelujah&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer = nullptr;

	void SetDir(float4& _DirPos)
	{
		Dir = _DirPos;
	}

	void GroundCheck(float _Delta) override;

protected:
	void ChangeState(HallelujahState _State);
	void StateUpdate(float _Delta);

	void ReadyStart();
	void ReadyUpdate(float _Delta);
	void IdleStart();
	void IdleUpdate(float _Delta);
	void FlyStart();
	void FlyUpdate(float _Delta);
	void PrevBombStart();
	void PrevBombUpdate(float _Delta);
	void BombStart();
	void BombUpdate(float _Delta);
	void DamageStart();
	void DamageUpdate(float _Delta);
	void InWaterStart();
	void InWaterUpdate(float _Delta);
	void MaxStart();
	void MaxUpdate(float _Delta);

private:
	float HallelujahDamage = 60.0f;
	float HallelujahSpeed = 3000.0f;

	// Move 중 벽을 판정해서 막히는 지점
	float4 LeftCheckPos = float4{ -5.0f, 0.0f };
	float4 RightCheckPos = float4{ 5.0f, 0.0f };
	float4 UpCheckPos = float4{ 0 , -10.0f };
	float4 DownCheckPos = float4{ 0 , 12.0f };

	float4 Dir = float4::ZERO;
	float4 GravityDir = float4::ZERO;
	float4 AngleVec = float4::RIGHT;

	HallelujahState State = HallelujahState::Max;

	class BombEffect* HallelujahBomb = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	void TongTong(float4 _Pos = float4::ZERO);

	void DirCheck();

	void Start() override;
	void Render(float _Delta) override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

