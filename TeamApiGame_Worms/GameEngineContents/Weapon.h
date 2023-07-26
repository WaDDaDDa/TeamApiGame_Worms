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

	class GameEngineRenderer* Renderer;

	void SetDir(float4& _DirPos)
	{
		Dir = _DirPos;
	}

protected:

private:
	float Speed = 200.0f;
	float4 Dir = float4::ZERO;
	float4 GravityDir = float4::ZERO;

	void Start() override;
	void Update(float _Delta) override;

};

