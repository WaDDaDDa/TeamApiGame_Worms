#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class MouseObject : public GameEngineActor
{
public:
	// constrcuter destructer
	MouseObject();
	~MouseObject();

	// delete Function
	MouseObject(const MouseObject & _Other) = delete;
	MouseObject(MouseObject && _Other) noexcept = delete;
	MouseObject& operator=(const MouseObject & _Other) = delete;
	MouseObject& operator=(MouseObject && _Other) noexcept = delete;

	float4 GetPlayMousePos()
	{
		return PlayMousePos;
	}
	

protected:

private:
	GameEngineRenderer* CrossHairRenderer;

	float4 PlayMousePos = float4::ZERO;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

};

