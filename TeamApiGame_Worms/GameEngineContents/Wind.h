
#pragma once
#include <GameEngineCore/GameEngineActor.h>

#define WIND_LIMIT 300.0F

class Wind :public GameEngineActor
{
public:
	Wind();
	~Wind();

	Wind(const Wind& _Other) = delete;
	Wind(Wind&& _Other) noexcept = delete;
	Wind& operator=(const Wind& _Other) = delete;
	Wind& operator=(const Wind&& _Other) noexcept = delete;

	static Wind* GetWind()
	{
		return PlayWind;
	}


	float4 GetWindVector() const
	{
		return WindVector;
	}

	float4 GetWindDir() const
	{
		return WindDir;
	}

	float GetWindPower() const
	{
		return WindPower;
	}

	void ChangeWind(float _Delta);

protected:

private:
	static Wind* PlayWind;

	void Start() override;;

	float4 WindVector = float4::ZERO;
	float4 WindDir = float4::ZERO;
	float WindPower = 0.0f;


};

