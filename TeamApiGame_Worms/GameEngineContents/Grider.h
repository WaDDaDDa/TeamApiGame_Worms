
#pragma once
#include "Weapon.h"

enum class GridState
{
	s0,
	s1,
	s2,
	s3,
	s4,
	s5,
	s6,
	s7,
	s8,
	l0,
	l1,
	l2,
	l3,
	l4,
	l5,
	l6,
	l7,
	l8
	
};


class GameEngineRenderer;
class Grider : public Weapon
{
public:
	Grider();
	~Grider();

	Grider(const Grider& _Other) = delete;
	Grider(Grider&& _Other) noexcept = delete;
	Grider& operator=(const Grider& _Other) = delete;
	Grider& operator=(const Grider&& _Other) noexcept = delete;

	void GriderConstruct(GameEngineWindowTexture* _GroundTexture, GameEngineWindowTexture* _GroundPixelTexture);
protected:

private:
	void ChangeState(GridState _State);

	

	

	GameEngineRenderer* Renderer = nullptr;
	class GameEngineWindowTexture* PixelTexture = nullptr;

	GridState State = GridState::s0;

	void Start() override;
	void Update(float _Delta) override;
 
};

