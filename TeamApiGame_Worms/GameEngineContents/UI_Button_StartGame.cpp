#include "UI_Button_StartGame.h"
#pragma region Headers
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCore.h>
#pragma endregion

#define UI_BUTTON_START_WITDH  100
#define UI_BUTTON_START_HEIGHT 100

UI_Button_StartGame::UI_Button_StartGame()
{

}

UI_Button_StartGame::~UI_Button_StartGame()
{
}

void UI_Button_StartGame::Start()
{
	InitButtonData("UI_Button_StartGame", float4{ UI_BUTTON_START_WITDH, UI_BUTTON_START_HEIGHT });
}

void UI_Button_StartGame::Update(float _Delta)
{
	OnClickEvent();
}

void UI_Button_StartGame::OnClickEvent()
{
	if (BUTTON_STATE::BUTTON_STATE_CLICKED == GetMouseState())
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
	
}
