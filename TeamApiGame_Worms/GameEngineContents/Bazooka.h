#pragma once
#include "Weapon.h"

class Bazooka : public Weapon
{
public:
	// constrcuter destructer
	Bazooka();
	~Bazooka();

	// delete Function
	Bazooka(const Bazooka& _Other) = delete;
	Bazooka(Bazooka&& _Other) noexcept = delete;
	Bazooka& operator=(const Bazooka& _Other) = delete;
	Bazooka& operator=(Bazooka&& _Other) noexcept = delete;

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

