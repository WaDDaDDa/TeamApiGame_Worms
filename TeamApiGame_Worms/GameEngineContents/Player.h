#pragma once
#include "GravityActor.h"
#include <vector>

enum class PlayerState
{
	Idle,
	Move,
	Fire,
	JumpReady,
	Jump,
	Falling,
	Damaging,
	Death,
	BazookaOn,
	Bazooka,
	BazookaOff,

	DeathEnd,
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

	int GetHp()
	{
		return Hp;
	}

	float GetCurAngle()
	{
		return CurAngle;
	}

	void Movement(float _Delta);

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

	void JumpReadyStart();
	void JumpReadyUpdate(float _Delta);

	void JumpStart();
	void JumpUpdate(float _Delta);

	void FallingStart();
	void FallingUpdate(float _Delta);

	void DamagingStart();
	void DamagingUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);
	void DeathEnd();

	void BazookaOnStart();
	void BazookaOnUpdate(float _Delta);

	void BazookaStart();
	void BazookaUpdate(float _Delta);

	void BazookaOffStart();
	void BazookaOffUpdate(float _Delta);

	void SetDirPosNormalize();

	// Collision
	GameEngineCollision* PlayerBodyCollision = nullptr;

private:
	// PlayerStatus 관련
	int Hp = 100;
	float PlayerSpeed = 200.0f;
	float PlayerJumpPower = 400.0f;

	float CurAngle = -45.0f;

	// 플레이어 전체를 관리하도록 list로 플레이어 관리
	static std::vector<Player*> AllPlayer;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	// 카메라, 조작 등 메인으로 움직일 수 있는 플레이어를 판별하기 위한 bool값. 추가
	// bool IsTurnPlayer = false;

	float4 CheckPos = float4::ZERO;

	// Move 중 벽을 판정해서 막히는 지점
	float4 LeftCheckPos = float4{ -5.0f, -10.0f };
	float4 RightCheckPos = float4{ 5.0f, -10.0f };
	float4 UpCheckPos = float4{ 0 , -20.0f };

};

