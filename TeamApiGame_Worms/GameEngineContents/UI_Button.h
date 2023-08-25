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

	// ��ư�� Ŭ���Ǿ��� �� ȣ������ �ݹ� �Լ��� ������ִ� �Լ��Դϴ�.
	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		m_pFunc = _pFunc;
		m_param1 = _param1;
		m_param2 = _param2;
	}

	void SetClickedCallBackEnum(void(*_pFuncEnum)(int _iWeaponEnum))
	{
		m_pFuncEnum = _pFuncEnum;
	}

	template<typename EnumValue>
	void SetEnumValue(EnumValue _EnumValue)
	{
		m_iEnumValue = static_cast<int>(_EnumValue);
	}

	UI_Button& InitButtonData(const std::string& _ButtonImage, float4 _ButtonScale, bool _UseHighlighter);

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

	bool m_IsActive = true;
	bool m_UseHighlighter = false;

	std::string ImageName;
	std::string HighlighterName;

private:
	// �ʿ信 ���� �ϳ��� UI_Button Ŭ������ ����� ����� ���� ������ �� �ְ� ���ִ� �Լ� �������Դϴ�.
	BTN_FUNC	m_pFunc;

	// �Լ� �����Ϳ� ����� 1�� �Լ� 
	DWORD_PTR	m_param1;

	// �Լ� �����Ϳ� ����� 2�� �Լ� 
	DWORD_PTR	m_param2;

	int m_iEnumValue = 0;

	void(*m_pFuncEnum)(int _iWeaponEnum) = nullptr;
};