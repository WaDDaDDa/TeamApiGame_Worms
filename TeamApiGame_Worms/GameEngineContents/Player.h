#pragma once
#include "GravityActor.h"
#include <vector>

enum class PlayerState
{
	Idle,
	Move,
	Fire,
	Max
};

enum class PlayerDir
{
	Left,
	Right
};

// ���� : 
class Player : public GravityActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player & _Other) = delete;
	Player(Player && _Other) noexcept = delete;
	Player& operator=(const Player & _Other) = delete;
	Player& operator=(Player && _Other) noexcept = delete;

	class GameEngineRenderer* MainRenderer = nullptr;
	static float4 DirPos;

	static std::vector<Player*> GetAllPlayer()
	{
		return AllPlayer;
	}

	void SwitchIsTurnPlayer()
	{
		IsTurnPlayer = !IsTurnPlayer;
	}

	int GetHp()
	{
		return Hp;
	}

protected:
	PlayerState State = PlayerState::Max;
	PlayerDir Dir = PlayerDir::Left;
	std::string CurState = "";

	void ChangeState(PlayerState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void DirCheck();

	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void FireStart();
	void FireUpdate(float _Delta);

	void SetDirPosNormalize();

private:
	// PlayerStatus ����
	int Hp = 100;
	float PlayerSpeed = 100.0f;
	
	

	// �÷��̾� ��ü�� �����ϵ��� list�� �÷��̾� ����
	static std::vector<Player*> AllPlayer;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	// ī�޶�, ���� �� �������� ������ �� �ִ� �÷��̾ �Ǻ��ϱ� ���� bool��. �߰�
	bool IsTurnPlayer = false;
};

