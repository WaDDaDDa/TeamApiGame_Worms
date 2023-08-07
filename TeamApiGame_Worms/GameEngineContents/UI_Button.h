#pragma once
#include <GameEngineCore/GameEngineActor.h>

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

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

	// 버튼이 클릭되었을 때 호출해줄 콜백 함수를 등록해주는 함수입니다.
	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		m_pFunc = _pFunc;
		m_param1 = _param1;
		m_param2 = _param2;
	}


	UI_Button& InitButtonData(const std::string _ButtonImage, float4 _ButtonScale, bool _UseHighlighter);

	void HighlighterOn();

	void HighlighterOff();


protected:
	void Start() override;
	void Update(float _Delta) override;

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

	void CheckButtonCollision();

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineCollision* MainCollision = nullptr;

private:
	// 필요에 따라 하나의 UI_Button 클래스에 사용할 기능을 직접 지정할 수 있게 해주는 함수 포인터입니다.
	BTN_FUNC	m_pFunc;

	// 함수 포인터에 등록할 1번 함수 
	DWORD_PTR	m_param1;

	// 함수 포인터에 등록할 2번 함수 
	DWORD_PTR	m_param2;

	BUTTON_STATE ButtonState;

	void StateUpdate();
	void ChangeState(BUTTON_STATE _ButtonState);

	void ClickedMouseButtonDown();
	void CheckButtonClick();

	bool m_IsActive = true;
	bool m_UseHighlighter = false;

	std::string ImageName;
	std::string HighlighterName;



};