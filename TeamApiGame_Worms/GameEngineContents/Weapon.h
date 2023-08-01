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

protected:

private:

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

