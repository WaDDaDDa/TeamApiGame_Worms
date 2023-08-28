#pragma once
#include "GravityActor.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <vector>

// UI
#include "UI_PlayerInfo.h"

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
	UziOn,
	Uzi,
	UziFire,
	UziOff,
	HomingMissileOn,
	HomingMissile,
	HomingMissileFire,
	HomingMissileOff,
	SheepOn,
	Sheep,
	SheepFire,
	SheepOff,
	GranadeOn,
	Granade,
	GranadeFire,
	GranadeOff,
	TeleportOn,
	Teleport,
	TeleportFire,
	TeleportMove,
	TeleportOff,
	AirStrikeOn,
	AirStrike,
	AirStrikeFire,
	AirStrikeOff,
	GirderOn,
	Girder,
	GirderOff,
	DonkeyOn,
	Donkey,
	DonkeyFire,
	DonkeyOff,
	HolyGranadeOn,
	HolyGranade,
	HolyGranadeFire,
	HolyGranadeOff,
	SuperSheepOn,
	SuperSheep,
	SuperSheepFire,
	SuperSheepOff,

	Diving,
	DeathEnd,
	Win,
	Max
};

enum class PlayerDir
{
	Left,
	Right
};


enum class GridState
{
	s0,
	s1,
	s2,
	s3,
	s4,
	s5,
	s6,
	s7,
	s8,
	l0,
	l1,
	l2,
	l3,
	l4,
	l5,
	l6,
	l7,
	l8

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
	class GameEngineRenderer* CrossHairRenderer = nullptr;
	static float4 DirPos;

	static std::vector<Player*> GetAllPlayer()
	{
		return AllPlayer;
	}

	int GetHp()
	{
		return Hp;
	}

	void HealHp()
	{
		Hp += 25;
	}

	float GetCurAngle()
	{
		return CurAngle;
	}

	void Movement(float _Delta);

	template <typename WeaponType>
	void CreateWeapon()
	{
		// 무기사용으로 
		class Weapon* NewWeapon = GetLevel()->CreateActor<WeaponType>();
		float ChargeRatio = ChargingTime / MaxChargingTime;
		ChargingTime = 0.0f;
		NewWeapon->SetChargingSpeed(ChargeRatio);
		// 플레이어의 제어권을 끄고
		SwitchIsTurnPlayer();
		// 무기에 카메라 포커싱 하기위해 제어권을 킨다.
		NewWeapon->SwitchIsTurnPlayer();
		NewWeapon->SetGroundTexture(GetGroundTexture());
		NewWeapon->SetMaster(this);
	}

	PlayerState GetState()
	{
		return State;
	}

	float4 GetTargetPos()
	{
		return TargetPos;
	}

	PlayerDir GetPlayerDir()
	{
		return Dir;
	}

	void SetTurnPlayerIndex(int _Index)
	{
		TurnPlayerIndex = _Index;
	}

	bool GetIsDiving()
	{
		return IsDiving;
	}

	void ChangeState(PlayerState _State);

	GameEngineRenderer* Gride_Renderer = nullptr;
protected:
	PlayerState State = PlayerState::Max;
	PlayerDir Dir = PlayerDir::Left;
	std::string CurState = "";


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

	void DeathEndStart();
	void DeathEndUpdate(float _Delta);

	void BazookaOnStart();
	void BazookaOnUpdate(float _Delta);

	void BazookaStart();
	void BazookaUpdate(float _Delta);

	void BazookaFireStart();
	void BazookaFireUpdate(float _Delta);

	void BazookaOffStart();
	void BazookaOffUpdate(float _Delta);

	void UziOnStart();
	void UziOnUpdate(float _Delta);

	void UziStart();
	void UziUpdate(float _Delta);

	void UziFireStart();
	void UziFireUpdate(float _Delta);

	void UziOffStart();
	void UziOffUpdate(float _Delta);

	void HomingMissileOnStart();
	void HomingMissileOnUpdate(float _Delta);

	void HomingMissileStart();
	void HomingMissileUpdate(float _Delta);

	void HomingMissileFireStart();
	void HomingMissileFireUpdate(float _Delta);

	void HomingMissileOffStart();
	void HomingMissileOffUpdate(float _Delta);

	void SheepOnStart();
	void SheepOnUpdate(float _Delta);

	void SheepStart();
	void SheepUpdate(float _Delta);

	void SheepFireStart();
	void SheepFireUpdate(float _Delta);

	void SheepOffStart();
	void SheepOffUpdate(float _Delta);

	void GranadeOnStart();
	void GranadeOnUpdate(float _Delta);

	void GranadeStart();
	void GranadeUpdate(float _Delta);

	void GranadeFireStart();
	void GranadeFireUpdate(float _Delta);

	void GranadeOffStart();
	void GranadeOffUpdate(float _Delta);

	void TeleportOnStart();
	void TeleportOnUpdate(float _Delta);

	void TeleportStart();
	void TeleportUpdate(float _Delta);

	void TeleportFireStart();
	void TeleportFireUpdate(float _Delta);

	void TeleportMoveStart();
	void TeleportMoveUpdate(float _Delta);

	void TeleportOffStart();
	void TeleportOffUpdate(float _Delta);

	void AirStrikeOnStart();
	void AirStrikeOnUpdate(float _Delta);

	void AirStrikeStart();
	void AirStrikeUpdate(float _Delta);

	void AirStrikeFireStart();
	void AirStrikeFireUpdate(float _Delta);

	void AirStrikeOffStart();
	void AirStrikeOffUpdate(float _Delta);

	void GirderOnStart();
	void GirderOnUpdate(float _Delta);

	void GirderStart();
	void GirderUpdate(float _Delta);

	void GirderOffStart();
	void GirderOffUpdate(float _Delta);

	void DonkeyOnStart();
	void DonkeyOnUpdate(float _Delta);

	void DonkeyStart();
	void DonkeyUpdate(float _Delta);

	void DonkeyFireStart();
	void DonkeyFireUpdate(float _Delta);

	void DonkeyOffStart();
	void DonkeyOffUpdate(float _Delta);

	void HolyGranadeOnStart();
	void HolyGranadeOnUpdate(float _Delta);

	void HolyGranadeStart();
	void HolyGranadeUpdate(float _Delta);

	void HolyGranadeFireStart();
	void HolyGranadeFireUpdate(float _Delta);

	void HolyGranadeOffStart();
	void HolyGranadeOffUpdate(float _Delta);

	void SuperSheepOnStart();
	void SuperSheepOnUpdate(float _Delta);
	
	void SuperSheepStart();
	void SuperSheepUpdate(float _Delta);

	void SuperSheepFireStart();
	void SuperSheepFireUpdate(float _Delta);

	void SuperSheepOffStart();
	void SuperSheepOffUpdate(float _Delta);

	void WinStart();
	void WinUpdate(float _Delta);

	void DivingStart();
	void DivingUpdate(float _Delta);

	void SetDirPosNormalize();

	void InputMove();
	void ChangeWeapon();
	void DamagingCheck();

	void ChangeCrossHairAnimation(const std::string& _State);
	void ChangeCrossHairRenderPos(int _iCurAngle);

	void ChangeAimAngle(float _Delta);
	void SetGauge(float _Delta);
	void AllGaugeOff();

	// Collision
	GameEngineCollision* PlayerBodyCollision = nullptr;

private:
	// TurnPlayerIndex
	int TurnPlayerIndex = 0;
	// PlayerStatus 관련
	int Hp = 100;
	float PlayerSpeed = 200.0f;
	float PlayerJumpPower = 400.0f;

	float CurAngle = 0.0f;

	PlayerState PrevMoveState = PlayerState::Idle;

	int DamageCount = 0;

	float4 GravityDir = float4::ZERO;

	float GravityDirMul = 0;
	
	bool IsDiving = false;

	int IdleCount = 0;

	// Uzi 관련
	int UziAnimationNumber = 15;
	int UziCount = 0;


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
	float4 DownCheckPos = float4{ 0, 5.0f };

	float ChargingTime = 0.0f;
	float MaxChargingTime = 3.0f;

	// 마우스로 클릭한 후 사용하는 무기의 마우스 클릭 좌표.
	float4 TargetPos = float4::ZERO;
	class TargetEffect* Target = nullptr;
	float4 TeleportPos = float4::ZERO;

	// CrossHairPos 관련
	float4 CrossHairPos = float4::ZERO;
	float LengthMulX = 0;
	float LengthMulY = 0;

	float LengthX = 92.0f;
	float LengthY = 0;

	float AngleSpeed = 5.0f;

	// Grider
	void GriderConstruct(GameEngineWindowTexture* _GroundTexture, GameEngineWindowTexture* _GroundPixelTexture);
	void ChangeGride_State(GridState _State);

	class GameEngineWindowTexture* Gride_PixelTexture = nullptr;

	GridState Gride_State = GridState::s0;

	
	// Gauge Renderer
	GameEngineRenderer* GaugeRenderer0 = nullptr;
	GameEngineRenderer* GaugeRenderer1 = nullptr;
	GameEngineRenderer* GaugeRenderer2 = nullptr;
	GameEngineRenderer* GaugeRenderer3 = nullptr;
	GameEngineRenderer* GaugeRenderer4 = nullptr;
	GameEngineRenderer* GaugeRenderer5 = nullptr;
	GameEngineRenderer* GaugeRenderer6 = nullptr;
	GameEngineRenderer* GaugeRenderer7 = nullptr;
	GameEngineRenderer* GaugeRenderer8 = nullptr;
	GameEngineRenderer* GaugeRenderer9 = nullptr;
	GameEngineRenderer* GaugeRenderer10 = nullptr;
	GameEngineRenderer* GaugeRenderer11 = nullptr;
	GameEngineRenderer* GaugeRenderer12 = nullptr;
	GameEngineRenderer* GaugeRenderer13 = nullptr;
	GameEngineRenderer* GaugeRenderer14 = nullptr;
	GameEngineRenderer* GaugeRenderer15 = nullptr;
	
	
	// Sound 관련
	int SoundCount = 0;
	
	int WhatSound = 0;


	// UI
	UI_PlayerInfo* PlayerInfoUI = nullptr;
};

