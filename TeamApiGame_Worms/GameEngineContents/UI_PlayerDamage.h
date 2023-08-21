#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_PlayerDamage : public GameEngineActor
{
public:
	UI_PlayerDamage();
	~UI_PlayerDamage();

	UI_PlayerDamage(const UI_PlayerDamage& _Other) = delete;
	UI_PlayerDamage(UI_PlayerDamage&& _Other) noexcept = delete;
	UI_PlayerDamage& operator=(const UI_PlayerDamage& _Other) = delete;
	UI_PlayerDamage& operator=(UI_PlayerDamage&& _Other) noexcept = delete;

	void UpdateData_PlayerDamageUI(float4 _TargetPos, int _PlayerDamage, int _PlayerIndex);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* DamageTextRenderer = nullptr;
};