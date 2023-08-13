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
	// ���ҽ� �ε�
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



	// ������ ����
	MainRenderer = CreateUIRenderer("UI_TimerWindowB.bmp", RenderOrder::UI);
	MainRenderer->SetRenderScale({ 56, 42 });

	// Ÿ�̸� ��Ʈ ������ ����
	TimerTextRenderer = CreateUIRenderer(RenderOrder::UI);
	TimerTextRenderer->SetText("00");
	TimerTextRenderer->SetRenderPos({ -9, -8});

}

void UI_Timer::Update(float _Delta)
{
	// ���⼭ - ����� �� �׽�Ʈ���Դϴ� ���� �Ѿ������ ������ ��� -�� �Ǳ� ������ �������� X 
	// => GameTurn �ʿ��� GetTurnPlayTime() - GetLiveTime() ����� ��ä�� �Ѿ�;� ������ ��Ȯ�ϰ� �Ǳ� ������ �����Ǿ�� �մϴ�
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