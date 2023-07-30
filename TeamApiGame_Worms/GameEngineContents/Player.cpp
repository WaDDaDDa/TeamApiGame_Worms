#include "Player.h"
#include "ContentsEnum.h"
#include "MouseObject.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

std::vector<Player*> Player::AllPlayer;

float4 Player::DirPos = float4::ZERO;

Player::Player()
{
	AllPlayer.push_back(this);
}

Player::~Player()
{
}

void Player::Start()
{
	// Resource 추가
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("KirbyLeft_Idel.bmp");
	if (false == IsResource)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Worms\\");
		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("파일명"), 가로, 세로);
		
		{ // LeftAnimation 셋팅
			FilePath.MoveChild("Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Idel.bmp"), 4, 1);
		}

		{ // RinghtAnimation 셋팅
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Idel.bmp"), 4, 1);
		}
	}
	
	MainRenderer = CreateRenderer(RenderOrder::Player);
	MainRenderer->SetTexture("KirbyLeft_Idel.bmp");

	{
		//MainRenderer->CreateAnimation("aniname", "filename", start, end, frame, loop

		{ // LeftAnimation 생성
			MainRenderer->CreateAnimation("Left_Idle", "KirbyLeft_Idel.bmp", 0, 1, 0.2f, true);
		}

		{ // RightAnimation 생성
			MainRenderer->CreateAnimation("Right_Idle", "KirbyRight_Idel.bmp", 0, 1, 0.2f, true);
		}
		MainRenderer->SetScaleRatio(3.0f);
		SetOrder(UpdateOrder::Player);
		
	}
	
	{
		//Collision
	}

	
	Dir = PlayerDir::Right;
	ChangeState(PlayerState::Idle);
}


void Player::Update(float _Delta)
{
	if (IsTurnPlayer == false)
	{
		GameEngineInput::Reset;
	}
	SetDirPosNormalize();
	StateUpdate(_Delta);
}


void Player::Render(float _Delta)
{

}

void Player::ChangeState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Move:
			MoveStart();
			break;
		case PlayerState::Fire:
			FireStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Move:
		return MoveUpdate(_Delta);
	case PlayerState::Fire:
		return FireUpdate(_Delta);
	default:
		break;
	}
}

void Player::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName;

	switch (Dir)
	{
	case PlayerDir::Right:
		AnimationName = "Right_";
		break;
	case PlayerDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _State;

	CurState = _State;
	
	MainRenderer->ChangeAnimation(AnimationName);
}

void Player::DirCheck()
{
	if (true == GameEngineInput::IsFree(VK_LEFT) && true == GameEngineInput::IsFree(VK_RIGHT))
	{
		return;
	}

	if (true == GameEngineInput::IsDown(VK_LEFT) || true == GameEngineInput::IsFree(VK_RIGHT))
	{
		Dir = PlayerDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	if (true == GameEngineInput::IsFree(VK_LEFT) || true == GameEngineInput::IsDown(VK_RIGHT))
	{
		Dir = PlayerDir::Right;
		ChangeAnimationState(CurState);
		return;
	}
}

void Player::SetDirPosNormalize()
{
	float4 MousePos = MouseObject::GetPlayMousePos();
	float4 PlayerPos = GetPos();

	float4 PlayerMouseDir = MousePos - PlayerPos;
	DirPos = PlayerMouseDir.NormalizeReturn();
}

void Player::Movement(float _Delta)
{
	DirCheck();

	float4 MovePos1 = float4::ZERO;

	if (true == GameEngineInput::IsPress(VK_LEFT) && Dir == PlayerDir::Left)
	{
		if (true != IsTurnPlayer)
		{
			return;
		}

		CheckPos = LeftCheckPos;
		MovePos1 = { -PlayerSpeed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{
		if (true != IsTurnPlayer)
		{
			return;
		}

		CheckPos = RightCheckPos;
		MovePos1 = { PlayerSpeed * _Delta, 0.0f };
	}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		if (Color == RGB(255, 255, 255))
		{
			// MovePos를 바꿔버리는 방법이 있을것이고.

			if (RGB(255, 255, 255) == GetGroundColor(RGB(255, 255, 255), MovePos1))
			{
				float4 XPos = float4::ZERO;
				float4 Dir = MovePos1.X <= 0.0f ? float4::RIGHT : float4::LEFT;

				while (RGB(0, 255, 0) != GetGroundColor(RGB(255, 255, 255), MovePos1 + XPos))
				{
					XPos += Dir;

					if (abs(XPos.X) > 50.0f)
					{
						break;
					}
				}

				float4 YPos = float4::ZERO;
				while (RGB(0, 255, 0) != GetGroundColor(RGB(255, 255, 255), MovePos1 + YPos))
				{
					YPos.Y += 1;

					if (YPos.Y > 60.0f)
					{
						break;
					}
				}

				if (abs(XPos.X) >= YPos.Y)
				{
					while (RGB(0, 255, 0) != GetGroundColor(RGB(255, 255, 255), MovePos1))
					{
						MovePos1.Y += 1;
					}
				}

			}

			AddPos(MovePos1);
		}
	}
}