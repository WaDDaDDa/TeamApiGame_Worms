#pragma once
#include "BombEffect.h"

class Range50 : public BombEffect
{
public:
	// constrcuter destructer
	Range50();
	~Range50();

	// delete Function
	Range50(const Range50& _Other) = delete;
	Range50(Range50&& _Other) noexcept = delete;
	Range50& operator=(const Range50& _Other) = delete;
	Range50& operator=(Range50&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

