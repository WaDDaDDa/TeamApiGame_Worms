#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include "UI_IntroLogo.h"
#include "UI_FadeObject.h"
#include <GameEnginePlatform/GameEngineWindow.h>

/*
	타이틀에서 사용할 배경이미지를 애니메이션으로 등록하고
	상태에 따라 바꿔주기

*/


TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	ChangeState(TITLE_STATE::TITLE_STATE_INTRO);
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

	TitleState = _TitleState;
}

void TitleLevel::Title_Intro_Start()
{
	IntroLogo = CreateActor<UI_IntroLogo>();
	IntroLogo->SetPos(GameEngineWindow::MainWindow.GetScale().Half());

	UI_FadeObject* FadeIn = CreateActor<UI_FadeObject>();
	FadeIn->SetFadeInMode();
}

void TitleLevel::Title_ShowTitle_Start()
{
	
}

void TitleLevel::Title_Main_Start()
{



}

void TitleLevel::Title_Intro_Update(float _Delta)
{
	if (IntroLogo->GetLiveTime() > 5.0f)
	{
		UI_FadeObject* FadeOut = CreateActor<UI_FadeObject>();
		FadeOut->SetFadeOutMode();
	}

	if (IntroLogo->GetLiveTime() > 6.0f)
	{
		ChangeState(TITLE_STATE::TITLE_STATE_SHOWTITLE);
	}

	

}

void TitleLevel::Title_ShowTitle_Update(float _Delta)
{
}

void TitleLevel::Title_Main_Update(float _Delta)
{
}

