#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_FadeObject : public GameEngineActor
{
public:
	enum class FADE_STATE
	{
		FADE_STATE_IN,
		FADE_STATE_OUT
	};

public:
	UI_FadeObject();
	~UI_FadeObject();

	UI_FadeObject(const UI_FadeObject& _Other) = delete;
	UI_FadeObject(UI_FadeObject&& _Other) noexcept = delete;
	UI_FadeObject& operator=(const UI_FadeObject& _Other) = delete;
	UI_FadeObject& operator=(UI_FadeObject&& _Other) noexcept = delete;

	float GetCurrentAlpha()
	{
		return m_fCurrentAlpha;
	}

	void ChangeState(FADE_STATE _FadeState);

	FADE_STATE FadeState;


	void SetFadeOutMode();
	void SetFadeInMode();

	void FadeIn(float _Delta);
	void FadeOut(float _Delta);

private:
	void Start() override;
	void Update(float _Delta) override;

	void StateUpdate(float _Delta);

	GameEngineRenderer* MainRenderer = nullptr;

	float m_fCurrentAlpha = 0.0f;
};

