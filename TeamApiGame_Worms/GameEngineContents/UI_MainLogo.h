#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

class UI_MainLogo : public GameEngineActor
{
public:
	UI_MainLogo();
	~UI_MainLogo();

	UI_MainLogo(const UI_MainLogo& _Other) = delete;
	UI_MainLogo(UI_MainLogo&& _Other) noexcept = delete;
	UI_MainLogo& operator=(const UI_MainLogo& _Other) = delete;
	UI_MainLogo& operator=(UI_MainLogo&& _Other) noexcept = delete;

	GameEngineRenderer* GetAnimRenderer() const
	{
		return AnimRenderer;
	}

	std::vector<GameEngineRenderer*> AllText;

	void SetShowAllTitleText()
	{
		IsAllTextShow = true;
	}

	bool GetShowAllTitleText() const
	{
		return IsAllTextShow;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* TitleRenderer = nullptr;
	GameEngineRenderer* AnimRenderer = nullptr;

	bool	IsAllTextShow = false;

	float	textTimer = 0.0f;
	int		textIndex = 0;
};