#include "UI_FadeObject.h"

#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>

UI_FadeObject::UI_FadeObject()
{
}

UI_FadeObject::~UI_FadeObject()
{
}

void UI_FadeObject::Start()
{
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("UI_FADE.bmp");

	if (false == IsResource)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_FADE.bmp"));
	}

	// ·»´õ·¯ ¼³Á¤
	MainRenderer = CreateUIRenderer("UI_FADE.bmp", RenderOrder::UI);
	MainRenderer->SetRenderPos(GameEngineWindow::MainWindow.GetScale().Half());
	MainRenderer->SetRenderScale(GameEngineWindow::MainWindow.GetScale());
	MainRenderer->Off();
	
	ChangeState(FADE_STATE::FADE_STATE_IN);
}

void UI_FadeObject::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void UI_FadeObject::StateUpdate(float _Delta)
{
	switch (FadeState)
	{
	case FADE_STATE::FADE_STATE_IN:
//		m_fCurrentAlpha = 255.0f;
		SetFadeIn(_Delta);
		break;

	case FADE_STATE::FADE_STATE_OUT:
//		m_fCurrentAlpha = 0.0f;
		SetFadeOut(_Delta);
		break;

	default:
		break;
	}
}

void UI_FadeObject::ChangeState(FADE_STATE _FadeState)
{
	FadeState = _FadeState;
}

void UI_FadeObject::SetFadeIn(float _Delta)
{
	MainRenderer->On();

	m_fCurrentAlpha -= _Delta * 100;
	if (0.0f >= m_fCurrentAlpha)
	{
		Death();
		return;
	}

	MainRenderer->SetAlpha(static_cast<unsigned char>(m_fCurrentAlpha));
}

void UI_FadeObject::SetFadeOut(float _Delta)
{
	MainRenderer->On();

	m_fCurrentAlpha += _Delta * 100;
	if (0.0f <= m_fCurrentAlpha)
	{
		Death();
		return;
	}

	MainRenderer->SetAlpha(static_cast<unsigned char>(m_fCurrentAlpha));
}