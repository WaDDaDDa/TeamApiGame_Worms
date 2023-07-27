#include "PlayLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>


#include "Ground.h"
#include "Player.h"
#include "GameTurn.h"
#include "MouseObject.h"

#include "UI_Mouse.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

Ground* PlayLevel::GetGround() const
{
	if (nullptr == GroundPtr)
	{
		MsgBoxAssert("Ground가 설정되지 않은채로 사용되려했습니다.");
		return nullptr;
	}
	
	return GroundPtr;
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

	GameEngineWindow::MainWindow.CursorOff();

	CreateActor<MouseObject>();
}



void PlayLevel::LevelStart(GameEngineLevel* _NextLevel)
{

	CreateActor<UI_Mouse>();


	GroundPtr = CreateActor<Ground>();
	GroundPtr->Init("TestGround.Bmp", "TestGroundPixel.bmp");

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
		GroundPtr->SwitchRender();
	}
}

void PlayLevel::Release()
{

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}