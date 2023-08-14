
#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum CloudType
{
	Small,
	Middle,
	Large,
};

class Cloud : public GameEngineActor
{
public:
	Cloud();
	~Cloud();

	Cloud(const Cloud& _Other) = delete;
	Cloud(Cloud&& _Other) noexcept = delete;
	Cloud& operator=(const Cloud& _Other) = delete;
	Cloud& operator=(const Cloud&& _Other) noexcept = delete;


protected:

private:
	float Speed ;
	float4 Dir = float4::ZERO;

	CloudType Type;

	void Start() override;
	void Update(float _Delta) override;

};

