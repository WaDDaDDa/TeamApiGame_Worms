#pragma once
#include "Weapon.h"

enum class BazookaState
{
	Fly,
	Bomb,
	Max,
};

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

	GameEngineCollision* BombCollision = nullptr;

	void SetDir(float4& _DirPos)
	{
		Dir = _DirPos;
	}

protected:
	void ChangeState(BazookaState _State);
	void StateUpdate(float _Delta);

	void FlyStart();
	void FlyUpdate(float _Delta);
	void BombStart();
	void BombUpdate(float _Delta);
	void MaxStart();
	void MaxUpdate(float _Delta);

private:
	float Speed = 200.0f;
	float4 Dir = float4::ZERO;
	float4 GravityDir = float4::ZERO;
	float4 AngleVec = float4::RIGHT;

	BazookaState State = BazookaState::Max;


	void DirCheck();

	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

