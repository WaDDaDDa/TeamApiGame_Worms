#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Weapon.h"

class TargetEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	TargetEffect();
	~TargetEffect();

	// delete Function
	TargetEffect(const TargetEffect& _Other) = delete;
	TargetEffect(TargetEffect&& _Other) noexcept = delete;
	TargetEffect& operator=(const TargetEffect& _Other) = delete;
	TargetEffect& operator=(TargetEffect&& _Other) noexcept = delete;

	void SetMaster(class Player* _Player)
	{
		Master = _Player;
	}

protected:
	GameEngineRenderer* Renderer = nullptr;

private:
	Player* Master = nullptr;
	void Start() override;
	void LevelStart() override;
	void Update(float _Delta) override;

};

