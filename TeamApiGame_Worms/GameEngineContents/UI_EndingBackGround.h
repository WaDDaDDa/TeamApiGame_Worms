#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_EndingBackGround : public GameEngineActor
{
public:
	UI_EndingBackGround();
	~UI_EndingBackGround();

	UI_EndingBackGround(const UI_EndingBackGround & _Other) = delete;
	UI_EndingBackGround(UI_EndingBackGround && _Other) noexcept = delete;
	UI_EndingBackGround& operator=(const UI_EndingBackGround & _Other) = delete;
	UI_EndingBackGround& operator=(UI_EndingBackGround && _Other) noexcept = delete;

protected:
	void Start() override;

private:
	GameEngineRenderer* MainRenderer = nullptr;

};