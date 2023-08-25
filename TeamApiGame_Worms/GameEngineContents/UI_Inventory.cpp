#include "UI_Inventory.h"

#include "UI_Button.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"
#include "GameTurn.h"
#include "UI_Mouse.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include "Player.h"

UI_Inventory* UI_Inventory::InventoryUI = nullptr;

void ChageSelectWeapon(int _SelectedWeapon);

UI_Inventory::UI_Inventory()
{
	InventoryUI = this;
}

UI_Inventory::~UI_Inventory()
{
}

void UI_Inventory::Start()
{
	// 배경 리소스 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Inventory_Filled.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\Inventory\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Inventory_Filled.bmp"));
	}

	// 배경 렌더러 세팅
	MainRenderer = CreateUIRenderer("UI_Inventory_Filled.bmp", RenderOrder::UI);
	MainRenderer->SetRenderScale({ 180, 400 });

	// 무기 이름 출력용 렌더러 세팅
	WeaponNameRenderer = CreateUIRenderer(RenderOrder::UI);
	WeaponNameRenderer->SetRenderScale({ 100, 100 });
	WeaponNameRenderer->SetText(" ", 14);
	WeaponNameRenderer->SetRenderPos({ -80 , 182 });

#pragma region 무기 버튼 세팅

	// Bazooka
	UI_Button* Btn_Weapon_Bazooka = GetLevel()->CreateActor<UI_Button>();
	Btn_Weapon_Bazooka->InitButtonData("UI_ButtonHighlighter", { 28, 28 }, true);
	Btn_Weapon_Bazooka->SetEnumValue(WeaponEnum::Bazooka);
	Btn_Weapon_Bazooka->SetPos({ 1358, 326 });
	Btn_Weapon_Bazooka->SetClickedCallBackEnum(ChageSelectWeapon);
	AllWeaponButtons.push_back(Btn_Weapon_Bazooka);

	// Homing Missile
	UI_Button* Btn_Weapon_HomingMissile = GetLevel()->CreateActor<UI_Button>();
	Btn_Weapon_HomingMissile->InitButtonData("UI_ButtonHighlighter", { 28, 28 }, true);
	Btn_Weapon_HomingMissile->SetEnumValue(WeaponEnum::HomingMissile);
	Btn_Weapon_HomingMissile->SetPos({ 1358, 355 });
	Btn_Weapon_HomingMissile->SetClickedCallBackEnum(ChageSelectWeapon);
	AllWeaponButtons.push_back(Btn_Weapon_HomingMissile);

	// Grenade
	UI_Button* Btn_Weapon_Grenade = GetLevel()->CreateActor<UI_Button>();
	Btn_Weapon_Grenade->InitButtonData("UI_ButtonHighlighter", { 28, 28 }, true);
	Btn_Weapon_Grenade->SetEnumValue(WeaponEnum::Granade);
	Btn_Weapon_Grenade->SetPos({ 1358, 384 });
	Btn_Weapon_Grenade->SetClickedCallBackEnum(ChageSelectWeapon);
	AllWeaponButtons.push_back(Btn_Weapon_Grenade);

	// Uzi
	UI_Button* Btn_Weapon_Uzi = GetLevel()->CreateActor<UI_Button>();
	Btn_Weapon_Uzi->InitButtonData("UI_ButtonHighlighter", { 28, 28 }, true);
	Btn_Weapon_Uzi->SetEnumValue(WeaponEnum::Uzi);
	Btn_Weapon_Uzi->SetPos({ 1358, 413 });
	Btn_Weapon_Uzi->SetClickedCallBackEnum(ChageSelectWeapon);
	AllWeaponButtons.push_back(Btn_Weapon_Uzi);

	// Sheep
	UI_Button* Btn_Weapon_Sheep = GetLevel()->CreateActor<UI_Button>();
	Btn_Weapon_Sheep->InitButtonData("UI_ButtonHighlighter", { 28, 28 }, true);
	Btn_Weapon_Sheep->SetEnumValue(WeaponEnum::Sheep);
	Btn_Weapon_Sheep->SetPos({ 1358, 442 });
	Btn_Weapon_Sheep->SetClickedCallBackEnum(ChageSelectWeapon);
	AllWeaponButtons.push_back(Btn_Weapon_Sheep);

	// Super Sheep
	UI_Button* Btn_Weapon_SuperSheep = GetLevel()->CreateActor<UI_Button>();
	Btn_Weapon_SuperSheep->InitButtonData("UI_ButtonHighlighter", { 28, 28 }, true);
	Btn_Weapon_SuperSheep->SetEnumValue(WeaponEnum::SuperSheep);
	Btn_Weapon_SuperSheep->SetPos({ 1358, 471 });
	Btn_Weapon_SuperSheep->SetClickedCallBackEnum(ChageSelectWeapon);
	AllWeaponButtons.push_back(Btn_Weapon_SuperSheep);

	// Air Strike
	UI_Button* Btn_Weapon_AirStrike = GetLevel()->CreateActor<UI_Button>();
	Btn_Weapon_AirStrike->InitButtonData("UI_ButtonHighlighter", { 28, 28 }, true);
	Btn_Weapon_AirStrike->SetEnumValue(WeaponEnum::AirStrike);
	Btn_Weapon_AirStrike->SetPos({ 1358, 500 });
	Btn_Weapon_AirStrike->SetClickedCallBackEnum(ChageSelectWeapon);
	AllWeaponButtons.push_back(Btn_Weapon_AirStrike);

	// Girder
	UI_Button* Btn_Weapon_Girder = GetLevel()->CreateActor<UI_Button>();
	Btn_Weapon_Girder->InitButtonData("UI_ButtonHighlighter", { 28, 28 }, true);
	Btn_Weapon_Girder->SetEnumValue(WeaponEnum::Girder);
	Btn_Weapon_Girder->SetPos({ 1358, 529 });
	Btn_Weapon_Girder->SetClickedCallBackEnum(ChageSelectWeapon);
	AllWeaponButtons.push_back(Btn_Weapon_Girder);

	// Teleport
	UI_Button* Btn_Weapon_Teleport = GetLevel()->CreateActor<UI_Button>();
	Btn_Weapon_Teleport->InitButtonData("UI_ButtonHighlighter", { 28, 28 }, true);
	Btn_Weapon_Teleport->SetEnumValue(WeaponEnum::Teleport);
	Btn_Weapon_Teleport->SetPos({ 1358, 558 });
	Btn_Weapon_Teleport->SetClickedCallBackEnum(ChageSelectWeapon);
	AllWeaponButtons.push_back(Btn_Weapon_Teleport);

	// Holy Hand Grenade
	UI_Button* Btn_Weapon_HolyHandGrenade = GetLevel()->CreateActor<UI_Button>();
	Btn_Weapon_HolyHandGrenade->InitButtonData("UI_ButtonHighlighter", { 28, 28 }, true);
	Btn_Weapon_HolyHandGrenade->SetEnumValue(WeaponEnum::HolyGranade);
	Btn_Weapon_HolyHandGrenade->SetPos({ 1358, 587 });
	Btn_Weapon_HolyHandGrenade->SetClickedCallBackEnum(ChageSelectWeapon);
	AllWeaponButtons.push_back(Btn_Weapon_HolyHandGrenade);

	// Concrete Donkey
	UI_Button* Btn_Weapon_ConcreteDonkey = GetLevel()->CreateActor<UI_Button>();
	Btn_Weapon_ConcreteDonkey->InitButtonData("UI_ButtonHighlighter", { 28, 28 }, true);
	Btn_Weapon_ConcreteDonkey->SetEnumValue(WeaponEnum::Donkey);
	Btn_Weapon_ConcreteDonkey->SetPos({ 1358, 616 });
	Btn_Weapon_ConcreteDonkey->SetClickedCallBackEnum(ChageSelectWeapon);
	AllWeaponButtons.push_back(Btn_Weapon_ConcreteDonkey);

#pragma endregion

	MouseUI = GetLevel()->CreateActor<UI_Mouse>();
	MouseUI->GetMouseUIRenderer()->Off();
}

void UI_Inventory::Update(float _Delta)
{
	ShowInventory(m_bIsActive, _Delta);
}

void UI_Inventory::ShowInventory(bool _isActive, float _Delta)
{
	// 활성 상태가 바뀜에 따라 위치를 전환합니다.
	if (true == m_bIsActive && GetPos().X > 1185)
	{
		GetWeaponNameRenderer()->SetText(" ", 14);
		MouseUI->GetMouseUIRenderer()->On();
		float4 MosuePos = { 1155, 373 };

		GameEngineWindow::MainWindow.SetCursorPos(MosuePos);

		float4 NextPos = GetPos() * float4::LEFT * _Delta;
		AddPos(NextPos);

		for (int i = 0; i < AllWeaponButtons.size(); i++)
		{
			AllWeaponButtons[i]->AddPos(NextPos);
		}
	}

	else if (false == m_bIsActive && GetPos().X < 1400)
	{
		MouseUI->GetMouseUIRenderer()->Off();

		float4 NextPos = GetPos() * float4::RIGHT * _Delta;
		AddPos(NextPos);

		for (int i = 0; i < AllWeaponButtons.size(); i++)
		{
			AllWeaponButtons[i]->AddPos(NextPos);
		}
	}

}

void ChageSelectWeapon(int _SelectedWeapon)
{

	WeaponEnum SelectedWeapon = static_cast<WeaponEnum>(_SelectedWeapon); ;

	Player* CurTurnPlayer = GameTurn::MainGameTurn->GetTurnPlayer();

	switch (SelectedWeapon)
	{
	case WeaponEnum::Bazooka:
		UI_Inventory::InventoryUI->GetInventoryUI()->GetWeaponNameRenderer()->SetText("Bazooka", 14);
		
		// 여기서 현재 턴 플레이어의 상태를 변경해서 최종적으로 선택한 Enum값에 맞는 무기를 사용하도록 합니다.
		// CurTurnPlayer->
		break;

	case WeaponEnum::HomingMissile:
		UI_Inventory::InventoryUI->GetInventoryUI()->GetWeaponNameRenderer()->SetText("Homing Missile", 14);

		break;

	case WeaponEnum::Granade:
		UI_Inventory::InventoryUI->GetInventoryUI()->GetWeaponNameRenderer()->SetText("Grenade", 14);

		break;

	case WeaponEnum::Uzi:
		UI_Inventory::InventoryUI->GetInventoryUI()->GetWeaponNameRenderer()->SetText("Uzi", 14);

		break;

	case WeaponEnum::Sheep:
		UI_Inventory::InventoryUI->GetInventoryUI()->GetWeaponNameRenderer()->SetText("Sheep", 14);

		break;

	case WeaponEnum::SuperSheep:
		UI_Inventory::InventoryUI->GetInventoryUI()->GetWeaponNameRenderer()->SetText("Super Sheep", 14);

		break;

	case WeaponEnum::AirStrike:
		UI_Inventory::InventoryUI->GetInventoryUI()->GetWeaponNameRenderer()->SetText("Air Strike", 14);

		break;

	case WeaponEnum::Girder:
		UI_Inventory::InventoryUI->GetInventoryUI()->GetWeaponNameRenderer()->SetText("Girder", 14);

		break;

	case WeaponEnum::Teleport:
		UI_Inventory::InventoryUI->GetInventoryUI()->GetWeaponNameRenderer()->SetText("Teleport", 14);
		break;

	case WeaponEnum::HolyGranade:
		UI_Inventory::InventoryUI->GetInventoryUI()->GetWeaponNameRenderer()->SetText("Holy Hand Grenade", 14);

		break;

	case WeaponEnum::Donkey:
		UI_Inventory::InventoryUI->GetInventoryUI()->GetWeaponNameRenderer()->SetText("Concrete Donkey", 14);

		break;

	default:
		break;
	}

}