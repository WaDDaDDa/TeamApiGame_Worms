#include "Player.h"
#include "ContentsEnum.h"
#include "MouseObject.h"
#include "GameTurn.h"
#include "Ground.h"
#include "PlayLevel.h"

//무기
#include "Weapon.h"
#include "Bazooka.h"
#include "HomingMissile.h"
#include "Sheep.h"
#include "Uzi.h"
#include "Grenade.h"
#include "Self_Bomb.h"
#include "BombEffect.h"
#include "Donkey.h"
#include "Hallelujah.h"
#include "TestWeapon.h"
#include "SuperSheep.h"
#include "TargetEffect.h"
#include "AirStrikeMissile.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>


// UI
#include "UI_PlayerDamage.h"
#include "UI_Box_AllTeamHpBar.h"

#define RIGHT_UP_MAXANGEL  -90
#define RIGHT_DOWN_MAXANGEL  90
#define LEFT_UP_MAXANGEL 270
#define LEFT_DOWN_MAXANGEL 90

void Player::IdleStart()
{
	//ChangeAnimationState("Idle");

	if (30 <= Hp)
	{
		ChangeAnimationState("IdleHp100_1");
	}
	else
	{
		ChangeAnimationState("IdleHp30_1");
	}

	CrossHairRenderer->Off();

	//PlayerBodyCollision->On();
	SoundCount = 0;
}
void Player::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);

	//std::vector<GameEngineCollision*> _Col;
	//if (true == PlayerBodyCollision->Collision(CollisionOrder::Bomb, _Col
	//	, CollisionType::Rect
	//	, CollisionType::CirCle
	//))
	//{
	//	for (size_t i = 0; i < _Col.size(); i++)
	//	{
	//		GameEngineCollision* Collison = _Col[i];

	//		GameEngineActor* Actor = Collison->GetActor();
	//	}
	//	ChangeState(PlayerState::Damaging);
	//}

	DamagingCheck();

	unsigned int Color = GetGroundColor(RGB(255, 255, 255), float4::DOWN);

	if ((RGB(255, 255, 255) == Color))
	{
		ChangeState(PlayerState::Falling);
		return;
	}

	if (MainRenderer->IsAnimationEnd())
	{
		if (MainRenderer->IsAnimation("Left_IdleHp100_1") || MainRenderer->IsAnimation("Right_IdleHp100_1"))
		{
			ChangeAnimationState("IdleHp100_2");
		}
		else if (MainRenderer->IsAnimation("Left_IdleHp100_2") || MainRenderer->IsAnimation("Right_IdleHp100_2"))
		{
			ChangeAnimationState("IdleHp100_1");
			IdleCount++;
		}
		else if (MainRenderer->IsAnimation("Left_IdleHp30_1") || MainRenderer->IsAnimation("Right_IdleHp30_1"))
		{
			ChangeAnimationState("IdleHp30_2");
		}
		else if (MainRenderer->IsAnimation("Left_IdleHp30_2") || MainRenderer->IsAnimation("Right_Idlehp30_2"))
		{
			ChangeAnimationState("IdleHp30_1");
			IdleCount++;
		}
		else if (MainRenderer->IsAnimation("Left_Blink1") || MainRenderer->IsAnimation("Right_Blink1"))
		{
			ChangeAnimationState("Blink2");
		}
		else if (MainRenderer->IsAnimation("Left_Blink2") || MainRenderer->IsAnimation("Right_Blink2"))
		{
			if (30 <= Hp)
			{
				ChangeAnimationState("IdleHp100_1");
			}
			else
			{
				ChangeAnimationState("IdleHp30_1");
			}
		}
	}

	if (3 <= IdleCount)
	{
		IdleCount = 0;
		ChangeAnimationState("Blink1");
	}

	if (true != IsTurnPlayer)
	{
		return;
	}

	if (true == GameTurn::MainGameTurn->GameOverCheck())
	{
		ChangeState(PlayerState::Win);
	}
	
	if (GameEngineInput::IsDown('T'))
	{
		TargetPos = MouseObject::GetPlayMousePos();
		CreateWeapon<TestWeapon>();
		//CreateWeapon<Donkey>();
	}

	//if (true == GameEngineInput::IsPress(VK_LEFT)
	//	|| true == GameEngineInput::IsPress(VK_RIGHT))
	//{
	//	DirCheck();
	//	ChangeState(PlayerState::Move);
	//	return;
	//}

	//if (true == GameEngineInput::IsDown(VK_SPACE))
	//{
	//	//ChangeState(PlayerState::Jump);
	//	ChangeState(PlayerState::JumpReady);
	//	return;
	//}

	if (0 >= Hp)
	{
		ChangeState(PlayerState::Death);
	}

	if (true == GameEngineInput::IsDown('S'))
	{
		ChangeState(PlayerState::Win);
	}

	InputMove();
	ChangeWeapon();

	
	
	
}

void Player::MoveStart()
{
	ChangeAnimationState("Move");
	SoundCount = 0;
	
}
void Player::MoveUpdate(float _Delta)
{
	DirCheck();

	GroundCheck(_Delta);

	Movement(_Delta);

	if (0 >= SoundCount)
	{
		GameEngineSound::SoundPlay("Walk-Expand.wav");
		SoundCount++;
	}

	if (MainRenderer->IsAnimationEnd())
	{
		SoundCount = 0;
	}


	if (true == GameEngineInput::IsFree(VK_LEFT) && true == GameEngineInput::IsFree(VK_RIGHT))
	{
		//ChangeState(PlayerState::Idle);
		ChangeState(PrevMoveState);
	}

	unsigned int Color = GetGroundColor(RGB(255, 255, 255), float4::DOWN);

	if ((RGB(255, 255, 255) == Color))
	{
		ChangeState(PlayerState::Falling);
		return;
	}

}

void Player::JumpReadyStart()
{
	ChangeAnimationState("JumpReady");
}
void Player::JumpReadyUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Jump);
	}
	
}

void Player::JumpStart()
{
	ChangeAnimationState("Jump");
	if (PlayerDir::Left == Dir)
	{
		SetGravityVector(float4::UP * PlayerJumpPower + float4::LEFT * 300.0f);
	}
	else if (PlayerDir::Right == Dir)
	{
		SetGravityVector(float4::UP * PlayerJumpPower + float4::RIGHT * 300.0f);
	}
	
	GameEngineSound::SoundPlay("JUMP1.WAV");
}
void Player::JumpUpdate(float _Delta)
{
	Gravity(_Delta);
	//DirCheck();

	// 머리위 체크가 하얀색이 아니라면 Falling으로 상태전환. = 다른색상이 있다면 Falling
	// 머리위 체크가 녹색이면 Falling,  빨간색이면 통과.  이런식으로 하면 통과하는 발판이 가능해질듯함.
	unsigned int ColorCheck = GetGroundColor(RGB(255, 255, 255), UpCheckPos);
	unsigned int LeftColorCheck = GetGroundColor(RGB(255, 255, 255), LeftCheckPos);
	unsigned int RightColorCheck = GetGroundColor(RGB(255, 255, 255), RightCheckPos);

	if (PlayerDir::Left == Dir && LeftColorCheck != RGB(255, 255, 255))
	{
		SetGravityVector(float4::ZERO);
		ChangeState(PlayerState::Falling);
		return;
	}
	else if (PlayerDir::Right == Dir && RightColorCheck != RGB(255, 255, 255))
	{
		SetGravityVector(float4::ZERO);
		ChangeState(PlayerState::Falling);
		return;
	}

	// 천장에 머리 부딪힘 -> Falling으로 전환
	if (ColorCheck != RGB(255, 255, 255))
	{
		SetGravityVector(float4::ZERO);
		ChangeState(PlayerState::Falling);
		return;
	}

	// 점프 최고점 -> Falling 으로 전환
	if (GetGravityVector().iY() >= float4::ZERO.iY())
	{
		ChangeState(PlayerState::Falling);
		return;
	}
	// 점프중 이동
	//Movement(_Delta);
}

void Player::FallingStart()
{
	ChangeAnimationState("Falling");
	
}


void Player::FallingUpdate(float _Delta)
{
	//DirCheck();
	Gravity(_Delta);

	// 땅에 닿으면 기본상태.
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));

	if (RGB(255, 255, 255) != Color)
	{
		GravityReset();
		ChangeState(PlayerState::Idle);
		GameEngineSound::SoundPlay("WormLanding.wav");
		return;
	}

	// 물에 닿으면 Diving 상태
	if (1875.0f <= GetPos().Y)
	{
		ChangeState(PlayerState::Diving);
	}
}

void Player::DamagingStart()
{
	ChangeAnimationState("Damaging0");

	// 데미지 UI 생성
	UI_PlayerDamage* DamageUI = GetLevel()->CreateActor<UI_PlayerDamage>();

	std::vector<GameEngineCollision*> _Col;

	// 만약 닿은 Collision이 Uzi와 Flame을 제외한 Bomb Collision이라면
	if (true == PlayerBodyCollision->Collision(CollisionOrder::Bomb, _Col
		, CollisionType::Rect
		, CollisionType::CirCle
	))
	{
		float4 WeaponPos = float4::ZERO;

		float4 WeaponPlayerPos = float4::ZERO;
		float WeaponDamage = 0.0f;

		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collision = _Col[i];

			GameEngineActor* Actor = Collision->GetActor();

			BombEffect* Effect = dynamic_cast<BombEffect*>(Collision->GetActor());

			WeaponDamage = Effect->GetDamage();

			WeaponPos = Actor->GetPos();

			//Collision->Off();
			
			//PlayerBodyCollision->Off();
		}
		float4 PlayerGetPos = GetPos();
		PlayerGetPos.Y -= 15.0f;
		GravityDir = PlayerGetPos - WeaponPos;
		GravityDir.Normalize();
		GravityDir += float4::UP;


		// Damage 받는 부분
		{
			WeaponPlayerPos = GetPos() - WeaponPos;

			float Damaging = WeaponDamage - (WeaponPlayerPos.Size());

			if (0 >= Damaging)
			{
				Damaging = 5;
			}

			// 데미지 UI 출력
			DamageUI->UpdateData_PlayerDamageUI(PlayerInfoUI->GetPos(), static_cast<int>(Damaging), Player::TurnPlayerIndex);

			this->Hp -= static_cast<int>(Damaging);

			
			UI_Box_AllTeamHpBar::GetAllTeamHpBarUI()->InitTeamHpBarData(TurnPlayerIndex, Hp);

		}
		DamageCount++;

		SetGravityVector(GravityDir * 250.0f);
	}

	// 닿은 Collision이 Uzi(ShotHit) Collision 이라면
	if (true == PlayerBodyCollision->Collision(CollisionOrder::ShotHit, _Col
		, CollisionType::Rect
		, CollisionType::CirCle
	))
	{
		float4 WeaponPos = float4::ZERO;

		float4 WeaponPlayerPos = float4::ZERO;
		float WeaponDamage = 0.0f;

		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collision = _Col[i];

			GameEngineActor* Actor = Collision->GetActor();

			BombEffect* Effect = dynamic_cast<BombEffect*>(Collision->GetActor());

			WeaponDamage = Effect->GetDamage();

			WeaponPos = Actor->GetPos();

			Collision->Off();
			//PlayerBodyCollision->Off();
		}
		float4 PlayerGetPos = GetPos();
		PlayerGetPos.Y -= 15.0f;
		GravityDir = PlayerGetPos - WeaponPos;
		GravityDir.Normalize();
		GravityDir += float4::UP;


		// Damage 받는 부분
		{
			WeaponPlayerPos = GetPos() - WeaponPos;

			float Damaging = WeaponDamage - (WeaponPlayerPos.Size());

			if (0 >= Damaging)
			{
				Damaging = 1;
			}

			// 데미지 UI 출력
			DamageUI->UpdateData_PlayerDamageUI(PlayerInfoUI->GetPos(), static_cast<int>(Damaging), Player::TurnPlayerIndex);

			this->Hp -= static_cast<int>(Damaging);

			UI_Box_AllTeamHpBar::GetAllTeamHpBarUI()->InitTeamHpBarData(TurnPlayerIndex, Hp);
		}

		SetGravityVector(GravityDir * 150.0f);
	}

	// 닿은 Collision이 Flame 이라면
	if (true == PlayerBodyCollision->Collision(CollisionOrder::Flame, _Col
		, CollisionType::Rect
		, CollisionType::CirCle
	))
	{
		float4 WeaponPos = float4::ZERO;

		float4 WeaponPlayerPos = float4::ZERO;
		float WeaponDamage = 0.0f;

		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collision = _Col[i];

			GameEngineActor* Actor = Collision->GetActor();

			BombEffect* Effect = dynamic_cast<BombEffect*>(Collision->GetActor());

			WeaponDamage = Effect->GetDamage();

			WeaponPos = Actor->GetPos();

			//PlayerBodyCollision->Off();
		}
		float4 PlayerGetPos = GetPos();
		PlayerGetPos.Y -= 15.0f;
		GravityDir = PlayerGetPos - WeaponPos;
		GravityDir.Normalize();
		GravityDir += float4::UP;

		if (0.5f <= GetLiveTime())
		{
			DamageUI->UpdateData_PlayerDamageUI(PlayerInfoUI->GetPos(), static_cast<int>(WeaponDamage), Player::TurnPlayerIndex);

			this->Hp -= static_cast<int>(WeaponDamage);

			UI_Box_AllTeamHpBar::GetAllTeamHpBarUI()->InitTeamHpBarData(TurnPlayerIndex, Hp);

			ResetLiveTime();
		}

		// Damage 받는 부분
		//{
		//	WeaponPlayerPos = GetPos() - WeaponPos;

		//	// 데미지 UI 출력
		//	DamageUI->UpdateData_PlayerDamageUI(PlayerInfoUI->GetPos(), static_cast<int>(WeaponDamage), Player::TurnPlayerIndex);

		//	this->Hp -= static_cast<int>(WeaponDamage);

		//	UI_Box_AllTeamHpBar::GetAllTeamHpBarUI()->InitTeamHpBarData(TurnPlayerIndex, Hp);
		//}

		SetGravityVector(GravityDir * 100.0f);
	}

	//GameEngineSound::SoundPlay("OW1.WAV");
	SoundCount = 0;


	ResetLiveTime();
}
void Player::DamagingUpdate(float _Delta)
{
	//GroundCheck(_Delta);
	
	if (0 >= SoundCount)
	{
		WhatSound = GameEngineRandom::MainRandom.RandomInt(1, 3);
		std::string SoundName = "OW";
		SoundName += std::to_string(WhatSound);
		SoundName += ".WAV";
		GameEngineSound::SoundPlay(SoundName);
		SoundCount++;
	}

	Gravity(_Delta);

	// Damaging Angle -> ChangeAnimation
	{
		if (0 <= GravityDir.X)
		{
			Dir = PlayerDir::Right;
		}
		if (0 > GravityDir.X)
		{
			Dir = PlayerDir::Left;
		}

		GravityDirMul = (GravityDir.Y + 1) * 90;
		GravityDir.Y += _Delta;

		int iGravityDirMul = static_cast<int>(GravityDirMul);

		switch (iGravityDirMul)
		{
		case -90:
			ChangeAnimationState("Damaging0");
			break;
		case -84:
			ChangeAnimationState("Damaging1");
			break;
		case -78:
			ChangeAnimationState("Damaging2");
			break;
		case -73:
			ChangeAnimationState("Damaging3");
			break;
		case -67:
			ChangeAnimationState("Damaging4");
			break;
		case -61:
			ChangeAnimationState("Damaging5");
			break;
		case -56:
			ChangeAnimationState("Damaging6");
			break;
		case -50:
			ChangeAnimationState("Damaging7");
			break;
		case -45:
			ChangeAnimationState("Damaging8");
			break;
		case -39:
			ChangeAnimationState("Damaging9");
			break;
		case -33:
			ChangeAnimationState("Damaging10");
			break;
		case -28:
			ChangeAnimationState("Damaging11");
			break;
		case -22:
			ChangeAnimationState("Damaging12");
			break;
		case -16:
			ChangeAnimationState("Damaging13");
			break;
		case -11:
			ChangeAnimationState("Damaging14");
			break;
		case -5:
			ChangeAnimationState("Damaging15");
			break;
		case 0:
			ChangeAnimationState("Damaging16");
			break;
		case 5:
			ChangeAnimationState("Damaging17");
			break;
		case 11:
			ChangeAnimationState("Damaging18");
			break;
		case 16:
			ChangeAnimationState("Damaging19");
			break;
		case 22:
			ChangeAnimationState("Damaging20");
			break;
		case 28:
			ChangeAnimationState("Damaging21");
			break;
		case 33:
			ChangeAnimationState("Damaging22");
			break;
		case 39:
			ChangeAnimationState("Damaging23");
			break;
		case 45:
			ChangeAnimationState("Damaging24");
			break;
		case 50:
			ChangeAnimationState("Damaging25");
			break;
		case 56:
			ChangeAnimationState("Damaging26");
			break;
		case 61:
			ChangeAnimationState("Damaging27");
			break;
		case 67:
			ChangeAnimationState("Damaging28");
			break;
		case 73:
			ChangeAnimationState("Damaging29");
			break;
		case 78:
			ChangeAnimationState("Damaging30");
			break;
		case 84:
			ChangeAnimationState("Damaging31");
			break;
		}
	}


	// Damage 연속 인식
	{
		UI_PlayerDamage* DamageUI = GetLevel()->CreateActor<UI_PlayerDamage>();
		std::vector<GameEngineCollision*> _Col;

		// Uzi
		if (true == PlayerBodyCollision->Collision(CollisionOrder::ShotHit, _Col
			, CollisionType::Rect
			, CollisionType::CirCle
		))
		{
			float4 WeaponPos = float4::ZERO;

			float4 WeaponPlayerPos = float4::ZERO;
			float WeaponDamage = 0.0f;

			for (size_t i = 0; i < _Col.size(); i++)
			{
				GameEngineCollision* Collision = _Col[i];

				GameEngineActor* Actor = Collision->GetActor();

				BombEffect* Effect = dynamic_cast<BombEffect*>(Collision->GetActor());

				WeaponDamage = Effect->GetDamage();

				WeaponPos = Actor->GetPos();

				Collision->Off();
				//PlayerBodyCollision->Off();
			}
			float4 PlayerGetPos = GetPos();
			PlayerGetPos.Y -= 15.0f;
			GravityDir = PlayerGetPos - WeaponPos;
			GravityDir.Normalize();
			GravityDir += float4::UP;


			SoundCount = 0;
			// Damage 받는 부분
			{
				WeaponPlayerPos = GetPos() - WeaponPos;

				float Damaging = WeaponDamage - (WeaponPlayerPos.Size());

				if (0 >= Damaging)
				{
					Damaging = 1;
				}

				// 데미지 UI 출력
				DamageUI->UpdateData_PlayerDamageUI(PlayerInfoUI->GetPos(), static_cast<int>(Damaging), Player::TurnPlayerIndex);

				this->Hp -= static_cast<int>(Damaging);

				UI_Box_AllTeamHpBar::GetAllTeamHpBarUI()->InitTeamHpBarData(TurnPlayerIndex, Hp);
			}

			SetGravityVector(GravityDir * 150.0f);
		}

		// Flame
		if (true == PlayerBodyCollision->Collision(CollisionOrder::Flame, _Col
			, CollisionType::Rect
			, CollisionType::CirCle
		))
		{
			float4 WeaponPos = float4::ZERO;

			float4 WeaponPlayerPos = float4::ZERO;
			float WeaponDamage = 0.0f;

			for (size_t i = 0; i < _Col.size(); i++)
			{
				GameEngineCollision* Collision = _Col[i];

				GameEngineActor* Actor = Collision->GetActor();

				BombEffect* Effect = dynamic_cast<BombEffect*>(Collision->GetActor());

				WeaponDamage = Effect->GetDamage();

				WeaponPos = Actor->GetPos();

				//PlayerBodyCollision->Off();
			}
			float4 PlayerGetPos = GetPos();
			PlayerGetPos.Y -= 15.0f;
			GravityDir = PlayerGetPos - WeaponPos;
			GravityDir.Normalize();
			GravityDir += float4::UP;

			SoundCount = 0;
			// Damage 받는 부분
			{
				WeaponPlayerPos = GetPos() - WeaponPos;

				// 데미지 UI 출력
				DamageUI->UpdateData_PlayerDamageUI(PlayerInfoUI->GetPos(), static_cast<int>(WeaponDamage), Player::TurnPlayerIndex);

				this->Hp -= static_cast<int>(WeaponDamage);

				UI_Box_AllTeamHpBar::GetAllTeamHpBarUI()->InitTeamHpBarData(TurnPlayerIndex, Hp);
			}

			SetGravityVector(GravityDir * 100.0f);
		}

	}




	unsigned int DownCheckColor = GetGroundColor(RGB(255, 255, 255), DownCheckPos);
	unsigned int UpCheckColor = GetGroundColor(RGB(255, 255, 255), UpCheckPos);
	unsigned int LeftCheckColor = GetGroundColor(RGB(255, 255, 255), LeftCheckPos);
	unsigned int RightCheckColor = GetGroundColor(RGB(255, 255, 255), RightCheckPos);

	if (RGB(255, 255, 255) != UpCheckColor)
	{
		SetGravityVector({ GravityDir.X, 1.0f });

		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), UpCheckPos);

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), UpCheckPos);
			AddPos(float4::DOWN);
		}
	}

	if (RGB(255, 255, 255) != LeftCheckColor)
	{
		if (0 >= GravityDir.X)
		{
			SetGravityVector({ -GravityDir.X , GravityDir.Y });
		}
		else
		{
			SetGravityVector(GravityDir);
		}

		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), LeftCheckPos);

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), LeftCheckPos);
			AddPos(float4::RIGHT);
		}
	}

	if (RGB(255, 255, 255) != RightCheckColor)
	{
		if (0 <= GravityDir.X)
		{
			SetGravityVector({ -GravityDir.X, GravityDir.Y });
		}
		else
		{
			SetGravityVector(GravityDir);
		}

		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), RightCheckPos);

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), RightCheckPos);
			AddPos(float4::LEFT);
		}
	}

	
	

	//if (RGB(255, 255, 255) == Color)
	//{
	//	Gravity(_Delta);
	//}
	//else // 모두흰색이 아니다 = 땅에닿아있다.
	//{
	//	unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

	//	// 체크중 어느하나라도  흰색이 아니라면 한칸올리기 반복한다.
	//	while (CheckColor != RGB(255, 255, 255))
	//	{
	//		CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

	//		AddPos(float4::UP);
	//	}

	//	GravityReset();
	//}




	if (RGB(255, 255, 255) != DownCheckColor)
	{
		GravityReset();
		//ChangeState(PlayerState::Death);
		ChangeState(PlayerState::Idle);
		return;
	}

	if (1875.0f <= GetPos().Y)
	{
		ChangeState(PlayerState::Diving);
	}

	/*if (0 >= Hp)
	{
		ChangeState(PlayerState::Death);
	}*/
}

void Player::DeathStart()
{
	ChangeAnimationState("Death");
	GameEngineSound::SoundPlay("BYEBYE.WAV");
}
void Player::DeathUpdate(float _Delta)
{
	if(MainRenderer->IsAnimationEnd())
	{
		CreateWeapon<Self_Bomb>();
		ChangeState(PlayerState::DeathEnd);
		return;
	}
}

void Player::DeathEndStart()
{
	// 플레이어가 죽어서 사라지면 안됨. 
	// 묘비 상태로 중력에는 영향을 받고있어야함.
	// Death();
	ChangeAnimationState("GraveStone");
	MainRenderer->SetRenderScaleToTexture();
	GravityReset();

	if (true == IsDiving)
	{
		UI_PlayerDamage* DamageUI = GetLevel()->CreateActor<UI_PlayerDamage>();
		DamageUI->UpdateData_PlayerDamageUI(PlayerInfoUI->GetPos(), this->Hp, Player::TurnPlayerIndex);

		this->Hp -= this->Hp;

		UI_Box_AllTeamHpBar::GetAllTeamHpBarUI()->InitTeamHpBarData(TurnPlayerIndex, Hp);
	}
}
void Player::DeathEndUpdate(float _Delta)
{
	if (false == IsDiving)
	{
		GroundCheck(_Delta);
	}
	else
	{
		if (2150.0f > GetPos().Y)
		{
			Gravity(_Delta);
		}
	}
}

void Player::BazookaOnStart()
{
	PrevMoveState = PlayerState::BazookaOn;
	ChangeAnimationState("BazookaOn");
	CrossHairRenderer->On();
	SoundCount = 0;
}
void Player::BazookaOnUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Bazooka);
		return;
	}
	InputMove();
}

void Player::BazookaStart()
{
	ChangeAnimationState("Bazooka15");
	CrossHairRenderer->On();
}
void Player::BazookaUpdate(float _Delta)
{
	DirCheck();

	if (true != IsTurnPlayer)
	{
		ChangeState(PlayerState::BazookaOff);
		return;
	}

	if (true == GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::BazookaOff);
		return;
	}

	ChangeAimAngle(_Delta);

	CrossHairPos = { LengthX, LengthY };
	CrossHairPos.Normalize();
	CrossHairPos *= 92;

	if (true == GameEngineInput::IsUp('A') || ChargingTime >= MaxChargingTime)
	{

		if (ChargingTime >= MaxChargingTime)
		{
			ChargingTime = MaxChargingTime;
			ChangeState(PlayerState::BazookaFire);
		}

		ChangeState(PlayerState::BazookaFire);
		return;
	}

	if (true == GameEngineInput::IsPress('A'))
	{
		if (0 >= SoundCount)
		{
			WhatSound = GameEngineRandom::MainRandom.RandomInt(1, 2);
			if (WhatSound == 1)
			{
				GameEngineSound::SoundPlay("FIRE.WAV");
			}
			else if (WhatSound == 2)
			{
				GameEngineSound::SoundPlay("WATCHTHIS.WAV");
			}
			
			SoundCount++;
		}
		
		ChargingTime += _Delta;
		SetGauge(_Delta);
	}

	int iCurAngle = static_cast<int>(CurAngle);
	// 애니메이션과 무기각도를 맞추기위한 중간 계산식.
	// 무기각도가 -90에서 +되면서 270도까지로 되어있음.
	if (PlayerDir::Left == Dir)
	{
		iCurAngle = 180 - iCurAngle;
	}

	switch (iCurAngle)
	{
	case -90:
		ChangeAnimationState("Bazooka31");
		break;
	case -84:
		ChangeAnimationState("Bazooka30");
		break;
	case -78:
		ChangeAnimationState("Bazooka29");
		break;
	case -73:
		ChangeAnimationState("Bazooka28");
		break;
	case -67:
		ChangeAnimationState("Bazooka27");
		break;
	case -61:
		ChangeAnimationState("Bazooka26");
		break;
	case -56:
		ChangeAnimationState("Bazooka25");
		break;
	case -50:
		ChangeAnimationState("Bazooka24");
		break;
	case -45:
		ChangeAnimationState("Bazooka23");
		break;
	case -39:
		ChangeAnimationState("Bazooka22");
		break;
	case -33:
		ChangeAnimationState("Bazooka21");
		break;
	case -28:
		ChangeAnimationState("Bazooka20");
		break;
	case -22:
		ChangeAnimationState("Bazooka19");
		break;
	case -16:
		ChangeAnimationState("Bazooka18");
		break;
	case -11:
		ChangeAnimationState("Bazooka17");
		break;
	case -5:
		ChangeAnimationState("Bazooka16");
		break;
	case 0:
		ChangeAnimationState("Bazooka15");
		break;
	case 5:
		ChangeAnimationState("Bazooka14");
		break;
	case 11:
		ChangeAnimationState("Bazooka13");
		break;
	case 16:
		ChangeAnimationState("Bazooka12");
		break;
	case 22:
		ChangeAnimationState("Bazooka11");
		break;
	case 28:
		ChangeAnimationState("Bazooka10");
		break;
	case 33:
		ChangeAnimationState("Bazooka9");
		break;
	case 39:
		ChangeAnimationState("Bazooka8");
		break;
	case 45:
		ChangeAnimationState("Bazooka7");
		break;
	case 50:
		ChangeAnimationState("Bazooka6");
		break;
	case 56:
		ChangeAnimationState("Bazooka5");
		break;
	case 61:
		ChangeAnimationState("Bazooka4");
		break;
	case 67:
		ChangeAnimationState("Bazooka3");
		break;
	case 73:
		ChangeAnimationState("Bazooka2");
		break;
	case 78:
		ChangeAnimationState("Bazooka1");
		break;
	case 84:
		ChangeAnimationState("Bazooka0");
		break;
	}

	

	//CrossHairRenderer->SetRenderPos(CrossHairPos);
	CrossHairRenderer->SetRenderPos(MainRenderer->GetRenderPos() + CrossHairPos);

	ChangeCrossHairRenderPos(iCurAngle);

	InputMove();
	ChangeWeapon();
}

void Player::BazookaFireStart()
{
	CreateWeapon<Bazooka>();
	AllGaugeOff();
	SoundCount = 0;
}

void Player::BazookaFireUpdate(float _Delta)
{
	DamagingCheck();

	ChangeState(PlayerState::BazookaOff);
	return;
}

void Player::BazookaOffStart()
{
	CrossHairRenderer->Off();
	ChangeAnimationState("BazookaOff");
}

void Player::BazookaOffUpdate(float _Delta)
{
	DamagingCheck();

	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::UziOnStart()
{
	PrevMoveState = PlayerState::UziOn;
	ChangeAnimationState("UziOn");
	CrossHairRenderer->On();
	SoundCount = 0;
}
void Player::UziOnUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Uzi);
		return;
	}

	InputMove();
}

void Player::UziStart()
{
	ChangeAnimationState("Uzi" + std::to_string(UziAnimationNumber));
	CrossHairRenderer->On();
}
void Player::UziUpdate(float _Delta)
{
	DirCheck();

	if (true != IsTurnPlayer)
	{
		ChangeState(PlayerState::UziOff);
		return;
	}

	if (true == GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::UziOff);
		return;
	}

	ChangeAimAngle(_Delta);

	CrossHairPos = { LengthX, LengthY };
	CrossHairPos.Normalize();
	CrossHairPos *= 92;

	

	int iCurAngle = static_cast<int>(CurAngle);
	// 애니메이션과 무기각도를 맞추기위한 중간 계산식.
	// 무기각도가 -90에서 +되면서 270도까지로 되어있음.
	if (PlayerDir::Left == Dir)
	{
		iCurAngle = 180 - iCurAngle;
	}

	switch (iCurAngle)
	{
	case -90:
		UziAnimationNumber = 31;
		ChangeAnimationState("Uzi31");
		break;
	case -84:
		UziAnimationNumber = 30;
		ChangeAnimationState("Uzi30");
		break;
	case -78:
		UziAnimationNumber = 29;
		ChangeAnimationState("Uzi29");
		break;
	case -73:
		UziAnimationNumber = 28;
		ChangeAnimationState("Uzi28");
		break;
	case -67:
		UziAnimationNumber = 27;
		ChangeAnimationState("Uzi27");
		break;
	case -61:
		UziAnimationNumber = 26;
		ChangeAnimationState("Uzi26");
		break;
	case -56:
		UziAnimationNumber = 25;
		ChangeAnimationState("Uzi25");
		break;
	case -50:
		UziAnimationNumber = 24;
		ChangeAnimationState("Uzi24");
		break;
	case -45:
		UziAnimationNumber = 23;
		ChangeAnimationState("Uzi23");
		break;
	case -39:
		UziAnimationNumber = 22;
		ChangeAnimationState("Uzi22");
		break;
	case -33:
		UziAnimationNumber = 21;
		ChangeAnimationState("Uzi21");
		break;
	case -28:
		UziAnimationNumber = 20;
		ChangeAnimationState("Uzi20");
		break;
	case -22:
		UziAnimationNumber = 19;
		ChangeAnimationState("Uzi19");
		break;
	case -16:
		UziAnimationNumber = 18;
		ChangeAnimationState("Uzi18");
		break;
	case -11:
		UziAnimationNumber = 17;
		ChangeAnimationState("Uzi17");
		break;
	case -5:
		UziAnimationNumber = 16;
		ChangeAnimationState("Uzi16");
		break;
	case 0:
		UziAnimationNumber = 15;
		ChangeAnimationState("Uzi15");
		break;
	case 5:
		UziAnimationNumber = 14;
		ChangeAnimationState("Uzi14");
		break;
	case 11:
		UziAnimationNumber = 13;
		ChangeAnimationState("Uzi13");
		break;
	case 16:
		UziAnimationNumber = 12;
		ChangeAnimationState("Uzi12");
		break;
	case 22:
		UziAnimationNumber = 11;
		ChangeAnimationState("Uzi11");
		break;
	case 28:
		UziAnimationNumber = 10;
		ChangeAnimationState("Uzi10");
		break;
	case 33:
		UziAnimationNumber = 9;
		ChangeAnimationState("Uzi9");
		break;
	case 39:
		UziAnimationNumber = 8;
		ChangeAnimationState("Uzi8");
		break;
	case 45:
		UziAnimationNumber = 7;
		ChangeAnimationState("Uzi7");
		break;
	case 50:
		UziAnimationNumber = 6;
		ChangeAnimationState("Uzi6");
		break;
	case 56:
		UziAnimationNumber = 5;
		ChangeAnimationState("Uzi5");
		break;
	case 61:
		UziAnimationNumber = 4;
		ChangeAnimationState("Uzi4");
		break;
	case 67:
		UziAnimationNumber = 3;
		ChangeAnimationState("Uzi3");
		break;
	case 73:
		UziAnimationNumber = 2;
		ChangeAnimationState("Uzi2");
		break;
	case 78:
		UziAnimationNumber = 1;
		ChangeAnimationState("Uzi1");
		break;
	case 84:
		UziAnimationNumber = 0;
		ChangeAnimationState("Uzi0");
		break;
	}


	//CrossHairRenderer->SetRenderPos(CrossHairPos);
	CrossHairRenderer->SetRenderPos(MainRenderer->GetRenderPos() + CrossHairPos);

	ChangeCrossHairRenderPos(iCurAngle);

	if (GameEngineInput::IsDown('A'))
	{
		ChangeState(PlayerState::UziFire);
	}

	InputMove();
	ChangeWeapon();
}
void Player::UziFireStart()
{
	UziCount = 10;
//	ChangeAnimationState("UziFire15");

	//CreateWeapon<Uzi>();
	ResetLiveTime();
}
void Player::UziFireUpdate(float _Delta)
{
	DamagingCheck();
	std::string AnimationUzi = "Uzi" + std::to_string(UziAnimationNumber);
	std::string AnimationUziFire = "UziFire" + std::to_string(UziAnimationNumber);

	if (0.05f <= GetLiveTime())
	{
		if (MainRenderer->IsAnimation("Left_" + AnimationUzi) || MainRenderer->IsAnimation("Right_" + AnimationUzi))
		{
			CreateWeapon<Uzi>();
			ChangeAnimationState(AnimationUziFire);
			UziCount -= 1;
			ResetLiveTime();
		}
		else if (MainRenderer->IsAnimation("Left_" + AnimationUziFire) || MainRenderer->IsAnimation("Right_" + AnimationUziFire))
		{
			ChangeAnimationState(AnimationUzi);
			ResetLiveTime();
		}

		if (0 >= UziCount)
		{
			ChangeState(PlayerState::UziOff);
		}
		
	}
	//ChangeState(PlayerState::UziOff);
}

void Player::UziOffStart()
{
	CrossHairRenderer->Off();
	ChangeAnimationState("UziOff");
}
void Player::UziOffUpdate(float _Delta)
{
	DamagingCheck();
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::HomingMissileOnStart()
{
	PrevMoveState = PlayerState::HomingMissileOn;
	ChangeAnimationState("HomingMissileOn");
	CrossHairRenderer->On();
	SoundCount = 0;
}
void Player::HomingMissileOnUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::HomingMissile);
		return;
	}

	InputMove();
}

void Player::HomingMissileStart()
{
	ChangeAnimationState("HomingMissile15");
	CrossHairRenderer->On();
}
void Player::HomingMissileUpdate(float _Delta)
{
	DirCheck();

	if (true != IsTurnPlayer)
	{
		ChangeState(PlayerState::HomingMissileOff);
		return;
	}

	if (true == GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::HomingMissileOff);
		return;
	}

	ChangeAimAngle(_Delta);

	CrossHairPos = { LengthX, LengthY };
	CrossHairPos.Normalize();
	CrossHairPos *= 92;

	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		TargetPos = MouseObject::GetPlayMousePos();

		Target = GetLevel()->CreateActor<TargetEffect>();
		Target->SetMaster(this);
		Target->SetPos(TargetPos);
	}


	if (true == GameEngineInput::IsUp('A') || ChargingTime >= MaxChargingTime)
	{

		if (ChargingTime >= MaxChargingTime)
		{
			ChargingTime = MaxChargingTime;
		}

		ChangeState(PlayerState::HomingMissileFire);
		return;
	}

	if (true == GameEngineInput::IsPress('A'))
	{
		if (0 >= SoundCount)
		{
			GameEngineSound::SoundPlay("FIRE.WAV");
			SoundCount++;
		}
		ChargingTime += _Delta;
		SetGauge(_Delta);
	}

	int iCurAngle = static_cast<int>(CurAngle);
	// 애니메이션과 무기각도를 맞추기위한 중간 계산식.
	// 무기각도가 -90에서 +되면서 270도까지로 되어있음.
	if (PlayerDir::Left == Dir)
	{
		iCurAngle = 180 - iCurAngle;
	}

	switch (iCurAngle)
	{
	case -90:
		ChangeAnimationState("HomingMissile31");
		break;
	case -84:
		ChangeAnimationState("HomingMissile30");
		break;
	case -78:
		ChangeAnimationState("HomingMissile29");
		break;
	case -73:
		ChangeAnimationState("HomingMissile28");
		break;
	case -67:
		ChangeAnimationState("HomingMissile27");
		break;
	case -61:
		ChangeAnimationState("HomingMissile26");
		break;
	case -56:
		ChangeAnimationState("HomingMissile25");
		break;
	case -50:
		ChangeAnimationState("HomingMissile24");
		break;
	case -45:
		ChangeAnimationState("HomingMissile23");
		break;
	case -39:
		ChangeAnimationState("HomingMissile22");
		break;
	case -33:
		ChangeAnimationState("HomingMissile21");
		break;
	case -28:
		ChangeAnimationState("HomingMissile20");
		break;
	case -22:
		ChangeAnimationState("HomingMissile19");
		break;
	case -16:
		ChangeAnimationState("HomingMissile18");
		break;
	case -11:
		ChangeAnimationState("HomingMissile17");
		break;
	case -5:
		ChangeAnimationState("HomingMissile16");
		break;
	case 0:
		ChangeAnimationState("HomingMissile15");
		break;
	case 5:
		ChangeAnimationState("HomingMissile14");
		break;
	case 11:
		ChangeAnimationState("HomingMissile13");
		break;
	case 16:
		ChangeAnimationState("HomingMissile12");
		break;
	case 22:
		ChangeAnimationState("HomingMissile11");
		break;
	case 28:
		ChangeAnimationState("HomingMissile10");
		break;
	case 33:
		ChangeAnimationState("HomingMissile9");
		break;
	case 39:
		ChangeAnimationState("HomingMissile8");
		break;
	case 45:
		ChangeAnimationState("HomingMissile7");
		break;
	case 50:
		ChangeAnimationState("HomingMissile6");
		break;
	case 56:
		ChangeAnimationState("HomingMissile5");
		break;
	case 61:
		ChangeAnimationState("HomingMissile4");
		break;
	case 67:
		ChangeAnimationState("HomingMissile3");
		break;
	case 73:
		ChangeAnimationState("HomingMissile2");
		break;
	case 78:
		ChangeAnimationState("HomingMissile1");
		break;
	case 84:
		ChangeAnimationState("HomingMissile0");
		break;
	}


	//CrossHairRenderer->SetRenderPos(CrossHairPos);
	CrossHairRenderer->SetRenderPos(MainRenderer->GetRenderPos() + CrossHairPos);

	ChangeCrossHairRenderPos(iCurAngle);

	InputMove();
	ChangeWeapon();
}

void Player::HomingMissileFireStart()
{
	CreateWeapon<HomingMissile>();
	AllGaugeOff();
}
void Player::HomingMissileFireUpdate(float _Delta)
{
	DamagingCheck();
	ChangeState(PlayerState::HomingMissileOff);
}

void Player::HomingMissileOffStart()
{
	CrossHairRenderer->Off();
	ChangeAnimationState("HomingMissileOff");
}
void Player::HomingMissileOffUpdate(float _Delta)
{
	DamagingCheck();
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::SheepOnStart()
{
	PrevMoveState = PlayerState::SheepOn;
	ChangeAnimationState("SheepOn");
	CrossHairRenderer->Off();
}
void Player::SheepOnUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Sheep);
	}

	InputMove();
}

void Player::SheepStart()
{
	ChangeAnimationState("Sheep");
}
void Player::SheepUpdate(float _Delta)
{
	if (true != IsTurnPlayer)
	{
		ChangeState(PlayerState::SheepOff);
		return;
	}

	if (GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::SheepOff);
	}

	if (GameEngineInput::IsDown('A'))
	{
		ChangeState(PlayerState::SheepFire);
	}

	InputMove();
	ChangeWeapon();
}

void Player::SheepFireStart()
{
	CreateWeapon<Sheep>();
}

void Player::SheepFireUpdate(float _Delta)
{
	DamagingCheck();
	ChangeState(PlayerState::SheepOff);
}

void Player::SheepOffStart()
{
	ChangeAnimationState("SheepOff");
}
void Player::SheepOffUpdate(float _Delta)
{
	DamagingCheck();
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::GranadeOnStart()
{
	PrevMoveState = PlayerState::GranadeOn;
	ChangeAnimationState("GranadeOn");
	CrossHairRenderer->On();
	SoundCount = 0;
}
void Player::GranadeOnUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Granade);
	}

	InputMove();
}

void Player::GranadeStart()
{
	ChangeAnimationState("Granade15");
	CrossHairRenderer->On();
}
void Player::GranadeUpdate(float _Delta)
{
	DirCheck();

	if (true != IsTurnPlayer)
	{
		ChangeState(PlayerState::GranadeOff);
		return;
	}

	if (true == GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::GranadeOff);
		return;
	}

	ChangeAimAngle(_Delta);

	CrossHairPos = { LengthX, LengthY };
	CrossHairPos.Normalize();
	CrossHairPos *= 92;

	if (true == GameEngineInput::IsUp('A') || ChargingTime >= MaxChargingTime)
	{

		if (ChargingTime >= MaxChargingTime)
		{
			ChargingTime = MaxChargingTime;
		}

		ChangeState(PlayerState::GranadeFire);
		return;
	}

	if (true == GameEngineInput::IsPress('A'))
	{
		if (0 >= SoundCount)
		{
			GameEngineSound::SoundPlay("FIRE.WAV");
			SoundCount++;
		}
		ChargingTime += _Delta;
		SetGauge(_Delta);
	}

	int iCurAngle = static_cast<int>(CurAngle);
	// 애니메이션과 무기각도를 맞추기위한 중간 계산식.
	// 무기각도가 -90에서 +되면서 270도까지로 되어있음.
	if (PlayerDir::Left == Dir)
	{
		iCurAngle = 180 - iCurAngle;
	}

	switch (iCurAngle)
	{
	case -90:
		ChangeAnimationState("Granade31");
		break;
	case -84:
		ChangeAnimationState("Granade30");
		break;
	case -78:
		ChangeAnimationState("Granade29");
		break;
	case -73:
		ChangeAnimationState("Granade28");
		break;
	case -67:
		ChangeAnimationState("Granade27");
		break;
	case -61:
		ChangeAnimationState("Granade26");
		break;
	case -56:
		ChangeAnimationState("Granade25");
		break;
	case -50:
		ChangeAnimationState("Granade24");
		break;
	case -45:
		ChangeAnimationState("Granade23");
		break;
	case -39:
		ChangeAnimationState("Granade22");
		break;
	case -33:
		ChangeAnimationState("Granade21");
		break;
	case -28:
		ChangeAnimationState("Granade20");
		break;
	case -22:
		ChangeAnimationState("Granade19");
		break;
	case -16:
		ChangeAnimationState("Granade18");
		break;
	case -11:
		ChangeAnimationState("Granade17");
		break;
	case -5:
		ChangeAnimationState("Granade16");
		break;
	case 0:
		ChangeAnimationState("Granade15");
		break;
	case 5:
		ChangeAnimationState("Granade14");
		break;
	case 11:
		ChangeAnimationState("Granade13");
		break;
	case 16:
		ChangeAnimationState("Granade12");
		break;
	case 22:
		ChangeAnimationState("Granade11");
		break;
	case 28:
		ChangeAnimationState("Granade10");
		break;
	case 33:
		ChangeAnimationState("Granade9");
		break;
	case 39:
		ChangeAnimationState("Granade8");
		break;
	case 45:
		ChangeAnimationState("Granade7");
		break;
	case 50:
		ChangeAnimationState("Granade6");
		break;
	case 56:
		ChangeAnimationState("Granade5");
		break;
	case 61:
		ChangeAnimationState("Granade4");
		break;
	case 67:
		ChangeAnimationState("Granade3");
		break;
	case 73:
		ChangeAnimationState("Granade2");
		break;
	case 78:
		ChangeAnimationState("Granade1");
		break;
	case 84:
		ChangeAnimationState("Granade0");
		break;
	}


	//CrossHairRenderer->SetRenderPos(CrossHairPos);
	CrossHairRenderer->SetRenderPos(MainRenderer->GetRenderPos() + CrossHairPos);

	ChangeCrossHairRenderPos(iCurAngle);

	InputMove();
	ChangeWeapon();
}

void Player::GranadeFireStart()
{
	CreateWeapon<Grenade>();
	AllGaugeOff();
}
void Player::GranadeFireUpdate(float _Delta)
{
	DamagingCheck();
	ChangeState(PlayerState::GranadeOff);
}

void Player::GranadeOffStart()
{
	CrossHairRenderer->Off();
	ChangeAnimationState("GranadeOff");
}
void Player::GranadeOffUpdate(float _Delta)
{
	DamagingCheck();
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::TeleportOnStart()
{
	PrevMoveState = PlayerState::TeleportOn;
	ChangeAnimationState("TeleportOn");
	CrossHairRenderer->Off();
}
void Player::TeleportOnUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Teleport);
		return;
	}

	InputMove();
}

void Player::TeleportStart()
{
	ChangeAnimationState("Teleport");
}
void Player::TeleportUpdate(float _Delta)
{
	if (true != IsTurnPlayer)
	{
		ChangeState(PlayerState::TeleportOff);
		return;
	}

	unsigned int ColorCheck;
	// 마우스 이용, 마우스 좌클릭시 애니메이션 전환
	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		TeleportPos = MouseObject::GetPlayMousePos();
		ColorCheck = GetGroundColor(RGB(255, 255, 255), TeleportPos - GetPos());

		if (ColorCheck != RGB(255, 255, 255))
		{
			return;
		}

		ChangeState(PlayerState::TeleportFire);
		return;
	}

	InputMove();
	ChangeWeapon();
}

void Player::TeleportFireStart()
{
	GameEngineSound::SoundPlay("Communicator.wav");
	ChangeAnimationState("TeleportFire");
}
void Player::TeleportFireUpdate(float _Delta)
{
	if(MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::TeleportMove);
		return;
	}
}

void Player::TeleportMoveStart()
{
	GameEngineSound::SoundPlay("TELEPORT.WAV");
	ChangeAnimationState("TeleportMoveOn");
}
void Player::TeleportMoveUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		if (MainRenderer->IsAnimation("Left_TeleportMoveOn") || MainRenderer->IsAnimation("Right_TeleportMoveOn"))
		{
			// 이동 코드
			SetPos(TeleportPos);

			// 애니메이션 전환
			ChangeAnimationState("TeleportMoveOff");
		}
		else if (MainRenderer->IsAnimation("Left_TeleportMoveOff") || MainRenderer->IsAnimation("Right_TeleportMoveOff"))
		{
			//ChangeState(PlayerState::TeleportOff);
			ChangeState(PlayerState::Idle);
			return;
		}
	}
}

void Player::TeleportOffStart()
{
	ChangeAnimationState("TeleportOff");
}
void Player::TeleportOffUpdate(float _Delta)
{
	if(MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::AirStrikeOnStart()
{
	PrevMoveState = PlayerState::AirStrikeOn;
	ChangeAnimationState("AirStrikeOn");
	CrossHairRenderer->Off();
}
void Player::AirStrikeOnUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::AirStrike);
		return;
	}

	InputMove();
}

void Player::AirStrikeStart()
{
	ChangeAnimationState("AirStrike");
}
void Player::AirStrikeUpdate(float _Delta)
{
	if (true != IsTurnPlayer)
	{
		ChangeState(PlayerState::AirStrikeOff);
		return;
	}

	// 마우스 이용, 마우스 좌클릭시 애니메이션 전환
	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		TargetPos = MouseObject::GetPlayMousePos();

		Target = GetLevel()->CreateActor<TargetEffect>();
		Target->SetMaster(this);
		Target->SetPos(TargetPos);

		ChangeState(PlayerState::AirStrikeFire);
		return;
	}

	if (MainRenderer->IsAnimation("Left_AirStrikeFire") || MainRenderer->IsAnimation("Right_AirStrikeFire"))
	{
		if (MainRenderer->IsAnimationEnd())
		{
			ChangeState(PlayerState::AirStrikeFire);
			return;
		}
	}


	if (GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::AirStrikeOff);
		return;
	}

	InputMove();
	ChangeWeapon();
}

void Player::AirStrikeFireStart()
{
	// 미사일 생성
	ChangeAnimationState("AirStrikeFire");
}
void Player::AirStrikeFireUpdate(float _Delta)
{
	DamagingCheck();
	if (MainRenderer->IsAnimationEnd())
	{
		CreateWeapon<AirStrikeMissile>();
		CreateWeapon<AirStrikeMissile>();
		CreateWeapon<AirStrikeMissile>();

		ChangeState(PlayerState::AirStrikeOff);
		return;
	}
}

void Player::AirStrikeOffStart()
{
	ChangeAnimationState("AirStrikeOff");
}
void Player::AirStrikeOffUpdate(float _Delta)
{
	DamagingCheck();

	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::GirderOnStart()
{
	// Girder 상태 이동 불가
	ChangeAnimationState("GirderOn");
	CrossHairRenderer->Off();
}
void Player::GirderOnUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Girder);
		return;
	}
}

void Player::GirderStart()
{
	ChangeAnimationState("Girder");
	Gride_Renderer->On();
}
void Player::GirderUpdate(float _Delta)
{
	// 보류
	// 마우스 포인터 바꾸고 철근 좌우방향키로 회전, 180도 돌면은 크기 변환

	if (true != IsTurnPlayer)
	{
		ChangeState(PlayerState::GirderOff);
		return;
	}
	
	GroundCheck(_Delta);

	Gride_Renderer->SetRenderPos(-GetPos() + MouseObject::GetPlayMousePos());

	if (true == GameEngineInput::IsDown(VK_RIGHT))
	{
		GameEngineSound::SoundPlay("GIRDERIMPACT.WAV");

		GridState NewState = static_cast<GridState>(static_cast<int>(Gride_State) + 1);

		if (18 == static_cast<int>(NewState))
		{
			NewState = GridState::s0;
		}

		ChangeGride_State(NewState);

	}

	if (true == GameEngineInput::IsDown(VK_LEFT))
	{
		GameEngineSound::SoundPlay("GIRDERIMPACT.WAV");

		GridState NewState = static_cast<GridState>(static_cast<int>(Gride_State) - 1);

		if (-1 == static_cast<int>(NewState))
		{
			NewState = GridState::l8;
		}

		ChangeGride_State(NewState);
	}

	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		GameEngineSound::SoundPlay("GIRDERIMPACT.WAV");
		GameEngineWindowTexture* GroundTexture = dynamic_cast<PlayLevel*>(GetLevel())->GetGround()->GetGroundTexture();
		GameEngineWindowTexture* GroundPIxelTexture = dynamic_cast<PlayLevel*>(GetLevel())->GetGround()->GetPixelGroundTexture();

		GriderConstruct(GroundTexture, GroundPIxelTexture);
	}

	if (GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::GirderOff);
		return;
	}

	ChangeWeapon();
}

void Player::GirderOffStart()
{
	Gride_Renderer->Off();
	ChangeAnimationState("GirderOff");
}
void Player::GirderOffUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::DonkeyOnStart()
{
	PrevMoveState = PlayerState::DonkeyOn;
	ChangeAnimationState("DonkeyOn");
	CrossHairRenderer->Off();
}
void Player::DonkeyOnUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Donkey);
		return;
	}
}

void Player::DonkeyStart()
{
	ChangeAnimationState("Donkey");
}
void Player::DonkeyUpdate(float _Delta)
{
	if (true != IsTurnPlayer)
	{
		ChangeState(PlayerState::DonkeyOff);
		return;
	}
	//ChangeAnimationState("DonkeyFire");

	

	// 마우스 이용, 마우스 좌클릭시 애니메이션 전환
	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		TargetPos = MouseObject::GetPlayMousePos();

		Target = GetLevel()->CreateActor<TargetEffect>();
		Target->SetMaster(this);
		Target->SetPos(TargetPos);

		ChangeState(PlayerState::DonkeyFire);
		return;
	}

	if (MainRenderer->IsAnimation("Left_DonkeyFire") || MainRenderer->IsAnimation("Right_DonkeyFire"))
	{
		if (MainRenderer->IsAnimationEnd())
		{
			ChangeState(PlayerState::DonkeyFire);
			return;
		}
	}

	if (GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::DonkeyOff);
		return;
	}

	InputMove();
	ChangeWeapon();

}

void Player::DonkeyFireStart()
{
	ChangeAnimationState("DonkeyFire");
	GameEngineSound::SoundPlay("INCOMING.WAV");
}
void Player::DonkeyFireUpdate(float _Delta)
{
	DamagingCheck();
	if (MainRenderer->IsAnimationEnd())
	{
		CreateWeapon<Donkey>();

		GameEngineSound::SoundPlay("HOLYDONKEY.WAV");
		ChangeState(PlayerState::DonkeyOff);
		return;
	}
}

void Player::DonkeyOffStart()
{
	ChangeAnimationState("DonkeyOff");
}
void Player::DonkeyOffUpdate(float _Delta)
{
	DamagingCheck();

	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::HolyGranadeOnStart()
{
	PrevMoveState = PlayerState::HolyGranadeOn;
	ChangeAnimationState("HolyGranadeOn");
	CrossHairRenderer->On();
	SoundCount = 0;
}
void Player::HolyGranadeOnUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::HolyGranade);
		return;
	}
	InputMove();
}

void Player::HolyGranadeStart()
{
	ChangeAnimationState("HolyGranade15");
	CrossHairRenderer->On();
}
void Player::HolyGranadeUpdate(float _Delta)
{
	DirCheck();

	if (true != IsTurnPlayer)
	{
		ChangeState(PlayerState::HolyGranadeOff);
		return;
	}

	if (true == GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::HolyGranadeOff);
		return;
	}

	ChangeAimAngle(_Delta);

	CrossHairPos = { LengthX, LengthY };
	CrossHairPos.Normalize();
	CrossHairPos *= 92;

	if (true == GameEngineInput::IsUp('A') || ChargingTime >= MaxChargingTime)
	{

		if (ChargingTime >= MaxChargingTime)
		{
			ChargingTime = MaxChargingTime;
		}

		ChangeState(PlayerState::HolyGranadeFire);
		return;
	}

	if (true == GameEngineInput::IsPress('A'))
	{
		if (0 >= SoundCount)
		{
			GameEngineSound::SoundPlay("FIRE.WAV");
			SoundCount++;
		}
		ChargingTime += _Delta;
		SetGauge(_Delta);
	}

	int iCurAngle = static_cast<int>(CurAngle);
	// 애니메이션과 무기각도를 맞추기위한 중간 계산식.
	// 무기각도가 -90에서 +되면서 270도까지로 되어있음.
	if (PlayerDir::Left == Dir)
	{
		iCurAngle = 180 - iCurAngle;
	}

	switch (iCurAngle)
	{
	case -90:
		ChangeAnimationState("HolyGranade31");
		break;
	case -84:
		ChangeAnimationState("HolyGranade30");
		break;
	case -78:
		ChangeAnimationState("HolyGranade29");
		break;
	case -73:
		ChangeAnimationState("HolyGranade28");
		break;
	case -67:
		ChangeAnimationState("HolyGranade27");
		break;
	case -61:
		ChangeAnimationState("HolyGranade26");
		break;
	case -56:
		ChangeAnimationState("HolyGranade25");
		break;
	case -50:
		ChangeAnimationState("HolyGranade24");
		break;
	case -45:
		ChangeAnimationState("HolyGranade23");
		break;
	case -39:
		ChangeAnimationState("HolyGranade22");
		break;
	case -33:
		ChangeAnimationState("HolyGranade21");
		break;
	case -28:
		ChangeAnimationState("HolyGranade20");
		break;
	case -22:
		ChangeAnimationState("HolyGranade19");
		break;
	case -16:
		ChangeAnimationState("HolyGranade18");
		break;
	case -11:
		ChangeAnimationState("HolyGranade17");
		break;
	case -5:
		ChangeAnimationState("HolyGranade16");
		break;
	case 0:
		ChangeAnimationState("HolyGranade15");
		break;
	case 5:
		ChangeAnimationState("HolyGranade14");
		break;
	case 11:
		ChangeAnimationState("HolyGranade13");
		break;
	case 16:
		ChangeAnimationState("HolyGranade12");
		break;
	case 22:
		ChangeAnimationState("HolyGranade11");
		break;
	case 28:
		ChangeAnimationState("HolyGranade10");
		break;
	case 33:
		ChangeAnimationState("HolyGranade9");
		break;
	case 39:
		ChangeAnimationState("HolyGranade8");
		break;
	case 45:
		ChangeAnimationState("HolyGranade7");
		break;
	case 50:
		ChangeAnimationState("HolyGranade6");
		break;
	case 56:
		ChangeAnimationState("HolyGranade5");
		break;
	case 61:
		ChangeAnimationState("HolyGranade4");
		break;
	case 67:
		ChangeAnimationState("HolyGranade3");
		break;
	case 73:
		ChangeAnimationState("HolyGranade2");
		break;
	case 78:
		ChangeAnimationState("HolyGranade1");
		break;
	case 84:
		ChangeAnimationState("HolyGranade0");
		break;
	}


	//CrossHairRenderer->SetRenderPos(CrossHairPos);
	CrossHairRenderer->SetRenderPos(MainRenderer->GetRenderPos() + CrossHairPos);

	ChangeCrossHairRenderPos(iCurAngle);

	InputMove();
	ChangeWeapon();
}

void Player::HolyGranadeFireStart()
{
	CreateWeapon<Hallelujah>();
	AllGaugeOff();
}
void Player::HolyGranadeFireUpdate(float _Delta)
{
	DamagingCheck();
	ChangeState(PlayerState::HolyGranadeOff);
}

void Player::HolyGranadeOffStart()
{
	CrossHairRenderer->Off();
	ChangeAnimationState("HolyGranadeOff");
}
void Player::HolyGranadeOffUpdate(float _Delta)
{
	DamagingCheck();
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::SuperSheepOnStart()
{
	PrevMoveState = PlayerState::SuperSheepOn;
	ChangeAnimationState("SuperSheepOn");
	CrossHairRenderer->Off();
}
void Player::SuperSheepOnUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::SuperSheep);
	}

	InputMove();
}

void Player::SuperSheepStart()
{
	ChangeAnimationState("SuperSheep");
}
void Player::SuperSheepUpdate(float _Delta)
{
	if (true != IsTurnPlayer)
	{
		ChangeState(PlayerState::SuperSheepOff);
		return;
	}

	if (GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::SuperSheepOff);
		return;
	}

	if (GameEngineInput::IsDown('A'))
	{
		ChangeState(PlayerState::SuperSheepFire);
		return;
	}

	InputMove();
	ChangeWeapon();
}

void Player::SuperSheepFireStart()
{
	CreateWeapon<SuperSheep>();
}
void Player::SuperSheepFireUpdate(float _Delta)
{
	DamagingCheck();
	ChangeState(PlayerState::SuperSheepOff);
}

void Player::SuperSheepOffStart()
{
	ChangeAnimationState("SuperSheepOff");
}
void Player::SuperSheepOffUpdate(float _Delta)
{
	DamagingCheck();
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::WinStart()
{
	ChangeAnimationState("Win");
}
void Player::WinUpdate(float _Delta)
{

}

void Player::DivingStart()
{
	ChangeAnimationState("Diving1");
	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetRenderPos({ 0, 0 });
	GameEngineSound::SoundPlay("Splash.wav");
	IsDiving = true;
}
void Player::DivingUpdate(float _Delta)
{
	// y -> 1875 ~ 2000
	if (2030 >= GetPos().Y)
	{
		SetPos({ GetPos().X, GetPos().Y + (30 * _Delta)});
	}
	else
	{
		ChangeState(PlayerState::DeathEnd);
	}



	if (MainRenderer->IsAnimationEnd())
	{
		if (MainRenderer->IsAnimation("Left_Diving1") || MainRenderer->IsAnimation("Right_Diving1"))
		{
			ChangeAnimationState("Diving2");
		}
		else if(MainRenderer->IsAnimation("Left_Diving2") || MainRenderer->IsAnimation("Right_Diving2"))
		{
			ChangeAnimationState("Diving1");
		}
	}
}
