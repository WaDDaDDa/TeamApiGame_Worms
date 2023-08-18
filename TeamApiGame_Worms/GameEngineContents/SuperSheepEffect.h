#pragma once
#include "BombEffect.h"

class SuperSheepEffect : public BombEffect
{
public:
	// constrcuter destructer
	SuperSheepEffect();
	~SuperSheepEffect();

	// delete Function
	SuperSheepEffect(const SuperSheepEffect& _Other) = delete;
	SuperSheepEffect(SuperSheepEffect&& _Other) noexcept = delete;
	SuperSheepEffect& operator=(const SuperSheepEffect& _Other) = delete;
	SuperSheepEffect& operator=(SuperSheepEffect&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;
};

