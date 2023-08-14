#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_Timer : public GameEngineActor
{
public:
	UI_Timer();
	~UI_Timer();

	UI_Timer(const UI_Timer& _Other) = delete;
	UI_Timer(UI_Timer&& _Other) noexcept = delete;
	UI_Timer& operator=(const UI_Timer& _Other) = delete;
	UI_Timer& operator=(UI_Timer&& _Other) noexcept = delete;

	static UI_Timer* GetTimerUI()
	{
		return TimerUI;
	}


	void ChangeTimerColor(int _PlayerIndex);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

	static UI_Timer* TimerUI;

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* TimerTextRenderer = nullptr;
};

