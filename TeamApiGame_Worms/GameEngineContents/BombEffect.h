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
		// �÷��̾� ������ ��ġ �ű丸ŭ.
		SetPos(Master->GetPos());
	}

protected:
	class GameEngineRenderer* Renderer = nullptr;
	class GameEngineCollision* BombCollision = nullptr;

	float4 BombRange = float4::ZERO;

	Weapon* Master = nullptr;

private:
	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

