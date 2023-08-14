#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_TeamHpBar : public GameEngineActor
{
public:
	UI_TeamHpBar();
	~UI_TeamHpBar();

	UI_TeamHpBar(const UI_TeamHpBar& _Other) = delete;
	UI_TeamHpBar(UI_TeamHpBar&& _Other) noexcept = delete;
	UI_TeamHpBar& operator=(const UI_TeamHpBar& _Other) = delete;
	UI_TeamHpBar& operator=(UI_TeamHpBar&& _Other) noexcept = delete;

	static UI_TeamHpBar* GetTimerUI()
	{
		return TeamHpBarUI;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

	static UI_TeamHpBar* TeamHpBarUI;

	GameEngineRenderer* TeamNameRenderer = nullptr;
	GameEngineRenderer* TeamFlagRenderer = nullptr;
	GameEngineRenderer* TeamHpRenderer = nullptr;

};

