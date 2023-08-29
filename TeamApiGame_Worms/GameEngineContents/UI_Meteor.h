#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_Meteor : public GameEngineActor
{
public:
	UI_Meteor();
	~UI_Meteor();

	UI_Meteor(const UI_Meteor& _Other) = delete;
	UI_Meteor(UI_Meteor&& _Other) noexcept = delete;
	UI_Meteor& operator=(const UI_Meteor& _Other) = delete;
	UI_Meteor& operator=(UI_Meteor&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* MainRenderer = nullptr;

	float MeteorDeathPos = 0.0f;

};
