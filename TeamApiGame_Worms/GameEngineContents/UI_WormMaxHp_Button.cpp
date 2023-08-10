#include "UI_WormMaxHp_Button.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineInput.h>

UI_WormMaxHp_Button::UI_WormMaxHp_Button()
{
}

UI_WormMaxHp_Button::~UI_WormMaxHp_Button()
{
}

void UI_WormMaxHp_Button::Start()
{

	// 리소스 로딩
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Hp00.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Hp00.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Hp100.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Hp100.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Hp150.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Hp150.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Hp200.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Hp200.bmp"));
	}

	MainRenderer = CreateRenderer(RenderOrder::UI);

	MainRenderer->SetRenderScale({ 68, 68 });

	MainRenderer->SetTexture("UI_Hp00.bmp");

	MainCollision = CreateCollision(CollisionOrder::UI);
	MainCollision->SetCollisionType(CollisionType::Rect);
	MainCollision->SetCollisionScale({ 68, 68 });

	ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);

}

void UI_WormMaxHp_Button::Update(float _Delta)
{
	StateUpdate();
	CheckButtonCollision();
}

void UI_WormMaxHp_Button::ChangeSelectValue()
{
	if (m_SelectIndex < 4)
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
		MainRenderer->SetTexture("UI_Hp00.bmp");
		break;

	case 1:
		MainRenderer->SetTexture("UI_Hp100.bmp");
		break;

	case 2:
		MainRenderer->SetTexture("UI_Hp150.bmp");
		break;

	case 3:
		MainRenderer->SetTexture("UI_Hp200.bmp");
		break;

	default:
		break;
	}

	ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
}

void UI_WormMaxHp_Button::StateUpdate()
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

void UI_WormMaxHp_Button::CheckButtonCollision()
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
				UI_WormMaxHp_Button* ButtonPtr = dynamic_cast<UI_WormMaxHp_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
			}

			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{

			}

				, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{
				GameEngineActor* thisActor = _this->GetActor();
				UI_WormMaxHp_Button* ButtonPtr = dynamic_cast<UI_WormMaxHp_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);
			}
			);

	}
}

void UI_WormMaxHp_Button::CheckButtonClick()
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

void UI_WormMaxHp_Button::ChangeState(BUTTON_STATE _ButtonState)
{
	ButtonState = _ButtonState;
}
