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

	UI_FadeObject* Fade = CreateActor<UI_FadeObject>();
	Fade->SetPos({ 0, 0 });

}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}