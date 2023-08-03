#pragma once
#include "GravityActor.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <vector>

enum class PlayerState
{
	Idle,
	Move,
	JumpReady,
	Jump,
	Falling,
	Damaging,
	Death,
	BazookaOn,
	Bazooka,
	BazookaFire,
	BazookaOff,

	DeathEnd,
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

	int GetHp()
	{
		return Hp;
	}

	float GetCurAngle()
	{
		return CurAngle;
	}

	void Movement(float _Delta);

	template <typename WeaponType>
	void CreateWeapon()
	{
		// ���������� 
		class Weapon* NewWeapon = GetLevel()->CreateActor<WeaponType>();
		// �÷��̾��� ������� ����
		SwitchIsTurnPlayer();
		// ���⿡ ī�޶� ��Ŀ�� �ϱ����� ������� Ų��.
		NewWeapon->SwitchIsTurnPlayer();
		NewWeapon->SetGroundTexture(GetGroundTexture());
		NewWeapon->SetMaster(this);
	}

	PlayerState GetState()
	{
		return State;
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

	void BazookaFireStart();
	void BazookaFireUpdate(float _Delta);

	void BazookaOffStart();
	void BazookaOffUpdate(float _Delta);

	void SetDirPosNormalize();

	// Collision
	GameEngineCollision* PlayerBodyCollision = nullptr;

private:
	// PlayerStatus ����
	int Hp = 100;
	float PlayerSpeed = 200.0f;
	float PlayerJumpPower = 400.0f;

	float CurAngle = -45.0f;

	// �÷��̾� ��ü�� �����ϵ��� list�� �÷��̾� ����
	static std::vector<Player*> AllPlayer;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	// ī�޶�, ���� �� �������� ������ �� �ִ� �÷��̾ �Ǻ��ϱ� ���� bool��. �߰�
	// bool IsTurnPlayer = false;

	float4 CheckPos = float4::ZERO;

	// Move �� ���� �����ؼ� ������ ����
	float4 LeftCheckPos = float4{ -5.0f, -10.0f };
	float4 RightCheckPos = float4{ 5.0f, -10.0f };
	float4 UpCheckPos = float4{ 0 , -20.0f };

};

