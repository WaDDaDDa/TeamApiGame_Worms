#pragma once
#include "GravityActor.h"
#include "Player.h"

// ���� : 
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
		// �÷��̾� ������ ��ġ �ű丸ŭ.
		SetPos(Master->GetPos() + float4{0, -15});
	}

	template <typename EffectType>
	EffectType* CreateBombEffect()
	{
		class BombEffect* NewEffect = GetLevel()->CreateActor<EffectType>();
		NewEffect->SetMaster(this);
		return dynamic_cast<EffectType*>(NewEffect);
	}

	void SetWeaponDamage(int _Value)
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

	// ������ �����
	int WeaponDamage = 0;

	// ������ ������ ���󰡴� ����
	float WeaponSpeed = 0.0f;

	// �÷��̾��� Ű�ٿ� �ð��� ���� ������ ���󰡴� ���Ⱑ ���� ũ��
	float WeaponChargeSpeed = 0.0f;

private:

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

