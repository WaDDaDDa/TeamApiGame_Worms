#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_Wind : public GameEngineActor
{
public:
	UI_Wind();
	~UI_Wind();

	UI_Wind(const UI_Wind& _Other) = delete;
	UI_Wind(UI_Wind&& _Other) noexcept = delete;
	UI_Wind& operator=(const UI_Wind& _Other) = delete;
	UI_Wind& operator=(UI_Wind&& _Other) noexcept = delete;

	static UI_Wind* GetWindUI()
	{
		return WindUI;
	}


	void ChangeWindBarDir(float4 _WindDir);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

	static UI_Wind* WindUI;

	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* WindDirRenderer_Left = nullptr;
	GameEngineRenderer* WindDirRenderer_Right = nullptr;


};

