#include "EndingLevel.h"
#include "UI_EndingBackGround.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}

void EndingLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<UI_EndingBackGround>();
	BGMPlayer = GameEngineSound::SoundPlay("Worms_TitleScreen.mp3", 100);
}

void EndingLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}

void EndingLevel::Start()
{
	if (nullptr == GameEngineSound::FindSound("Worms_TitleScreen.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Effects\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Worms_TitleScreen.mp3"));
	}
}

void EndingLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RETURN))
	{
		DestroyWindow(GameEngineWindow::MainWindow.GetHWND());
	}
}