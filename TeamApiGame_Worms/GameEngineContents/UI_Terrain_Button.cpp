#include "UI_Terrain_Button.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "GameStateManager.h"

UI_Terrain_Button::UI_Terrain_Button()
{
}

UI_Terrain_Button::~UI_Terrain_Button()
{
}



void UI_Terrain_Button::Start()
{
	// 리소스 로딩
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\Lobby\\SelectMap\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("LobbyMap_MapBooks.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LobbyMap_MapBooks.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("LobbyMap_MapCars.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LobbyMap_MapCars.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("LobbyMap_MapCity.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LobbyMap_MapCity.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("LobbyMap_MapTrain.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LobbyMap_MapTrain.bmp"));
	}

	MainRenderer = CreateRenderer(RenderOrder::UI);

	MainRenderer->SetRenderScale({ 400, 200 });

	MainRenderer->SetTexture("LobbyMap_MapBooks.bmp");

	MainCollision = CreateCollision(CollisionOrder::UI);
	MainCollision->SetCollisionType(CollisionType::Rect);
	MainCollision->SetCollisionScale({ 400, 200 });

	ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);
}

void UI_Terrain_Button::Update(float _Delta)
{
	StateUpdate();
	CheckButtonCollision();
}


void UI_Terrain_Button::ChangeSelectMap()
{
	if (m_SelectIndex < 3)
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
		MainRenderer->SetTexture("LobbyMap_MapBooks.bmp");
		GameStateManager::GameState->SetStageName("MapBooks");
		break;

	case 1:
		MainRenderer->SetTexture("LobbyMap_MapCars.bmp");
		GameStateManager::GameState->SetStageName("MapCars");
		break;

	case 2:
		MainRenderer->SetTexture("LobbyMap_MapCity.bmp");
		GameStateManager::GameState->SetStageName("MapCity");
		break;

	case 3:
		MainRenderer->SetTexture("LobbyMap_MapTrain.bmp");
		GameStateManager::GameState->SetStageName("MapTrain");
		break;

	default:
		break;
	}

	ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
}

void UI_Terrain_Button::StateUpdate()
{
	switch (ButtonState)
	{
	case BUTTON_STATE::BUTTON_STATE_HOVERED:
		CheckButtonClick();
		break;

	case BUTTON_STATE::BUTTON_STATE_UNHOVERED:
		break;

	case BUTTON_STATE::BUTTON_STATE_CLICKED:
		ChangeSelectMap();
		break;

	default:
		break;
	}
}

void UI_Terrain_Button::ChangeState(BUTTON_STATE _ButtonState)
{
	ButtonState = _ButtonState;
}

void UI_Terrain_Button::CheckButtonClick()
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


void UI_Terrain_Button::CheckButtonCollision()
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
				UI_Terrain_Button* ButtonPtr = dynamic_cast<UI_Terrain_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
			}

			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{

			}

				, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{
				GameEngineActor* thisActor = _this->GetActor();
				UI_Terrain_Button* ButtonPtr = dynamic_cast<UI_Terrain_Button*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);
			}
			);

	}
}

