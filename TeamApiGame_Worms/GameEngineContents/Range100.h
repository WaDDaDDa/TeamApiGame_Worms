#pragma once
#include "BombEffect.h"

class Range100 : public BombEffect
{
public:
	// constrcuter destructer
	Range100();
	~Range100();

	// delete Function
	Range100(const Range100& _Other) = delete;
	Range100(Range100&& _Other) noexcept = delete;
	Range100& operator=(const Range100& _Other) = delete;
	Range100& operator=(Range100&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

