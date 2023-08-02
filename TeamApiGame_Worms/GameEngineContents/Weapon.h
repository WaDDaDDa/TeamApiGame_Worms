#pragma once
#include "GravityActor.h"
#include "Player.h"

// Ό³Έν : 
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
		SetPos(Master->GetPos() + float4{0, -15});
	}

protected:
	Player* Master = nullptr;

private:

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

