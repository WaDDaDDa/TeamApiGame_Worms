#include "UI_Win_Button.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineInput.h>

UI_Win_Button::UI_Win_Button()
{
}

UI_Win_Button::~UI_Win_Button()
{
}

void UI_Win_Button::Start()
{
	// 리소스 로딩
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Wins0.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Wins0.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Wins1.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Wins1.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Wins2.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Wins2.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Wins3.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Wins3.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Wins4.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Wins4.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Wins5.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Wins5.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Wins6.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Wins6.bmp"));
	}

	MainRenderer = CreateRenderer(RenderOrder::UI);

	MainRenderer->SetRenderScale({ 68, 68 });

	MainRenderer->SetTexture("UI_Wins0.bmp");

	MainCollision = CreateCollision(CollisionOrder::UI);
	MainCollision->SetCollisionType(CollisionType::Rect);
	MainCollision->SetCollisionScale({ 68, 68 });

	ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);
}

void UI_Win_Button::Update(float _Delta)
{
	StateUpdate();
	CheckButtonCollision();
}

void UI_Win_Button::ChangeSelectValue()
{
	if (m_SelectIndex < 6)
	{
		++m_SelectIndex;
	}

	else
	{
		m_SelectIndex = 0;
	}

	switch (m_SelectIndex)
	{
	case 0:
		MainRenderer->SetTexture("UI_Wins0.bmp");
		break;

	case 1:
		MainRenderer->SetTexture("UI_Wins1.bmp");
		break;

	case 2:
		MainRenderer->SetTexture("UI_Wins2.bmp");
		break;

	case 3:
		MainRenderer->SetTexture("UI_Wins3.bmp");
		break;

	case 4:
		MainRenderer->SetTexture("UI_Wins4.bmp");
		break;

	case 5:
		MainRenderer->SetTexture("UI_Wins5.bmp");
		break;

	case 6:
		MainRenderer->SetTexture("UI_Wins6.bmp");
		break;

	default:
		break;
	}

	ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
}

void UI_Win_Button::StateUpdate()
{
	switch (ButtonState)
	{
	case BUTTON_STATE::BUTTON_STATE_HOVERED:
		CheckButtonClick();
		break;

	case BUTTON_STATE::BUTTON_STATE_UNHOVERED:
		break;

	case BUTTON_STATE::BUTTON_STATE_CLICKED:
		ChangeSelectValue();
		break;

	default:
		break;
	}
}

void UI_Win_Button::CheckButtonCollision()
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
				UI_Win_Button* ButtonPtr = dynamic_cast<UI_Win_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
			}

			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{

			}

				, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{
				GameEngineActor* thisActor = _this->GetActor();
				UI_Win_Button* ButtonPtr = dynamic_cast<UI_Win_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);
			}
			);

	}
}

void UI_Win_Button::CheckButtonClick()
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

void UI_Win_Button::ChangeState(BUTTON_STATE _ButtonState)
{
	ButtonState = _ButtonState;
}
