#include "UI_Meteor.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "ContentsEnum.h"

UI_Meteor::UI_Meteor()
{
}

UI_Meteor::~UI_Meteor()
{
}

void UI_Meteor::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Meteor.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\Lobby\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("UI_Meteor.bmp"), 1, 129);
	}

	MainRenderer = CreateRenderer(RenderOrder::BackGroundEffect);

	MainRenderer->SetRenderScale({ 42, 42 });

	MainRenderer->CreateAnimation("MeteorFall", "UI_Meteor.bmp", 0, 128, 0.02f, true);

	MainRenderer->ChangeAnimation("MeteorFall");

	MeteorDeathPos = GameEngineWindow::MainWindow.GetScale().Y;
	
}

void UI_Meteor::Update(float _Delta)
{

	AddPos({ float4::RIGHT.X * _Delta * 150.0f, float4::DOWN.Y * _Delta * 150.0f });

	if (GetPos().Y > MeteorDeathPos)
	{
		Death();
	}
}
