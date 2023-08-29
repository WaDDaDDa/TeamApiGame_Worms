#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_LoadingCDRom : public GameEngineActor
{
public:
	UI_LoadingCDRom();
	~UI_LoadingCDRom();

	UI_LoadingCDRom(const UI_LoadingCDRom& _Other) = delete;
	UI_LoadingCDRom(UI_LoadingCDRom&& _Other) noexcept = delete;
	UI_LoadingCDRom& operator=(const UI_LoadingCDRom& _Other) = delete;
	UI_LoadingCDRom& operator=(UI_LoadingCDRom&& _Other) noexcept = delete;

	GameEngineRenderer* GetUICDRomRenderer()
	{
		return CDRomRenderer;
	}

	GameEngineRenderer* CDRomRenderer = nullptr;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineRenderer* MainRenderer = nullptr;


};