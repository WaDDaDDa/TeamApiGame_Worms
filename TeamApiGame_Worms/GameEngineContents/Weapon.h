#pragma once
#include "GravityActor.h"
#include "Player.h"

// 설명 : 
class Weapon : public GravityActor
{
public:
	// constrcuter destructer
	Weapon();
	~Weapon();

	// delete Function
	Weapon(const Weapon & _Other) = delete;
	Weapon(Weapon && _Other) noexcept = delete;
	Weapon& operator=(const Weapon & _Other) = delete;
	Weapon& operator=(Weapon && _Other) noexcept = delete;

	void SetMaster(class Player* _CurPlayer)
	{
		Master = _CurPlayer;
		// 플레이어 랜더러 위치 옮긴만큼.
		SetPos(Master->GetPos() + float4{0, -15});
	}

	template <typename EffectType>
	EffectType* CreateBombEffect()
	{
		class BombEffect* NewEffect = GetLevel()->CreateActor<EffectType>();
		NewEffect->SetMaster(this);
		NewEffect->SetDamage(WeaponDamage);
		NewEffect->SetGroundTexture(GetGroundTexture());
		return dynamic_cast<EffectType*>(NewEffect);
	}

	template <typename EffectType>
	EffectType* CreateBombEffect(float4 _Pos)
	{
		EffectType* NewEffect = CreateBombEffect<EffectType>();
		NewEffect->AddPos(_Pos);
		return NewEffect;
	}

	void SetWeaponDamage(float _Value)
	{
		WeaponDamage = _Value;
	}

	void SetWeaponSpeed(float _Value)
	{
		WeaponSpeed = _Value;
	}

	void SetChargingSpeed(float _ChargeRatio)
	{
		WeaponChargeSpeed = WeaponSpeed * _ChargeRatio;
	}

	float GetChargingSpeed()
	{
		return WeaponChargeSpeed;
	}

protected:
	Player* Master = nullptr;

	// 무기의 대미지
	float WeaponDamage = 0.0f;

	// 무기의 고유의 날라가는 세기
	float WeaponSpeed = 0.0f;

	// 플레이어의 키다운 시간과 무기 고유의 날라가는 세기가 계산된 크기
	float WeaponChargeSpeed = 0.0f;

private:

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

