#pragma once
#include <GameEngineCore/GameEngineActor.h>

/*
	여러개의 이미지를 클릭할 때마다 번갈아가면서 출력하는 버튼의 경우
	지금 만들어놓은 로직이 작동하지 않기 때문에 수정이 필요하다.

	단순히 클릭하면 어떤 함수가 작동하는 시스템은 이미 존재하기 때문에
	초기화 단계에서 필요한 이미지를 모두 가져와서 로딩해놓고
	=> 특정 경로 안에서 찾으려는 이름이 있는 모든 텍스처를 로딩한다?
	=> 순서대로 불러내서 내부에서 또 소팅을 하고 집어넣어야한다.
	=> 비효율적? 그냥 버튼을 상속하는 파생 클래스들로 만들어서 따로 설정해보자

	클릭하면 바뀐 이미지로 버튼 텍스쳐를 바꾸도록 하는 방향으로 구현해보자

*/


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

	GameEngineCollision* MainCollision = nullptr;

protected:
	void Start() override;
	void Update(float _Delta) override;


	GameEngineRenderer* MainRenderer = nullptr;


	BUTTON_STATE ButtonState;

	void StateUpdate();
	void ChangeState(BUTTON_STATE _ButtonState);

	void ClickedMouseButtonDown();
	void CheckButtonClick();

private:
	// 필요에 따라 하나의 UI_Button 클래스에 사용할 기능을 직접 지정할 수 있게 해주는 함수 포인터입니다.
	BTN_FUNC	m_pFunc;

	// 함수 포인터에 등록할 1번 함수 
	DWORD_PTR	m_param1;

	// 함수 포인터에 등록할 2번 함수 
	DWORD_PTR	m_param2;



	bool m_IsActive = true;
	bool m_UseHighlighter = false;

	std::string ImageName;
	std::string HighlighterName;



};