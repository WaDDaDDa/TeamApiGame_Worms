#include "UI_Inventory.h"

#include "UI_Button.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"
#include "GameTurn.h"

void ChangeWeapon(DWORD_PTR, DWORD_PTR);

UI_Inventory::UI_Inventory()
{
}

UI_Inventory::~UI_Inventory()
{
}

void UI_Inventory::Start()
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\Inventory\\");

	// 리소스 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Inventory_Weapon.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Inventory_Weapon.bmp"));
	}

	// 배경 렌더러 세팅
	MainRenderer = CreateUIRenderer("UI_Inventory_Weapon.bmp", RenderOrder::UI);
//	MainRenderer = CreateRenderer("UI_Inventory_Weapon.bmp", RenderOrder::UI);
	MainRenderer->SetRenderScale({ 180, 400 });


	// 무기 이름 출력용 렌더러 세팅
	WeaponNameRenderer = CreateUIRenderer(RenderOrder::UI);
	WeaponNameRenderer->SetRenderScale({ 100, 100 });
	WeaponNameRenderer->SetText("TEST TEXT", 14);
	WeaponNameRenderer->SetRenderPos({ -80 , 182 });

	//// 위치 테스트용


//	UI_Button* Btn_Weapon_Bazooka = GetLevel()->CreateActor<UI_Button>();
//	Btn_Weapon_Bazooka->InitButtonData("UI_ButtonHighlighter", { 30, 30 }, true);
//
//	Btn_Weapon_Bazooka->SetPos({ 1317, 1616 });
//
//
//	Btn_Weapon_Bazooka->SetPos({ 1359, 347 });
//	Btn_Weapon_Bazooka->SetPos({ 1125, 347 }); // ON 최종 위치
//	Btn_Weapon_Bazooka->SetClickedCallBack(ChangeWeapon, 0, 0);
//	AllWeaponButtons.push_back(Btn_Weapon_Bazooka);






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

		for (int i = 0; i < AllWeaponButtons.size(); i++)
		{
			AllWeaponButtons[i]->AddPos(NextPos);
		}
	}

	else if (false == m_bIsActive && GetPos().X < 1400)
	{
		float4 NextPos = GetPos() * float4::RIGHT * _Delta;
		AddPos(NextPos);

		for (int i = 0; i < AllWeaponButtons.size(); i++)
		{
			AllWeaponButtons[i]->AddPos(NextPos);
		}
	}

}

void ChangeWeapon(DWORD_PTR, DWORD_PTR)
{
	//ChangeState(PlayerState::BazookaOn);
}
