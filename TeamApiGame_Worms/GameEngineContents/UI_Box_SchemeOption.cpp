#include "UI_Box_SchemeOption.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include "UI_Button.h"
#include <GameEngineCore/GameEngineLevel.h>

UI_Box_SchemeOption::UI_Box_SchemeOption()
{
}

UI_Box_SchemeOption::~UI_Box_SchemeOption()
{
}

void UI_Box_SchemeOption::Start()
{
	// 레이아웃 리소스 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_SchemeOption.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\Lobby\\SchemeOption\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_SchemeOption.bmp"));
	}

	MainRenderer = CreateRenderer(RenderOrder::UI);
	MainRenderer->SetRenderScale({ 530, 250 });
	MainRenderer->SetTexture("UI_SchemeOption.bmp");

	UI_Button* Btn_GameOptions = GetLevel()->CreateActor<UI_Button>();
	Btn_GameOptions->InitButtonData("UI_Gameoptions", { 230, 180 }, true);
	Btn_GameOptions->SetPos({ 250, 410 });

	UI_Button* Btn_WeaponOptions = GetLevel()->CreateActor<UI_Button>();
	Btn_WeaponOptions->InitButtonData("UI_WeaponOptions", { 230, 180 }, true);
	Btn_WeaponOptions->SetPos({ 490, 410 });

}

void UI_Box_SchemeOption::Update(float _Delta)
{
}
