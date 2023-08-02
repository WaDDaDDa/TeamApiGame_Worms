
#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineWindowTexture;
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

	float GetDistanceFromHoleCenter(float4 _Pos);

	void SetScale(float4 _Scale)
	{
		Scale = _Scale;
	}

		
protected:

private:
	 GameEngineWindowTexture* Texture = nullptr;
	 GameEngineWindowTexture* PixelTexture = nullptr;



	float4 Scale=float4::ZERO;

	void Start();

	
	
};

