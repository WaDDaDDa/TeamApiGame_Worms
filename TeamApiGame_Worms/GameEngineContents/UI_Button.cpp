#include "UI_Button.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

UI_Button::UI_Button()
{
}

UI_Button::~UI_Button()
{
}

void UI_Button::Start()
{

}

void UI_Button::Update(float _Delta)
{
	if (false == m_IsActive)
	{
		return;
	}

	// ��ư ���� �浹�� ���� Ȱ�� ���� üũ
	CheckButtonCollision();

	// ��ư ��ü ���� ������Ʈ
	StateUpdate();

}

UI_Button& UI_Button::InitButtonData(const std::string _ButtonName, float4 _ButtonScale)
{
	// �̸� ����
	std::string ButtonName = _ButtonName;
	float4 ButtonScale = _ButtonScale;

	// ������ ����
	std::string ImageName = ButtonName + ".bmp";

	bool IsResource = ResourcesManager::GetInst().IsLoadTexture(ImageName);

	if (false == IsResource)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(ImageName));
	}

	MainRenderer = CreateRenderer(ImageName, static_cast<int>(RenderOrder::UI));
	MainRenderer->SetRenderScale(ButtonScale);

	MainCollision = CreateCollision(CollisionOrder::UI);
	MainCollision->SetCollisionType(CollisionType::Rect);
	MainCollision->SetCollisionScale(ButtonScale);

	ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);

	return *this;
}

void UI_Button::StateUpdate()
{
	switch (ButtonState)
	{
	case BUTTON_STATE::BUTTON_STATE_HOVERED:
		BUTTON_STATE_HOVERED_UPDATE();
		//CheckButtonClick();
		break;

	case BUTTON_STATE::BUTTON_STATE_UNHOVERED:
		break;

	default:
		break;
	}
}

void UI_Button::ChangeState(BUTTON_STATE _ButtonState)
{
	ButtonState = _ButtonState;
}

void UI_Button::BUTTON_STATE_HOVERED_UPDATE()
{
	CheckButtonClick();
}

void UI_Button::CheckButtonCollision()
{
	if (nullptr != MainCollision)
	{

		MainCollision->CollisionCallBack
		(
			CollisionOrder::Mouse
			, CollisionType::Rect // _this�� �浹ü Ÿ��
			, CollisionType::CirCle // _Other�� �浹ü Ÿ��
			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{
				GameEngineActor* thisActor = _this->GetActor();
				UI_Button* ButtonPtr = dynamic_cast<UI_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
			}

			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{
				GameEngineActor* thisActor = _this->GetActor();
				UI_Button* ButtonPtr = dynamic_cast<UI_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
			}

			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{
				GameEngineActor* thisActor = _this->GetActor();
				UI_Button* ButtonPtr = dynamic_cast<UI_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);
			}
			);

	}
}

void UI_Button::CheckButtonClick()
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
