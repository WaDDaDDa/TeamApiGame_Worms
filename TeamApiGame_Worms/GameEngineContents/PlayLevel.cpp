#include "PlayLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>


#include "BackGround.h"
#include "Player.h"
#include "GameTurn.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	//
	if (false == ResourcesManager::GetInst().IsLoadTexture("TestGround.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TestGround.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TestGroundPixel.bmp"));
	}

}

void PlayLevel::LevelStart(GameEngineLevel* _NextLevel)
{
	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("TestGround.Bmp", "TestGroundPixel.bmp");

	{
		Player* TestPlayer = CreateActor<Player>();
		TestPlayer->SetGroundTexture("TestGroundPixel.bmp");
		TestPlayer->SetPos(float4{ 100, 100 });
	}

	{
		Player* TestPlayer = CreateActor<Player>();
		TestPlayer->SetGroundTexture("TestGroundPixel.bmp");
		TestPlayer->SetPos(float4{ 400, 100 });
	}

	{
		Player* TestPlayer = CreateActor<Player>();
		TestPlayer->SetGroundTexture("TestGroundPixel.bmp");
		TestPlayer->SetPos(float4{ 700, 100 });
	}

	{
		Player* TestPlayer = CreateActor<Player>();
		TestPlayer->SetGroundTexture("TestGroundPixel.bmp");
		TestPlayer->SetPos(float4{ 1000, 100 });
	}

	CreateActor<GameTurn>();
}

void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('J'))
	{
		BackGroundPtr->SwitchRender();
	}
}

void PlayLevel::Release()
{

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}