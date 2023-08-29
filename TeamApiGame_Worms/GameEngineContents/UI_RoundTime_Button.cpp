#include "UI_RoundTime_Button.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineInput.h>

UI_RoundTime_Button::UI_RoundTime_Button()
{
}

UI_RoundTime_Button::~UI_RoundTime_Button()
{
}

void UI_RoundTime_Button::Start()
{

	// 이미지 리소스 로딩
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Round0.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Round0.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Round1.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Round1.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Round2.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Round2.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Round3.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Round3.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Round4.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Round4.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Round5.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Round5.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Round6.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Round6.bmp"));
	}


	// 하이라이트 리소스 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("H_UI_Round0.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("H_UI_Round0.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("H_UI_Round1.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("H_UI_Round1.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("H_UI_Round2.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("H_UI_Round2.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("H_UI_Round3.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("H_UI_Round3.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("H_UI_Round4.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("H_UI_Round4.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("H_UI_Round5.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("H_UI_Round5.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("H_UI_Round6.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("H_UI_Round6.bmp"));
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

	MainRenderer->SetTexture("UI_Round0.bmp");

	MainCollision = CreateCollision(CollisionOrder::UI);
	MainCollision->SetCollisionType(CollisionType::Rect);
	MainCollision->SetCollisionScale({ 68, 68 });

	ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);

}

void UI_RoundTime_Button::Update(float _Delta)
{
	StateUpdate();
	CheckButtonCollision();
}

void UI_RoundTime_Button::ChangeSelectValue()
{
	if (m_SelectIndex < 6)
	{
		++m_SelectIndex;
	}

	else
	{
		m_SelectIndex = 0;
	}

	EFFECT_Player_Click = GameEngineSound::SoundPlay("CursorSelect.wav");
	ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
}

void UI_RoundTime_Button::StateUpdate()
{
	switch (ButtonState)
	{
	case BUTTON_STATE::BUTTON_STATE_HOVERED:
		CheckButtonClick();
		HighlighterOn();
		break;

	case BUTTON_STATE::BUTTON_STATE_UNHOVERED:
		EFFECT_Player_Click.Stop();
		HighlighterOff();
		break;

	case BUTTON_STATE::BUTTON_STATE_CLICKED:
		ChangeSelectValue();
		HighlighterOn();
		break;

	default:
		break;
	}
}

void UI_RoundTime_Button::CheckButtonCollision()
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
				UI_RoundTime_Button* ButtonPtr = dynamic_cast<UI_RoundTime_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
			}

			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{

			}

				, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{
				GameEngineActor* thisActor = _this->GetActor();
				UI_RoundTime_Button* ButtonPtr = dynamic_cast<UI_RoundTime_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);
			}
			);

	}
}

void UI_RoundTime_Button::CheckButtonClick()
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

void UI_RoundTime_Button::ChangeState(BUTTON_STATE _ButtonState)
{
	ButtonState = _ButtonState;
}

void UI_RoundTime_Button::HighlighterOn()
{
	switch (m_SelectIndex)
	{
	case 0:
		MainRenderer->SetTexture("H_UI_Round0.bmp");
		break;

	case 1:
		MainRenderer->SetTexture("H_UI_Round1.bmp");
		break;

	case 2:
		MainRenderer->SetTexture("H_UI_Round2.bmp");
		break;

	case 3:
		MainRenderer->SetTexture("H_UI_Round3.bmp");
		break;

	case 4:
		MainRenderer->SetTexture("H_UI_Round4.bmp");
		break;

	case 5:
		MainRenderer->SetTexture("H_UI_Round5.bmp");
		break;

	case 6:
		MainRenderer->SetTexture("H_UI_Round6.bmp");
		break;

	default:
		break;
	}

}

void UI_RoundTime_Button::HighlighterOff()
{

	switch (m_SelectIndex)
	{
	case 0:
		MainRenderer->SetTexture("UI_Round0.bmp");
		break;

	case 1:
		MainRenderer->SetTexture("UI_Round1.bmp");
		break;

	case 2:
		MainRenderer->SetTexture("UI_Round2.bmp");
		break;

	case 3:
		MainRenderer->SetTexture("UI_Round3.bmp");
		break;

	case 4:
		MainRenderer->SetTexture("UI_Round4.bmp");
		break;

	case 5:
		MainRenderer->SetTexture("UI_Round5.bmp");
		break;

	case 6:
		MainRenderer->SetTexture("UI_Round6.bmp");
		break;

	default:
		break;
	}

}