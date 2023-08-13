#include "UI_Timer.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include "GameTurn.h"
#include <math.h>
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
	MainRenderer = CreateUIRenderer("UI_TimerWindowB.bmp", RenderOrder::UI);
	MainRenderer->SetRenderScale({ 56, 42 });

	// 타이머 폰트 렌더러 설정
	TimerTextRenderer = CreateUIRenderer(RenderOrder::UI);
	TimerTextRenderer->SetText("00");
	TimerTextRenderer->SetRenderPos({ -9, -8});

}

void UI_Timer::Update(float _Delta)
{
	// 여기서 - 계산한 건 테스트용입니다 턴이 넘어가버리면 리셋이 없어서 -가 되기 때문에 최종버전 X 
	// => GameTurn 쪽에서 GetTurnPlayTime() - GetLiveTime() 계산을 한채로 넘어와야 리셋이 정확하게 되기 때문에 수정되어야 합니다
	int t = static_cast<int>(GameTurn::MainGameTurn.GetTurnTime());
	TimerTextRenderer->SetText(std::to_string(t));

	if (t < 10)
	{
		TimerTextRenderer->SetRenderPos({ -5, -8 });
	}

	else
	{
		TimerTextRenderer->SetRenderPos({ -12, -8 });
	}
}

void UI_Timer::ChangeTimer()
{
}