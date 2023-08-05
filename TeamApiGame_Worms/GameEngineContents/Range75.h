#pragma once
#include "BombEffect.h"

class Range75 : public BombEffect
{
public:
	// constrcuter destructer
	Range75();
	~Range75();

	// delete Function
	Range75(const Range75& _Other) = delete;
	Range75(Range75&& _Other) noexcept = delete;
	Range75& operator=(const Range75& _Other) = delete;
	Range75& operator=(Range75&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

