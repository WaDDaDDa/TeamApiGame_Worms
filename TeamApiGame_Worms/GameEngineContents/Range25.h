#pragma once
#include "BombEffect.h"

class Range25 : public BombEffect
{
public:
	// constrcuter destructer
	Range25();
	~Range25();

	// delete Function
	Range25(const Range25& _Other) = delete;
	Range25(Range25&& _Other) noexcept = delete;
	Range25& operator=(const Range25& _Other) = delete;
	Range25& operator=(Range25&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

