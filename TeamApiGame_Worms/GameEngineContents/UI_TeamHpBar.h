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

	float GetCurHpBarAmount() const
	{
		return CurHpBarAmount;
	}

	void SetMaxPlayerHp(int _MaxPlayerHp)
	{
		MaxHpBarAmount = static_cast<float>(_MaxPlayerHp);
	}

	void SetCurPlayerHp(int _CurPlayerHp)
	{
		CurHpBarAmount = static_cast<float>(_CurPlayerHp);
	}

	void SetHpBarWidth(float _HpBarWidth)
	{
		HpBarWidth = static_cast<float>(_HpBarWidth);
	}

	void InitDecreaseHpBar(int _DamagedHp);
	void DecreaseHpBar();

	void InitMoveSortedHpbars(float4 _StartPos, float4 _DestPos, float _MoveSpeed);
	void MoveSortedHpBars(float _Delta);


	GameEngineRenderer* TeamNameRenderer = nullptr;
	GameEngineRenderer* TeamFlagRenderer = nullptr;
	GameEngineRenderer* TeamHpRenderer = nullptr;




protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	static UI_TeamHpBar* TeamHpBarUI;

	// HpBar 최대치
	float	MaxHpBarAmount			=	100.0f;
	// 현재 HpBar 수치
	float	CurHpBarAmount		= MaxHpBarAmount;
	// HpBar 목표 감소치
	float	TargetHpBarAmount	=	0.0f;
	float	HpBarWidth			=	100.0f;

	float	MoveDeltaTime;
	float	MoveSpeed;
	float	MoveLerpDeltaTime = 0.0f;

	bool	trigger_UpdateHP = false;
	bool	trigger_SortHp = false;

	float4	StartMoveHpBarPos;
	float4	DestMoveHpBarPos;
	float4	CurHpBarPos;

	int		OriginScaleX = 100;
	int		CurScaleX = 100;


};