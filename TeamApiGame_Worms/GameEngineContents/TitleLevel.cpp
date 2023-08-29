#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

#include "UI_IntroLogo.h"
#include "UI_FadeObject.h"
#include "UI_MainLogo.h"

#include <GameEnginePlatform/GameEngineWindow.h>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
	
}

void TitleLevel::Start()
{
	if (nullptr == GameEngineSound::FindSound("Worms_TitleScreen.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Effects\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Worms_TitleScreen.mp3"));
	}

	if (nullptr == GameEngineSound::FindSound("Worms_TitleScreen_Heartbeat.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Effects\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Worms_TitleScreen_Heartbeat.wav"));
	}

	if (nullptr == GameEngineSound::FindSound("meganuke.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Effects\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("meganuke.wav"));
	}



	IntroLogo = CreateActor<UI_IntroLogo>();
	IntroLogo->SetPos(GameEngineWindow::MainWindow.GetScale().Half());

	ChangeState(TITLE_STATE::TITLE_STATE_INTRO);
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("ModeSelectLevel");
	}

	StateUpdate(_DeltaTime);
}

void TitleLevel::StateUpdate(float _Delta)
{
	switch (TitleState)
	{
	case TITLE_STATE::TITLE_STATE_INTRO:
		Title_Intro_Update(_Delta);
		break;

	case TITLE_STATE::TITLE_STATE_SHOWTITLE:
		Title_ShowTitle_Update(_Delta);
		break;

	case TITLE_STATE::TITLE_STATE_MAIN:
		Title_Main_Update(_Delta);
		break;

	default:
		break;
	}

}

void TitleLevel::ChangeState(TITLE_STATE _TitleState)
{

	TitleState = _TitleState;

	switch (TitleState)
	{
	case TITLE_STATE::TITLE_STATE_INTRO:
		Title_Intro_Start();
		break;

	case TITLE_STATE::TITLE_STATE_SHOWTITLE:
		Title_ShowTitle_Start();
		break;

	case TITLE_STATE::TITLE_STATE_MAIN:
		Title_Main_Start();
		break;

	default:
		break;
	}

}

void TitleLevel::Title_Intro_Start()
{
	UI_FadeObject* FadeIn = CreateActor<UI_FadeObject>();
	FadeIn->SetFadeInMode();
}

void TitleLevel::Title_ShowTitle_Start()
{
	BGMPlayer = GameEngineSound::SoundPlay("Worms_TitleScreen_Heartbeat.wav");
	BGMPlayer.SetVolume(5.0f);
	IntroLogo->ChangeState_Black();
	MainLogo = CreateActor<UI_MainLogo>();

}

void TitleLevel::Title_Main_Start()
{
	EFFECTPlayer_Bomb = GameEngineSound::SoundPlay("meganuke.wav");
	BGMPlayer.Stop();
	BGMPlayer = GameEngineSound::SoundPlay("Worms_TitleScreen.mp3");
	IntroLogo->ChangeState_Main_Back();
	MainLogo->On();
	MainLogo->SetShowAllTitleText();
}

void TitleLevel::Title_Intro_Update(float _Delta)
{
	if (IntroLogo != nullptr)
	{
		if (IntroLogo->GetLiveTime() > 4.0f)
		{
			UI_FadeObject* FadeOut = CreateActor<UI_FadeObject>();
			FadeOut->SetFadeOutMode();

		}

		if (IntroLogo->GetLiveTime() > 6.0f)
		{
			ChangeState(TITLE_STATE::TITLE_STATE_SHOWTITLE);
		}

	}

}

void TitleLevel::Title_ShowTitle_Update(float _Delta)
{
	if (MainLogo != nullptr)
	{

		if (MainLogo->GetLiveTime() > 5.0f)
		{
			ChangeState(TITLE_STATE::TITLE_STATE_MAIN);
			UI_FadeObject* FadeIn = CreateActor<UI_FadeObject>();
			FadeIn->SetFadeInMode();
		}
	}
}

void TitleLevel::Title_Main_Update(float _Delta)
{
	if (true == MainLogo->IsUpdate())
	{
		if (false == MainLogo->GetShowAllTitleText())
		{
			IntroLogo->ChangeState_Main();
			MainLogo->Off();
		}
	}

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		GameEngineCore::ChangeLevel("ModeSelectLevel");
	}

}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	EFFECTPlayer_Bomb.Stop();
	BGMPlayer.Stop();
}

