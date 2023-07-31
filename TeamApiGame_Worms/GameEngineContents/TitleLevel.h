#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class TitleLevel : public GameEngineLevel
{
private:
	enum class TITLE_STATE
	{
		TITLE_STATE_INTRO,
		TITLE_STATE_SHOWTITLE,
		TITLE_STATE_MAIN
	};

public:
	TitleLevel();
	~TitleLevel();

	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	TITLE_STATE TitleState;

	void StateUpdate(float _Delta);
	void ChangeState(TITLE_STATE _TitleState);

	void Title_Intro_Start();
	void Title_ShowTitle_Start();
	void Title_Main_Start();

	void Title_Intro_Update(float _Delta);
	void Title_ShowTitle_Update(float _Delta);
	void Title_Main_Update(float _Delta);

};