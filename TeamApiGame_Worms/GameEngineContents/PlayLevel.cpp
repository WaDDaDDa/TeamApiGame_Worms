#include "PlayLevel.h"


#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>

#include "BackGround.h"
#include "Ground.h"
#include "Player.h"
#include "GameTurn.h"
#include "MouseObject.h"

#pragma region UI���� ����� ��� & �Լ� ���� ����
#include "UI_Mouse.h"
#include "UI_Button.h"
#include "ContentsDefine.h"

void ChangeLevel(DWORD_PTR, DWORD_PTR);
#pragma endregion

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

Ground* PlayLevel::GetGround() const
{
	if (nullptr == GroundPtr)
	{
		MsgBoxAssert("Ground�� �������� ����ä�� ���Ƿ��߽��ϴ�.");
		return nullptr;
	}
	
	return GroundPtr;
}

void PlayLevel::Start()
{
	//���߿� LobbyLevel���� �޾ƿð�
	{
		GroundFileName = "MapBooks.Bmp";
		GroundPixelFileName = "MapBooks_Ground.Bmp";

	}


	if (false == ResourcesManager::GetInst().IsLoadTexture(GroundFileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(GroundFileName));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(GroundPixelFileName));
	}

	CreateActor<MouseObject>();
}



void PlayLevel::LevelStart(GameEngineLevel* _NextLevel)
{
#pragma region UI ����
	CreateActor<UI_Mouse>();

	//// UI ���� �׽�Ʈ
	//UI_Button* Btn_StartGame = CreateActor<UI_Button>();
	//Btn_StartGame->InitButtonData("UI_Button_StartGame", float4{ UI_BUTTON_START_WITDH, UI_BUTTON_START_HEIGHT });
	//Btn_StartGame->SetPos({ 400, 1000 });
	//Btn_StartGame->SetClickedCallBack(ChangeLevel, 0, 0);
#pragma endregion


	{

		GroundPtr = CreateActor<Ground>();
		GroundPtr->Init(GroundFileName, GroundPixelFileName);

		BackGroundPtr = CreateActor<BackGround>();
		BackGroundPtr->Init("Back.bmp",GroundPtr->GetGroundTexture()->GetScale());
		
	}



	{
		Player* TestPlayer = CreateActor<Player>();
		TestPlayer->SetGroundTexture(GroundPixelFileName);
		TestPlayer->SetPos(float4{ 100, 100 });
	}

	{
		Player* TestPlayer = CreateActor<Player>();
		TestPlayer->SetGroundTexture(GroundPixelFileName);
		TestPlayer->SetPos(float4{ 400, 100 });
	}

	{
		Player* TestPlayer = CreateActor<Player>();
		TestPlayer->SetGroundTexture(GroundPixelFileName);
		TestPlayer->SetPos(float4{ 700, 100 });
	}

	{
		Player* TestPlayer = CreateActor<Player>();
		TestPlayer->SetGroundTexture(GroundPixelFileName);
		TestPlayer->SetPos(float4{ 1000, 100 });
	}

	CreateActor<GameTurn>();
}

void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('J'))
	{
		GameEngineLevel::CollisionDebugRenderSwitch();
		GroundPtr->SwitchRender();
	}
}

void PlayLevel::Release()
{

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}


#pragma region UI �Լ� ������ ��Ͽ� �Լ�

void ChangeLevel(DWORD_PTR, DWORD_PTR)
{
	GameEngineCore::ChangeLevel("TitleLevel");
}

#pragma endregion