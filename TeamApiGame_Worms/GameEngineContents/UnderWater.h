
#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UnderWater : public GameEngineActor
{
public:
	UnderWater();
	~UnderWater();

	UnderWater(const UnderWater& _Other) = delete;
	UnderWater(UnderWater&& _Other) noexcept = delete;
	UnderWater& operator=(const UnderWater& _Other) = delete;
	UnderWater& operator=(const UnderWater&& _Other) noexcept = delete;

	void DrawAtStage(class GameEngineLevel* _Level);
	

protected:

private:
	class GameEngineWindowTexture* Texture = nullptr;
	class GameEngineRenderer* Renderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};

