#include "UI_Inventory.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"

UI_Inventory::UI_Inventory()
{
}

UI_Inventory::~UI_Inventory()
{
}

void UI_Inventory::Start()
{
	// 리소스 로딩

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Inventory_Base.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\Inventory\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("UI_Inventory_Base.bmp"), 1, 1);
	}

	MainRenderer = CreateUIRenderer("UI_Inventory_Base.bmp", RenderOrder::UI);
	MainRenderer->SetRenderScale({ 180, 400 });

}

void UI_Inventory::Update(float _Delta)
{
	ShowInventory(m_bIsActive, _Delta);
}

void UI_Inventory::ShowInventory(bool _isActive, float _Delta)
{
	// 활성 상태가 바뀜에 따라 위치를 전환합니다.
	if (true == m_bIsActive && GetPos().X > 1180)
	{
		float4 NextPos = GetPos() * float4::LEFT * _Delta;
		AddPos(NextPos);
	}

	else if (false == m_bIsActive && GetPos().X < 1400)
	{
		float4 NextPos = GetPos() * float4::RIGHT * _Delta;
		AddPos(NextPos);
	}

}
