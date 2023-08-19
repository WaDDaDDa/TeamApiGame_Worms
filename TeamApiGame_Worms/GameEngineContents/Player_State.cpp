#include "Player.h"
#include "ContentsEnum.h"
#include "MouseObject.h"
#include "GameTurn.h"

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
#include "Grider.h"


#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

// UI
#include "UI_PlayerDamage.h"
#include "UI_Box_AllTeamHpBar.h"

#define RIGHT_UP_MAXANGEL  -90
#define RIGHT_DOWN_MAXANGEL  90
#define LEFT_UP_MAXANGEL 270
#define LEFT_DOWN_MAXANGEL 90

void Player::IdleStart()
{
	ChangeAnimationState("Idle");

	//PlayerBodyCollision->On();
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

	if (true != IsTurnPlayer)
	{
		return;
	}

	if (true == GameTurn::GameOverCheck())
	{
		ChangeState(PlayerState::Win);
	}
	

	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		TargetPos = MouseObject::GetPlayMousePos();
		CreateWeapon<TestWeapon>();
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
}
void Player::MoveUpdate(float _Delta)
{
	DirCheck();

	GroundCheck(_Delta);

	Movement(_Delta);

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
		return;
	}

	// 물에 닿으면 Diving 상태
	if (false)
	{
		ChangeState(PlayerState::Diving);
	}
}

void Player::DamagingStart()
{
	ChangeAnimationState("Damaging");

	// 데미지 UI 생성
	UI_PlayerDamage* DamageUI = GetLevel()->CreateActor<UI_PlayerDamage>();

	std::vector<GameEngineCollision*> _Col;
	if (true == PlayerBodyCollision->Collision(CollisionOrder::Bomb, _Col
		, CollisionType::Rect
		, CollisionType::CirCle
	))
	{
		float4 WeaponPos = float4::ZERO;
		float4 GravityDir = float4::ZERO;

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
		GravityDir = GetPos() - WeaponPos;
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
			DamageUI->UpdateData_PlayerDamageUI(PlayerInfoUI->GetPos(), static_cast<int>(Damaging));

			this->Hp -= static_cast<int>(Damaging);

			UI_Box_AllTeamHpBar::GetAllTeamHpBarUI()->InitTeamHpBarData(TurnPlayerIndex, GetHp());


		}
		DamageCount++;

		SetGravityVector(GravityDir * 250.0f);
	}

}
void Player::DamagingUpdate(float _Delta)
{
	GroundCheck(_Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));

	if (RGB(255, 255, 255) != Color)
	{
		GravityReset();
		//ChangeState(PlayerState::Death);
		ChangeState(PlayerState::Idle);
		return;
	}

	/*if (0 >= Hp)
	{
		ChangeState(PlayerState::Death);
	}*/
}

void Player::DeathStart()
{
	ChangeAnimationState("Death");
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
}
void Player::DeathEndUpdate(float _Delta)
{
	GroundCheck(_Delta);
}

void Player::BazookaOnStart()
{
	PrevMoveState = PlayerState::BazookaOn;
	ChangeAnimationState("BazookaOn");
	CrossHairRenderer->On();
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

	// 오른쪽 각도조절
	if (PlayerDir::Right == Dir)
	{
		if (true == GameEngineInput::IsPress(VK_UP))
		{
			CurAngle -= (5.625f * _Delta * 4.0f);
			
			LengthY -= (5.75f * _Delta * 4.0f);

			if (0 <= LengthY)
			{
				LengthX += (5.75f * _Delta * 4.0f);
			}
			else
			{
				LengthX -= (5.75f * _Delta * 4.0f);
			}

			if (CurAngle <= RIGHT_UP_MAXANGEL)
			{
				CurAngle = RIGHT_UP_MAXANGEL;
				LengthX = 0;
				LengthY = -92;
			}
		}
		if (true == GameEngineInput::IsPress(VK_DOWN))
		{
			CurAngle += (5.625f * _Delta * 4.0f);
			if (CurAngle >= RIGHT_DOWN_MAXANGEL)
			{
				CurAngle = RIGHT_DOWN_MAXANGEL;
			}
		}
	}

	// 왼쪽 각도조절
	if (PlayerDir::Left == Dir)
	{
		if (true == GameEngineInput::IsPress(VK_UP))
		{
			CurAngle += (5.625f * _Delta * 4.0f);


			if (CurAngle >= LEFT_UP_MAXANGEL)
			{
				CurAngle = LEFT_UP_MAXANGEL;
			}
		}
		if (true == GameEngineInput::IsPress(VK_DOWN))
		{
			CurAngle -= (5.625f * _Delta * 4.0f);
			if (CurAngle <= LEFT_DOWN_MAXANGEL)
			{
				CurAngle = LEFT_DOWN_MAXANGEL;
			}
		}
	}


	if (true == GameEngineInput::IsUp('A') || GameEngineInput::GetPressTime('A') >= MaxChargingTime)
	{
		ChargingTime = GameEngineInput::GetPressTime('A');

		if (ChargingTime >= MaxChargingTime)
		{
			ChargingTime = MaxChargingTime;
		}
		GameEngineInput::ResetPressTime('A');

		ChangeState(PlayerState::BazookaFire);
		return;
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

	//ChangeCrossHairRenderPos(iCurAngle);

	CrossHairPos = { LengthX, LengthY };
	CrossHairPos.Normalize();
	CrossHairPos *= 92;

	CrossHairRenderer->SetRenderPos(CrossHairPos);


	InputMove();
	ChangeWeapon();
}

void Player::BazookaFireStart()
{
	CreateWeapon<Bazooka>();
}

void Player::BazookaFireUpdate(float _Delta)
{
	DamagingCheck();

	ChangeState(PlayerState::BazookaOff);
	return;
}

void Player::BazookaOffStart()
{
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
	ChangeAnimationState("Uzi15");
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

	// 오른쪽 각도조절
	if (PlayerDir::Right == Dir)
	{
		if (true == GameEngineInput::IsPress(VK_UP))
		{
			CurAngle -= (5.625f * _Delta * 4.0f);

			if (CurAngle <= RIGHT_UP_MAXANGEL)
			{
				CurAngle = RIGHT_UP_MAXANGEL;
			}
		}
		if (true == GameEngineInput::IsPress(VK_DOWN))
		{
			CurAngle += (5.625f * _Delta * 4.0f);

			if (CurAngle >= RIGHT_DOWN_MAXANGEL)
			{
				CurAngle = RIGHT_DOWN_MAXANGEL;
			}
		}
	}

	// 왼쪽 각도조절
	if (PlayerDir::Left == Dir)
	{
		if (true == GameEngineInput::IsPress(VK_UP))
		{
			CurAngle += (5.625f * _Delta * 4.0f);

			if (CurAngle >= LEFT_UP_MAXANGEL)
			{
				CurAngle = LEFT_UP_MAXANGEL;
			}
		}
		if (true == GameEngineInput::IsPress(VK_DOWN))
		{
			CurAngle -= (5.625f * _Delta * 4.0f);

			if (CurAngle <= LEFT_DOWN_MAXANGEL)
			{
				CurAngle = LEFT_DOWN_MAXANGEL;
			}
		}
	}

	if (GameEngineInput::IsDown('A'))
	{
		ChangeState(PlayerState::UziFire);
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

	// 오른쪽 각도조절
	if (PlayerDir::Right == Dir)
	{
		if (true == GameEngineInput::IsPress(VK_UP))
		{
			CurAngle -= (5.625f * _Delta * 4.0f);


			if (CurAngle <= RIGHT_UP_MAXANGEL)
			{
				CurAngle = RIGHT_UP_MAXANGEL;
			}
		}
		if (true == GameEngineInput::IsPress(VK_DOWN))
		{
			CurAngle += (5.625f * _Delta * 4.0f);
			if (CurAngle >= RIGHT_DOWN_MAXANGEL)
			{
				CurAngle = RIGHT_DOWN_MAXANGEL;
			}
		}
	}

	// 왼쪽 각도조절
	if (PlayerDir::Left == Dir)
	{
		if (true == GameEngineInput::IsPress(VK_UP))
		{
			CurAngle += (5.625f * _Delta * 4.0f);


			if (CurAngle >= LEFT_UP_MAXANGEL)
			{
				CurAngle = LEFT_UP_MAXANGEL;
			}
		}
		if (true == GameEngineInput::IsPress(VK_DOWN))
		{
			CurAngle -= (5.625f * _Delta * 4.0f);
			if (CurAngle <= LEFT_DOWN_MAXANGEL)
			{
				CurAngle = LEFT_DOWN_MAXANGEL;
			}
		}
	}

	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		TargetPos = MouseObject::GetPlayMousePos();
	}


	if (true == GameEngineInput::IsUp('A') || GameEngineInput::GetPressTime('A') >= MaxChargingTime)
	{
		ChargingTime = GameEngineInput::GetPressTime('A');

		if (ChargingTime >= MaxChargingTime)
		{
			ChargingTime = MaxChargingTime;
		}

		GameEngineInput::ResetPressTime('A');

		ChangeState(PlayerState::HomingMissileFire);
		return;
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

	InputMove();
	ChangeWeapon();
}

void Player::HomingMissileFireStart()
{
	CreateWeapon<HomingMissile>();
}
void Player::HomingMissileFireUpdate(float _Delta)
{
	DamagingCheck();
	ChangeState(PlayerState::HomingMissileOff);
}

void Player::HomingMissileOffStart()
{
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
	//CreateWeapon<Sheep>();
	CreateWeapon<SuperSheep>();
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

	// 오른쪽 각도조절
	if (PlayerDir::Right == Dir)
	{
		if (true == GameEngineInput::IsPress(VK_UP))
		{
			CurAngle -= (5.625f * _Delta * 4.0f);


			if (CurAngle <= RIGHT_UP_MAXANGEL)
			{
				CurAngle = RIGHT_UP_MAXANGEL;
			}
		}
		if (true == GameEngineInput::IsPress(VK_DOWN))
		{
			CurAngle += (5.625f * _Delta * 4.0f);
			if (CurAngle >= RIGHT_DOWN_MAXANGEL)
			{
				CurAngle = RIGHT_DOWN_MAXANGEL;
			}
		}
	}

	// 왼쪽 각도조절
	if (PlayerDir::Left == Dir)
	{
		if (true == GameEngineInput::IsPress(VK_UP))
		{
			CurAngle += (5.625f * _Delta * 4.0f);


			if (CurAngle >= LEFT_UP_MAXANGEL)
			{
				CurAngle = LEFT_UP_MAXANGEL;
			}
		}
		if (true == GameEngineInput::IsPress(VK_DOWN))
		{
			CurAngle -= (5.625f * _Delta * 4.0f);
			if (CurAngle <= LEFT_DOWN_MAXANGEL)
			{
				CurAngle = LEFT_DOWN_MAXANGEL;
			}
		}
	}


	if (true == GameEngineInput::IsUp('A') || GameEngineInput::GetPressTime('A') >= MaxChargingTime)
	{
		ChargingTime = GameEngineInput::GetPressTime('A');

		if (ChargingTime >= MaxChargingTime)
		{
			ChargingTime = MaxChargingTime;
		}
		GameEngineInput::ResetPressTime('A');

		ChangeState(PlayerState::GranadeFire);
		return;
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

	InputMove();
	ChangeWeapon();
}

void Player::GranadeFireStart()
{
	CreateWeapon<Grenade>();
}
void Player::GranadeFireUpdate(float _Delta)
{
	DamagingCheck();
	ChangeState(PlayerState::GranadeOff);
}

void Player::GranadeOffStart()
{
	ChangeAnimationState("GranadeOff");
}
void Player::GranadeOffUpdate(float _Delta)
{
	DamagingCheck();
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::TeleportOnStart()
{
	PrevMoveState = PlayerState::TeleportOn;
	ChangeAnimationState("TeleportOn");
}
void Player::TeleportOnUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Teleport);
	}

	InputMove();
}

void Player::TeleportStart()
{
	ChangeAnimationState("Teleport");
}
void Player::TeleportUpdate(float _Delta)
{
	unsigned int ColorCheck;
	// 마우스 이용, 마우스 좌클릭시 애니메이션 전환
	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		TeleportPos = MouseObject::GetPlayMousePos();
		ColorCheck = GetGroundColor(RGB(255, 255, 255), TeleportPos);

		if (ColorCheck == RGB(255, 255, 255))
		{
			return;
		}

		ChangeState(PlayerState::TeleportFire);
	}

	InputMove();
	ChangeWeapon();
}

void Player::TeleportFireStart()
{
	ChangeAnimationState("TeleportFire");
}
void Player::TeleportFireUpdate(float _Delta)
{
	if(MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::TeleportMove);
	}
}

void Player::TeleportMoveStart()
{
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
	}
}

void Player::AirStrikeOnStart()
{
	PrevMoveState = PlayerState::AirStrikeOn;
	ChangeAnimationState("AirStrikeOn");
}
void Player::AirStrikeOnUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::AirStrike);
	}

	InputMove();
}

void Player::AirStrikeStart()
{
	ChangeAnimationState("AirStrike");
}
void Player::AirStrikeUpdate(float _Delta)
{
	// 마우스 위치 이용해서 목표 설정
	// 하늘에서 미사일 5개 스폰

	//ChangaAnimationState("AirStrikeFire");

	if (MainRenderer->IsAnimation("Left_AirStrikeFire") || MainRenderer->IsAnimation("Right_AirStrikeFire"))
	{
		if (MainRenderer->IsAnimationEnd())
		{
			ChangeState(PlayerState::AirStrikeFire);
		}
	}


	if (GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::AirStrikeOff);
	}

	InputMove();
	ChangeWeapon();
}

void Player::AirStrikeFireStart()
{
	// 미사일 생성
}
void Player::AirStrikeFireUpdate(float _Delta)
{
	
	ChangeState(PlayerState::AirStrikeOff);
}

void Player::AirStrikeOffStart()
{
	ChangeAnimationState("AirStrikeOff");
}
void Player::AirStrikeOffUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::GirderOnStart()
{
	// Girder 상태 이동 불가
	ChangeAnimationState("GirderOn");
}
void Player::GirderOnUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Girder);
	}
}

void Player::GirderStart()
{
	ChangeAnimationState("Girder");

	CreateWeapon<Grider>();
}
void Player::GirderUpdate(float _Delta)
{
	// 보류
	// 마우스 포인터 바꾸고 철근 좌우방향키로 회전, 180도 돌면은 크기 변환

	
	

	if (GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::GirderOff);
	}

	ChangeWeapon();
}

void Player::GirderOffStart()
{
	ChangeAnimationState("GirderOff");
}
void Player::GirderOffUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::DonkeyOnStart()
{
	PrevMoveState = PlayerState::DonkeyOn;
	ChangeAnimationState("DonkeyOn");
}
void Player::DonkeyOnUpdate(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Donkey);
	}
}

void Player::DonkeyStart()
{
	ChangeAnimationState("Donkey");
}
void Player::DonkeyUpdate(float _Delta)
{
	//ChangeAnimationState("DonkeyFire");

	

	// 마우스 이용, 마우스 좌클릭시 애니메이션 전환
	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		TargetPos = MouseObject::GetPlayMousePos();
		ChangeState(PlayerState::DonkeyFire);
	}

	if (MainRenderer->IsAnimation("Left_DonkeyFire") || MainRenderer->IsAnimation("Right_DonkeyFire"))
	{
		if (MainRenderer->IsAnimationEnd())
		{
			ChangeState(PlayerState::DonkeyFire);
		}
	}

	if (GameEngineInput::IsDown('1'))
	{
		ChangeState(PlayerState::DonkeyOff);
	}

	InputMove();
	ChangeWeapon();

}

void Player::DonkeyFireStart()
{
	ChangeAnimationState("DonkeyFire");
}
void Player::DonkeyFireUpdate(float _Delta)
{
	DamagingCheck();
	if (MainRenderer->IsAnimationEnd())
	{
		CreateWeapon<Donkey>();
		ChangeState(PlayerState::DonkeyOff);
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
	}
}

void Player::HolyGranadeOnStart()
{
	PrevMoveState = PlayerState::HolyGranade;
	ChangeAnimationState("HolyGranadeOn");
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

	// 오른쪽 각도조절
	if (PlayerDir::Right == Dir)
	{
		if (true == GameEngineInput::IsPress(VK_UP))
		{
			CurAngle -= (5.625f * _Delta * 4.0f);


			if (CurAngle <= RIGHT_UP_MAXANGEL)
			{
				CurAngle = RIGHT_UP_MAXANGEL;
			}
		}
		if (true == GameEngineInput::IsPress(VK_DOWN))
		{
			CurAngle += (5.625f * _Delta * 4.0f);
			if (CurAngle >= RIGHT_DOWN_MAXANGEL)
			{
				CurAngle = RIGHT_DOWN_MAXANGEL;
			}
		}
	}

	// 왼쪽 각도조절
	if (PlayerDir::Left == Dir)
	{
		if (true == GameEngineInput::IsPress(VK_UP))
		{
			CurAngle += (5.625f * _Delta * 4.0f);


			if (CurAngle >= LEFT_UP_MAXANGEL)
			{
				CurAngle = LEFT_UP_MAXANGEL;
			}
		}
		if (true == GameEngineInput::IsPress(VK_DOWN))
		{
			CurAngle -= (5.625f * _Delta * 4.0f);
			if (CurAngle <= LEFT_DOWN_MAXANGEL)
			{
				CurAngle = LEFT_DOWN_MAXANGEL;
			}
		}
	}


	if (true == GameEngineInput::IsUp('A') || GameEngineInput::GetPressTime('A') >= MaxChargingTime)
	{
		ChargingTime = GameEngineInput::GetPressTime('A');

		if (ChargingTime >= MaxChargingTime)
		{
			ChargingTime = MaxChargingTime;
		}
		GameEngineInput::ResetPressTime('A');

		ChangeState(PlayerState::HolyGranadeFire);
		return;
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

	InputMove();
	ChangeWeapon();
}

void Player::HolyGranadeFireStart()
{
	CreateWeapon<Hallelujah>();
}
void Player::HolyGranadeFireUpdate(float _Delta)
{
	DamagingCheck();
	ChangeState(PlayerState::HolyGranadeOff);
}

void Player::HolyGranadeOffStart()
{
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
}
void Player::DivingUpdate(float _Delta)
{
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