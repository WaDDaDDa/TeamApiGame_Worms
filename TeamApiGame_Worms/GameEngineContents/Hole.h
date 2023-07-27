
#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Hole : public GameEngineActor
{
public:
	Hole();
	~Hole();

	Hole(const Hole& _Other) = delete;
	Hole(Hole&& _Other) noexcept = delete;
	Hole& operator=(const Hole& _Other) = delete;
	Hole& operator=(const Hole&& _Other) noexcept = delete;

	void AddHoleAtGround(class GameEngineRenderer* _GroundTexture, GameEngineRenderer* _GroundPixelTexture);
protected:

private:
	class GameEngineWindowTexture* Texture = nullptr;



	void Start();

	
	
};

