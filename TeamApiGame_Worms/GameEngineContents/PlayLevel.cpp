#include "PlayLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>


#include "BackGround.h"

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

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("TestGround.Bmp", "TestGroundPixel.bmp");


}

void PlayLevel::Update(float _Delta)
{

	if (true == GameEngineInput::IsDown('J'))
	{
		BackGroundPtr->SwitchRender();
	}

}
