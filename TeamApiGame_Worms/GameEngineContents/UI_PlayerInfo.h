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

	// �÷��̾� �̸� ��¿� ������
	GameEngineRenderer* PlayerNameRenderer = nullptr;

	// �÷��̾� HP ��¿� ������
	GameEngineRenderer* PlayerHpBaseRenderer = nullptr;
	GameEngineRenderer* PlayerHpTextRenderer = nullptr;

	// ���� ���� �÷��̾ ��Ÿ���� ȭ��ǥ ��¿� ������
	GameEngineRenderer* PlayerArrowRenderer = nullptr;

	// �÷��̾��� HP�� �޾ƿ� ������
	int*		PlayerHp;
	float4*		PlayerPos;

	int			CurPlayerHp = 0;
	float4		CurPlayerPos = float4::ZERO;

	// �÷��̾��� �÷��� �����ϱ� ���� �ε���
	int			 PlayerColorIndex = 0;

	// �ؽ�Ʈ �÷��� �����ϱ� ���� �ε���
	unsigned int TextColor = 0;
	
};