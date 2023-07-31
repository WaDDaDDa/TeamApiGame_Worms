#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include "UI_IntroLogo.h"
#include "UI_FadeObject.h"
#include <GameEnginePlatform/GameEngineWindow.h>

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	UI_IntroLogo* IntroLogo = CreateActor<UI_IntroLogo>();
	IntroLogo->SetPos(GameEngineWindow::MainWindow.GetScale().Half());

	UI_FadeObject* FadeOut = CreateActor<UI_FadeObject>();
	FadeOut->SetFadeOutMode();

	UI_FadeObject* FadeIn = CreateActor<UI_FadeObject>();
	FadeIn->SetFadeInMode();

}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
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
	if (_TitleState != TitleState)
	{
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

	TitleState = _TitleState;
}

void TitleLevel::Title_Intro_Start()
{
}

void TitleLevel::Title_ShowTitle_Start()
{
}

void TitleLevel::Title_Main_Start()
{
}

void TitleLevel::Title_Intro_Update(float _Delta)
{
}

void TitleLevel::Title_ShowTitle_Update(float _Delta)
{
}

void TitleLevel::Title_Main_Update(float _Delta)
{
}

