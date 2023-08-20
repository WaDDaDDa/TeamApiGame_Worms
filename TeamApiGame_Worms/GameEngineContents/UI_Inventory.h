#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
#include "UI_Button.h"
#include "UI_Mouse.h"

class UI_Inventory : public GameEngineActor
{
public:
	UI_Inventory();
	~UI_Inventory();

	UI_Inventory(const UI_Inventory& _Other) = delete;
	UI_Inventory(UI_Inventory&& _Other) noexcept = delete;
	UI_Inventory& operator=(const UI_Inventory& _Other) = delete;
	UI_Inventory& operator=(UI_Inventory&& _Other) noexcept = delete;

	std::vector<UI_Button*> AllWeaponButtons;

	bool GetActiveState() const
	{
		return m_bIsActive;
	}

	GameEngineRenderer* GetWeaponNameRenderer()
	{
		return WeaponNameRenderer;
	}

	// 인벤토리의 활성 여부를 현재 상태의 반대로 설정합니다.
	void SwitchActiveState()
	{
		m_bIsActive = !m_bIsActive;
	}

	void ShowInventory(bool _isActive, float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* WeaponNameRenderer = nullptr;

	UI_Mouse* MouseUI = nullptr;

	UI_Button* Btn_Weapon_Bazooka = nullptr;

	bool m_bIsActive = false;

};