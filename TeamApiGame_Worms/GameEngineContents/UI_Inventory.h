#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
#include "UI_Button.h"

class UI_Inventory : public GameEngineActor
{
public:
	UI_Inventory();
	~UI_Inventory();

	UI_Inventory(const UI_Inventory& _Other) = delete;
	UI_Inventory(UI_Inventory&& _Other) noexcept = delete;
	UI_Inventory& operator=(const UI_Inventory& _Other) = delete;
	UI_Inventory& operator=(UI_Inventory&& _Other) noexcept = delete;

	std::vector<UI_Button> AllButtons;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* MainRenderer = nullptr;

};