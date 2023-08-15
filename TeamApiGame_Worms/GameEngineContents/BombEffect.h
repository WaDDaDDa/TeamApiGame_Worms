#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Weapon.h"

class BombEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	BombEffect();
	~BombEffect();

	// delete Function
	BombEffect(const BombEffect& _Other) = delete;
	BombEffect(BombEffect&& _Other) noexcept = delete;
	BombEffect& operator=(const BombEffect& _Other) = delete;
	BombEffect& operator=(BombEffect&& _Other) noexcept = delete;

	void SetBombRange(float4 _BombRange);

	void SetMaster(class Weapon* _CurWeapon)
	{
		Master = _CurWeapon;
		// 플레이어 랜더러 위치 옮긴만큼.
		SetPos(Master->GetPos());
	}

	class GameEngineRenderer* GetRenderer()
	{
		return Renderer;
	}

	void SetDamage(float _Damage)
	{
		BombDamage = _Damage;
	}

	float GetDamage()
	{
		return BombDamage;
	}

protected:
	class GameEngineCollision* BombCollision = nullptr;
	GameEngineRenderer* Renderer = nullptr;

	float4 BombRange = float4::ZERO;
	float BombDamage = 0.0f;

	Weapon* Master = nullptr;

private:
	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

