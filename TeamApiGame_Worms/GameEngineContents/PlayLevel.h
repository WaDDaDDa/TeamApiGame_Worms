
#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "UI_Inventory.h"

class Ground;
class GameStateManager;
class PlayLevel :public GameEngineLevel
{
public:
	PlayLevel();
	~PlayLevel();

	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(const PlayLevel&& _Other) noexcept = delete;

	Ground* GetGround() const;
	

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	Ground* GroundPtr=nullptr;
	class BackGround* BackGroundPtr = nullptr;
	std::string GroundFileName = "";
	std::string GroundPixelFileName = "";

	float CloudRespawn = 0.0f;
	float BackGroundEffectRespawn = 0.0f;

	void PlayerSetting(size_t _PlayerCount);


	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	

	// 추후에 매니저로 따로 빼거나 수정할 예정
	UI_Inventory* Inven = nullptr;

};

