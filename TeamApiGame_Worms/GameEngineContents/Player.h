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

// 설명 : 
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
	// PlayerStatus 관련
	int Hp = 100;
	float PlayerSpeed = 100.0f;
	
	

	// 플레이어 전체를 관리하도록 list로 플레이어 관리
	static std::vector<Player*> AllPlayer;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	// 카메라, 조작 등 메인으로 움직일 수 있는 플레이어를 판별하기 위한 bool값. 추가
	bool IsTurnPlayer = false;
};

