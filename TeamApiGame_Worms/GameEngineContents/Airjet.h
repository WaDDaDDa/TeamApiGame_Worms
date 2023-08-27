#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Weapon.h"

class Airjet : public GameEngineActor
{
public:
	// constrcuter destructer
	Airjet();
	~Airjet();

	// delete Function
	Airjet(const Airjet& _Other) = delete;
	Airjet(Airjet&& _Other) noexcept = delete;
	Airjet& operator=(const Airjet& _Other) = delete;
	Airjet& operator=(Airjet&& _Other) noexcept = delete;

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

