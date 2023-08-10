#include "Wind.h"
#include <GameEngineBase/GameEngineRandom.h>

Wind* Wind::PlayWind = nullptr;

#define WIND_LIMIT 100.0F


Wind::Wind()
{
}

Wind::~Wind()
{
}

void Wind::ChangeWind()
{
	WindPower= GameEngineRandom::MainRandom.RandomFloat(0, WIND_LIMIT);
	int WindDirtmp = GameEngineRandom::MainRandom.RandomInt(0, 1);

	switch (WindDirtmp)
	{
	case 0:
		WindDir = float4::LEFT ;
		break;
	case 1:
		WindDir = float4::RIGHT;
		break;

	default:
		break;
	}

	WindVector = WindDir * WindPower;
}

void Wind::Start()
{
	PlayWind = this;
}
