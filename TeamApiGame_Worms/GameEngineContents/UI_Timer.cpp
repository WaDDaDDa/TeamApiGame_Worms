#include "UI_Timer.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include "GameTurn.h"
#include <string.h>


UI_Timer* UI_Timer::TimerUI = nullptr;

UI_Timer::UI_Timer()
{
	TimerUI = this;
}

UI_Timer::~UI_Timer()
{
}

void UI_Timer::Start()
{
	// 리소스 로딩
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\Timer\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_TimerWindowB.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_TimerWindowB.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_TimerWindowC.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_TimerWindowC.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_TimerWindowG.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_TimerWindowG.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_TimerWindowP.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_TimerWindowP.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_TimerWindowR.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_TimerWindowR.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_TimerWindowY.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_TimerWindowY.bmp"));
	}



	// 렌더러 설정
	MainRenderer = CreateUIRenderer("UI_TimerWindowR.bmp", RenderOrder::UI);
	MainRenderer->SetRenderScale({ 56, 42 });

	// 타이머 폰트 렌더러 설정
	TimerTextRenderer = CreateUIRenderer(RenderOrder::UI);
	TimerTextRenderer->SetText("00");
	TimerTextRenderer->SetRenderPos({ -9, -8});

}

void UI_Timer::Update(float _Delta)
{

	int CurTurnTime = static_cast<int>(GameTurn::MainGameTurn->GetTurnTime());
	TimerTextRenderer->SetText(std::to_string(CurTurnTime));

	if (CurTurnTime < 10)
	{
		TimerTextRenderer->SetRenderPos({ -5, -8 });
	}

	else
	{
		TimerTextRenderer->SetRenderPos({ -12, -8 });
	}
}

void UI_Timer::ChangeTimerColor(int _PlayerIndex)
{

	int PlayerIndex = _PlayerIndex;

	switch (PlayerIndex)
	{
	case 0:
		MainRenderer->SetTexture("UI_TimerWindowR.bmp");
		break;

	case 1:
		MainRenderer->SetTexture("UI_TimerWindowB.bmp");
		break;

	case 2:
		MainRenderer->SetTexture("UI_TimerWindowG.bmp");
		break;

	case 3:
		MainRenderer->SetTexture("UI_TimerWindowY.bmp");
		break;

	case 4:
		MainRenderer->SetTexture("UI_TimerWindowP.bmp");
		break;

	case 5:
		MainRenderer->SetTexture("UI_TimerWindowC.bmp");
		break;

	default:
		break;
	}

}