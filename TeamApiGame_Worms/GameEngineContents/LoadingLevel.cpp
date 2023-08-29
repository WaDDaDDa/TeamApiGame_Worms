#include "LoadingLevel.h"
#include "UI_LoadingCDRom.h"

LoadingLevel::LoadingLevel()
{
}

LoadingLevel::~LoadingLevel()
{
}

void LoadingLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	LoadingUI = CreateActor<UI_LoadingCDRom>();
}

void LoadingLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	LoadingUI->Death();
}

void LoadingLevel::Start()
{

}

void LoadingLevel::Update(float _Delta)
{

}
