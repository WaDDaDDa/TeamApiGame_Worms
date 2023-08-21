#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_PlayerInfo : public GameEngineActor
{
public:
	UI_PlayerInfo();
	~UI_PlayerInfo();

	UI_PlayerInfo(const UI_PlayerInfo& _Other) = delete;
	UI_PlayerInfo(UI_PlayerInfo&& _Other) noexcept = delete;
	UI_PlayerInfo& operator=(const UI_PlayerInfo& _Other) = delete;
	UI_PlayerInfo& operator=(UI_PlayerInfo&& _Other) noexcept = delete;

	static UI_PlayerInfo* GetPlayerInfoUI()
	{
		return PlayerInfoUI;
	}

	void SetPlayerColorIndex(int _ColorIndex);

//	void UpdateData_PlayerInfoUI(float4* _PlayerPos, int* _PlayerHp, bool _IsTurnPlayer);
	void UpdateData_PlayerInfoUI(int* _PlayerHp, bool _IsTurnPlayer, int _PlayerIndex);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	static UI_PlayerInfo* PlayerInfoUI;

	// 플레이어 이름 출력용 렌더러
	GameEngineRenderer* PlayerNameRenderer = nullptr;

	// 플레이어 HP 출력용 렌더러
	GameEngineRenderer* PlayerHpBaseRenderer = nullptr;
	GameEngineRenderer* PlayerHpTextRenderer = nullptr;

	// 현재 턴인 플레이어를 나타내는 화살표 출력용 렌더러
	GameEngineRenderer* PlayerArrowRenderer = nullptr;

	// 플레이어의 HP를 받아올 포인터
	int*		PlayerHp;
	float4*		PlayerPos;

	int			CurPlayerHp = 0;
	float4		CurPlayerPos = float4::ZERO;

	// 플레이어의 컬러를 결정하기 위한 인덱스
	int			 PlayerColorIndex = 0;

	// 텍스트 컬러를 결정하기 위한 인덱스
	unsigned int TextColor = 0;
	
};