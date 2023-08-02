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
	// Resource
	{
		if (false == ResourcesManager::GetInst().IsLoadTexture("idleLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("idleLeft.bmp"), 1, 6);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("idleRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("idleRight.bmp"), 1, 6);
		}

		if (false == ResourcesManager::GetInst().IsLoadTexture("walkLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("walkLeft.bmp"), 1, 15);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("walkRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("walkRight.bmp"), 1, 15);
		}

		// Jump
		if (false == ResourcesManager::GetInst().IsLoadTexture("jumpReadyLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("jumpReadyLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("jumpReadyRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("jumpReadyRight.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("flyUpLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("flyUpLeft.bmp"), 1, 2);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("flyUpRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("flyUpRight.bmp"), 1, 2);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("flyLinkLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("flyLinkLeft.bmp"), 1, 7);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("flyLinkRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("flyLinkRight.bmp"), 1, 7);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("flyDownLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("flyDownLeft.bmp"), 1, 2);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("flyDownRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("flyDownRight.bmp"), 1, 2);
		}

		// Bazooka
		if (false == ResourcesManager::GetInst().IsLoadTexture("bazOnLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("bazOnLeft.bmp"), 1, 7);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("bazOnRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("bazOnRight.bmp"), 1, 7);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("bazAimLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("bazAimLeft.bmp"), 1, 32);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("bazAimRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("bazAimRight.bmp"), 1, 32);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("bazOffLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("bazOffLeft.bmp"), 1, 7);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("bazOffRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("bazOffRight.bmp"), 1, 7);
		}
		
	}

	
	MainRenderer = CreateRenderer(RenderOrder::Player);

	// Animation
	{
		// Left
		MainRenderer->CreateAnimation("Left_Idle", "idleLeft.bmp", 0, 5, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Move", "walkLeft.bmp", 0, 14, 0.2f, true);
		MainRenderer->CreateAnimation("Left_JumpReady", "jumpReadyLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_JumpUp", "flyUpLeft.bmp", 0, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Jump", "flyLinkLeft.bmp", 0, 6, 0.1f, false);
		//MainRenderer->CreateAnimation("Left_JumpDown", "flyDownLeft.bmp", 0, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Falling", "flyDownLeft.bmp", 0, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Left_BazookaOn", "bazOnLeft.bmp", 0, 6, 0.1f, false);
		MainRenderer->CreateAnimation("Left_BazookaOff", "bazOffLeft.bmp", 0, 6, 0.1f, false);


		// Right
		MainRenderer->CreateAnimation("Right_Idle", "idleRight.bmp", 0, 5, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Move", "walkRight.bmp", 0, 14, 0.2f, true);
		MainRenderer->CreateAnimation("Right_JumpReady", "jumpReadyRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_JumpUp", "flyUpRight.bmp", 0, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Jump", "flyLinkRight.bmp", 0, 6, 0.1f, false);
		//MainRenderer->CreateAnimation("Right_JumpDown", "flyDownRight.bmp", 0, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Falling", "flyDownRight.bmp", 0, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Right_BazookaOn", "bazOnRight.bmp", 0, 6, 0.1f, false);
		MainRenderer->CreateAnimation("Right_BazookaOff", "bazOffRight.bmp", 0, 6, 0.1f, false);

		// BazookaAnimation
		for (int i = 0; i < 32; i++)
		{
			MainRenderer->CreateAnimation("Left_Bazooka" + std::to_string(i), "bazAimLeft.bmp", i, i, 0.1f, false);
			MainRenderer->CreateAnimation("Right_Bazooka" + std::to_string(i), "bazAimRight.bmp", i, i, 0.1f, false);
		}
	}
	
	{
		//Collision
	}

	MainRenderer->SetRenderPos({ 0, -15 });

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
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	{
	CollisionData Data;

	Data.Pos = ActorCameraPos();

	Data.Scale = { 5,5 };

	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}

	{
		CollisionData Data;

		Data.Pos = ActorCameraPos() + LeftCheckPos;

		Data.Scale = { 5,5 };

		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}

	{
		CollisionData Data;

		Data.Pos = ActorCameraPos() + RightCheckPos;

		Data.Scale = { 5,5 };

		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}

	{
		CollisionData Data;

		Data.Pos = ActorCameraPos() + UpCheckPos;

		Data.Scale = { 5,5 };

		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}
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
		case PlayerState::JumpReady:
			JumpReadyStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Falling:
			FallingStart();
			break;
		case PlayerState::BazookaOn:
			BazookaOnStart();
			break;
		case PlayerState::Bazooka:
			BazookaStart();
		case PlayerState::BazookaOff:
			BazookaOffStart();
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
	case PlayerState::JumpReady:
		return JumpReadyUpdate(_Delta);
	case PlayerState::Jump:
		return JumpUpdate(_Delta);
	case PlayerState::Falling:
		return FallingUpdate(_Delta);
	case PlayerState::BazookaOn:
		return BazookaOnUpdate(_Delta);
	case PlayerState::Bazooka:
		return BazookaUpdate(_Delta);
	case PlayerState::BazookaOff:
		return BazookaOffUpdate(_Delta);
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

	if (true != IsTurnPlayer)
	{
		return;
	}

	if (true == GameEngineInput::IsFree(VK_LEFT) && true == GameEngineInput::IsFree(VK_RIGHT))
	{
		return;
	}

	if (true == GameEngineInput::IsDown(VK_LEFT) || true == GameEngineInput::IsFree(VK_RIGHT))
	{
		PlayerDir CurDir = PlayerDir::Left;
		if (Dir == CurDir)
		{
			return;
		}
		Dir = CurDir;
		CurAngle = 180 - CurAngle;
		ChangeAnimationState(CurState);
		return;
	}

	if (true == GameEngineInput::IsFree(VK_LEFT) || true == GameEngineInput::IsDown(VK_RIGHT))
	{
		PlayerDir CurDir = PlayerDir::Right;
		if (Dir == CurDir)
		{
			return;
		}
		Dir = CurDir;
		CurAngle = 180 - CurAngle;
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
		// 움직일 곳의 Pos를 MovePos에 담았다.
	}
	

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);
		// 플레이어가 공중이면
		if (Color == RGB(255, 255, 255))
		{
			// 움직일 예정의 곳도 공중인지 체크한다.
			if (RGB(255, 255, 255) == GetGroundColor(RGB(255, 255, 255), MovePos1))
			{
				// 움직일 곳 또한 공중이라면
				float4 XPos = float4::ZERO;
				float4 Dir = MovePos1.X <= 0.0f ? float4::RIGHT : float4::LEFT;

				while (RGB(0, 0, 255) != GetGroundColor(RGB(255, 255, 255), MovePos1 + XPos))
				{
					XPos += Dir;

					if (abs(XPos.X) > 50.0f)
					{
						break;
					}
				}

				float4 YPos = float4::ZERO;
				while (RGB(0, 0, 255) != GetGroundColor(RGB(255, 255, 255), MovePos1 + YPos))
				{
					YPos.Y += 2;

					if (YPos.Y > 60.0f)
					{
						break;
					}
				}

				if (abs(XPos.X) >= YPos.Y)
				{
					while (RGB(0, 0, 255) != GetGroundColor(RGB(255, 255, 255), MovePos1))
					{
						MovePos1.Y += 2;
					}
				}

			}
			AddPos(MovePos1);
		}
	}
}