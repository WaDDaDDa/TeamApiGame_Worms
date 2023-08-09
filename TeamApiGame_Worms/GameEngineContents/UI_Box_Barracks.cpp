#include "UI_Box_Barracks.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include "UI_Button.h"
#include <GameEngineCore/GameEngineLevel.h>

UI_Box_Barracks::UI_Box_Barracks()
{
}

UI_Box_Barracks::~UI_Box_Barracks()
{
}

void UI_Box_Barracks::Start()
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\Lobby\\");

	// Box 레이아웃 세팅용 리소스
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Barracks.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Barracks.bmp"));
	}

	// 팀 버튼 세팅용 리소스
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Teams_1Up.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Teams_1Up.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Teams_2Up.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Teams_2Up.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Teams_3Up.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Teams_3Up.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Teams_4Up.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Teams_4Up.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Teams_5Up.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Teams_5Up.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Teams_6Up.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Teams_6Up.bmp"));
	}

	MainRenderer = CreateRenderer(RenderOrder::UI);
	MainRenderer->SetRenderScale({ 530, 250 });
	MainRenderer->SetTexture("UI_Barracks.bmp");


	// Box 내부의 버튼 세팅
	UI_Button* TestButton = GetLevel()->CreateActor<UI_Button>();
	TestButton->InitButtonData("UI_Teams_1Up", { 100, 24 }, false);
	TestButton->SetPos({ 740, 342 });

	UI_Button* TestButton2 = GetLevel()->CreateActor<UI_Button>();
	TestButton2->InitButtonData("UI_Teams_2Up", { 100, 24 }, false);
	TestButton2->SetPos({ 740, 372 });

	UI_Button* TestButton3 = GetLevel()->CreateActor<UI_Button>();
	TestButton3->InitButtonData("UI_Teams_3Up", { 100, 24 }, false);
	TestButton3->SetPos({ 740, 402 });

	UI_Button* TestButton4 = GetLevel()->CreateActor<UI_Button>();
	TestButton4->InitButtonData("UI_Teams_4Up", { 100, 24 }, false);
	TestButton4->SetPos({ 740, 432 });

	UI_Button* TestButton5 = GetLevel()->CreateActor<UI_Button>();
	TestButton5->InitButtonData("UI_Teams_5Up", { 100, 24 }, false);
	TestButton5->SetPos({ 740, 462 });

	UI_Button* TestButton6 = GetLevel()->CreateActor<UI_Button>();
	TestButton6->InitButtonData("UI_Teams_6Up", { 100, 24 }, false);
	TestButton6->SetPos({ 740, 492 });
}

void UI_Box_Barracks::Update(float _Delta)
{
}
