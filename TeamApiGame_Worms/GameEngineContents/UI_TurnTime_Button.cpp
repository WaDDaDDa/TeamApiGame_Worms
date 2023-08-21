#include "UI_TurnTime_Button.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "GameStateManager.h"

UI_TurnTime_Button::UI_TurnTime_Button()
{
}

UI_TurnTime_Button::~UI_TurnTime_Button()
{
}

void UI_TurnTime_Button::Start()
{
	// 리소스 로딩
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_TurnTime_0.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_TurnTime_0.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_TurnTime_1.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_TurnTime_1.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_TurnTime_2.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_TurnTime_2.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_TurnTime_3.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_TurnTime_3.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_TurnTime_4.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_TurnTime_4.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_TurnTime_5.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_TurnTime_5.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_TurnTime_6.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_TurnTime_6.bmp"));
	}

	MainRenderer = CreateRenderer(RenderOrder::UI);

	MainRenderer->SetRenderScale({ 68, 68 });

	MainRenderer->SetTexture("UI_TurnTime_0.bmp");

	MainCollision = CreateCollision(CollisionOrder::UI);
	MainCollision->SetCollisionType(CollisionType::Rect);
	MainCollision->SetCollisionScale({ 68, 68 });

	ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);

	// 아무것도 누르지 않았을 때의 기본값
	GameStateManager::GameState->SetTurnTime(15.0f);
}

void UI_TurnTime_Button::Update(float _Delta)
{
	StateUpdate();
	CheckButtonCollision();
}

void UI_TurnTime_Button::ChangeSelectValue()
{
	if (m_SelectIndex < 5)
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
		MainRenderer->SetTexture("UI_TurnTime_0.bmp");
		GameStateManager::GameState->SetTurnTime(15.0f);
		break;

	case 1:
		MainRenderer->SetTexture("UI_TurnTime_1.bmp");
		GameStateManager::GameState->SetTurnTime(20.0f);
		break;

	case 2:
		MainRenderer->SetTexture("UI_TurnTime_2.bmp");
		GameStateManager::GameState->SetTurnTime(30.0f);
		break;

	case 3:
		MainRenderer->SetTexture("UI_TurnTime_3.bmp");
		GameStateManager::GameState->SetTurnTime(45.0f);
		break;

	case 4:
		MainRenderer->SetTexture("UI_TurnTime_4.bmp");
		GameStateManager::GameState->SetTurnTime(60.0f);
		break;

	case 5:
		MainRenderer->SetTexture("UI_TurnTime_5.bmp");
		GameStateManager::GameState->SetTurnTime(90.0f);
		break;

	default:
		break;
	}

	ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
}

void UI_TurnTime_Button::StateUpdate()
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

void UI_TurnTime_Button::CheckButtonCollision()
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
				UI_TurnTime_Button* ButtonPtr = dynamic_cast<UI_TurnTime_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
			}

			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{

			}

				, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{
				GameEngineActor* thisActor = _this->GetActor();
				UI_TurnTime_Button* ButtonPtr = dynamic_cast<UI_TurnTime_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);
			}
			);

	}
}

void UI_TurnTime_Button::CheckButtonClick()
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

void UI_TurnTime_Button::ChangeState(BUTTON_STATE _ButtonState)
{
	ButtonState = _ButtonState;
}
