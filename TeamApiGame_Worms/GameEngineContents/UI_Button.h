#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_Button : public GameEngineActor
{
protected:
	enum class BUTTON_STATE
	{
		BUTTON_STATE_HOVERED,
		BUTTON_STATE_UNHOVERED,
		BUTTON_STATE_CLICKED
	};

public:
	UI_Button();
	~UI_Button();

	UI_Button(const UI_Button& _Other) = delete;
	UI_Button(UI_Button&& _Other) noexcept = delete;
	UI_Button& operator=(const UI_Button& _Other) = delete;
	UI_Button& operator=(UI_Button&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	UI_Button& InitButtonData(const std::string _ButtonImage, float4 _ButtonScale);

	GameEngineRenderer* GetRenderer()
	{
		return MainRenderer;
	}

	GameEngineCollision* GetCollision()
	{
		return MainCollision;
	}

	BUTTON_STATE GetMouseState()
	{
		return ButtonState;
	}


	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineCollision* MainCollision = nullptr;

private:
	BUTTON_STATE ButtonState;

	void StateUpdate();
	void ChangeState(BUTTON_STATE _ButtonState);

	void CheckButtonCollision();
	void CheckButtonClick();

	bool m_IsActive = true;

};