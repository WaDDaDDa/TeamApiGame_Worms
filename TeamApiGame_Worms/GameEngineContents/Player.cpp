#include "Player.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	// Resource 추가
	if (false)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");
		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("파일명"), 가로, 세로);
	}

	{
		//MainRenderer = CreateRenderer(RenderOrder::Player);

		//MainRenderer->CreateAnimation("aniname", "filename", start, end, frame, loop

		
	}
	
	{
		//Collision
	}

	ChangeState(PlayerState::Idle);
}
void Player::Update(float _Delta)
{
	StateUpdate(_Delta);
}
void Player::Render(float _Delta)
{
	// PosCheck
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	CollisionData Data;

	

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
	
	//MainRenderer->ChangeAnimation(AnimationName);
}