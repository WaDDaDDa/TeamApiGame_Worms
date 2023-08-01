#pragma once
#include "GravityActor.h"

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
	}

protected:
	Player* Master = nullptr;

private:

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

