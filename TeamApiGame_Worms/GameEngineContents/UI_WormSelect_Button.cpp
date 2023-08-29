#include "UI_WormSelect_Button.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineInput.h>

UI_WormSelect_Button::UI_WormSelect_Button()
{
}

UI_WormSelect_Button::~UI_WormSelect_Button()
{
}

void UI_WormSelect_Button::Start()
{

	// 리소스 로딩
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_WormSelectOFF.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_WormSelectOFF.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_WormSelectON.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_WormSelectON.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_WormSelectRANDOM.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_WormSelectRANDOM.bmp"));
	}

	// 하이라이트 리소스 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("H_UI_WormSelectOFF.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("H_UI_WormSelectOFF.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("H_UI_WormSelectON.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("H_UI_WormSelectON.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("H_UI_WormSelectRANDOM.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("H_UI_WormSelectRANDOM.bmp"));
	}

	// 사운드 리소스 로딩
	if (nullptr == GameEngineSound::FindSound("CursorSelect.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Effects\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("CursorSelect.wav"));
	}

	MainRenderer = CreateRenderer(RenderOrder::UI);

	MainRenderer->SetRenderScale({ 68, 68 });

	MainRenderer->SetTexture("UI_WormSelectOFF.bmp");

	MainCollision = CreateCollision(CollisionOrder::UI);
	MainCollision->SetCollisionType(CollisionType::Rect);
	MainCollision->SetCollisionScale({ 68, 68 });

	ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);

}

void UI_WormSelect_Button::Update(float _Delta)
{
	StateUpdate();
	CheckButtonCollision();
}

void UI_WormSelect_Button::HighlighterOn()
{
	switch (m_SelectIndex)
	{
	case 0:
		MainRenderer->SetTexture("H_UI_WormSelectOFF.bmp");
		break;

	case 1:
		MainRenderer->SetTexture("H_UI_WormSelectON.bmp");
		break;

	case 2:
		MainRenderer->SetTexture("H_UI_WormSelectRANDOM.bmp");
		break;

	default:
		break;
	}
}

void UI_WormSelect_Button::HighlighterOff()
{
	switch (m_SelectIndex)
	{
	case 0:
		MainRenderer->SetTexture("UI_WormSelectOFF.bmp");
		break;

	case 1:
		MainRenderer->SetTexture("UI_WormSelectON.bmp");
		break;

	case 2:
		MainRenderer->SetTexture("UI_WormSelectRANDOM.bmp");
		break;

	default:
		break;
	}
}

void UI_WormSelect_Button::ChangeSelectValue()
{
	if (m_SelectIndex < 3)
	{
		++m_SelectIndex;
	}

	else
	{
		m_SelectIndex = 0;
	}

	HighlighterOn();

	EFFECT_Player_Click = GameEngineSound::SoundPlay("CursorSelect.wav");

	ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
}

void UI_WormSelect_Button::StateUpdate()
{
	switch (ButtonState)
	{
	case BUTTON_STATE::BUTTON_STATE_HOVERED:
		HighlighterOn();
		CheckButtonClick();
		break;

	case BUTTON_STATE::BUTTON_STATE_UNHOVERED:
		EFFECT_Player_Click.Stop();
		HighlighterOff();
		break;

	case BUTTON_STATE::BUTTON_STATE_CLICKED:
		ChangeSelectValue();
		break;

	default:
		break;
	}
}

void UI_WormSelect_Button::CheckButtonCollision()
{
	if (nullptr != MainCollision)
	{

		MainCollision->CollisionCallBack
		(
			CollisionOrder::Mouse
			, CollisionType::Rect // _this의 충돌체 타입
			, CollisionType::CirCle // _Other의 충돌체 타입
			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{
				GameEngineActor* thisActor = _this->GetActor();
				UI_WormSelect_Button* ButtonPtr = dynamic_cast<UI_WormSelect_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
			}

			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{

			}

				, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{
				GameEngineActor* thisActor = _this->GetActor();
				UI_WormSelect_Button* ButtonPtr = dynamic_cast<UI_WormSelect_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);
			}
			);

	}
}

void UI_WormSelect_Button::CheckButtonClick()
{
	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChangeState(BUTTON_STATE::BUTTON_STATE_CLICKED);
	}

	if (true == GameEngineInput::IsFree(VK_LBUTTON) && true == GameEngineInput::IsFree(VK_RBUTTON))
	{
		ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
	}
}

void UI_WormSelect_Button::ChangeState(BUTTON_STATE _ButtonState)
{
	ButtonState = _ButtonState;
}
