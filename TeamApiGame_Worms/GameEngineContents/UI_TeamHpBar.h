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

	void SetMaxPlayerHp(int _MaxPlayerHp)
	{
		MaxHpBarAmount = _MaxPlayerHp;
	}

	void SetCurPlayerHp(int _CurPlayerHp)
	{
		CurHpBarAmount = _CurPlayerHp;
	}

	void SetHpBarWidth(float _HpBarWidth)
	{
		HpBarWidth = _HpBarWidth;
	}


	void InitDecreaseHpBar(int _DamagedHp);
	void DecreaseHpBar();


	GameEngineRenderer* TeamNameRenderer = nullptr;
	GameEngineRenderer* TeamFlagRenderer = nullptr;
	GameEngineRenderer* TeamHpRenderer = nullptr;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	static UI_TeamHpBar* TeamHpBarUI;

	// HpBar �ִ�ġ
	float	MaxHpBarAmount			=	100.0f;
	// ���� HpBar ��ġ
	float	CurHpBarAmount		=	0.0f;
	// HpBar ��ǥ ����ġ
	float	TargetHpBarAmount	=	0.0f;
	float	HpBarWidth			=	0.0f;
	float	HpBarWidthPivot		=	0.0f;
	bool	trigger_UpdateHP = false;

};