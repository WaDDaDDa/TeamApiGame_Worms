#include "UI_Wind.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"

#include "Wind.h"

UI_Wind* UI_Wind::WindUI = nullptr;

UI_Wind::UI_Wind()
{
	WindUI = this;
}

UI_Wind::~UI_Wind()
{
}

void UI_Wind::Start()
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\Windbar\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_WindBarBase.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_WindBarBase.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_WindBarHider.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("UI_WindBarHider.bmp"), 1, 1);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_WindBar.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("UI_WindBar.bmp"), 5, 4);
	}


	// 렌더러 설정
	MainRenderer = CreateUIRenderer("UI_WindBarBase.bmp", RenderOrder::UI);
	MainRenderer->SetRenderScale({ 181, 17 });

	// 바람 방향 렌더러 설정
	WindDirRenderer_Left = CreateUIRenderer(RenderOrder::UI);
	WindDirRenderer_Left->SetRenderPos({ -45 , 0});
	WindDirRenderer_Left->CreateAnimation("WIND_ANIM_LEFT_FLOW", "UI_WindBar.bmp", 0, 7, 0.1f, true);
	WindDirRenderer_Left->CreateAnimation("WIND_ANIM_LEFT_HIDE", "UI_WindBarHider.bmp", 0, 0, 0.1f, false);
	WindDirRenderer_Left->ChangeAnimation("WIND_ANIM_LEFT_HIDE");

	WindDirRenderer_Right = CreateUIRenderer(RenderOrder::UI);
	WindDirRenderer_Right->SetRenderPos({ 45 , 0 });
	WindDirRenderer_Right->CreateAnimation("WIND_ANIM_RIGHT_FLOW", "UI_WindBar.bmp", 8, 15, 0.1f, true);
	WindDirRenderer_Right->CreateAnimation("WIND_ANIM_RIGHT_HIDE", "UI_WindBarHider.bmp", 0, 0, 0.1f, false);
	WindDirRenderer_Right->ChangeAnimation("WIND_ANIM_RIGHT_HIDE");
}


void UI_Wind::ChangeWindBarDir(float4 _WindDir)
{
	if (float4::LEFT == _WindDir)
	{
		WindDirRenderer_Left->ChangeAnimation("WIND_ANIM_LEFT_FLOW");
		WindDirRenderer_Right->ChangeAnimation("WIND_ANIM_RIGHT_HIDE");
	}

	else if (float4::RIGHT == _WindDir)
	{
		WindDirRenderer_Left->ChangeAnimation("WIND_ANIM_LEFT_HIDE");
		WindDirRenderer_Right->ChangeAnimation("WIND_ANIM_RIGHT_FLOW");
	}
}


void UI_Wind::Update(float _Delta)
{
	float4 SetWindDir = Wind::GetWind()->GetWindDir();

	ChangeWindBarDir(SetWindDir);

}


