#pragma once
#include "BombEffect.h"

// Ό³Έν : 
class ShotHit : public BombEffect
{
public:
	// constrcuter destructer
	ShotHit();
	~ShotHit();

	// delete Function
	ShotHit(const ShotHit & _Other) = delete;
	ShotHit(ShotHit && _Other) noexcept = delete;
	ShotHit& operator=(const ShotHit & _Other) = delete;
	ShotHit& operator=(ShotHit && _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;
};

