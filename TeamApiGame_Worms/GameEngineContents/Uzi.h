#pragma once
#include "Weapon.h"

enum class UziState
{
	Fly,
	Bomb,
	Damage, //플레이어가 대미지입고 정리되는 단계
	Max,
};

class Uzi : public Weapon
{
public:
	// constrcuter destructer
	Uzi();
	~Uzi();

	// delete Function
	Uzi(const Uzi& _Other) = delete;
	Uzi(Uzi&& _Other) noexcept = delete;
	Uzi& operator=(const Uzi& _Other) = delete;
	Uzi& operator=(Uzi&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer = nullptr;

	void SetDir(float4& _DirPos)
	{
		Dir = _DirPos;
	}

protected:
	void ChangeState(UziState _State);
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
	int UziDamage = 50;
	float UziSpeed = 2000.0f;

	float4 Dir = float4::ZERO;
	float4 GravityDir = float4::ZERO;
	float4 AngleVec = float4::RIGHT;

	UziState State = UziState::Max;

	class BombEffect* UziBomb = nullptr;

	GameEngineCollision* BodyCollision = nullptr;

	void DirCheck();

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

