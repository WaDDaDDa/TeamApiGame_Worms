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
#include <GameEngineCore/GameEngineCollision.h>

#include "UI_PlayerInfo.h"

#define RIGHT_UP_MAXANGLE  -90
#define RIGHT_DOWN_MAXANGLE  90
#define LEFT_UP_MAXANGLE 270
#define LEFT_DOWN_MAXANGLE 90

std::vector<Player*> Player::AllPlayer;

float4 Player::DirPos = float4::ZERO;

Player::Player()
{
	AllPlayer.push_back(this);
	TurnPlayerIndex++;
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
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Blank.bmp"));
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

		// Uzi
		if (false == ResourcesManager::GetInst().IsLoadTexture("uziOnLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("uziOnLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("uziOnRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("uziOnRight.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("uziAimLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("uziAimLeft.bmp"), 1, 32);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("uziAimRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("uziAimRight.bmp"), 1, 32);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("uziFireLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("uziFireLeft.bmp"), 1, 32);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("uziFireRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("uziFireRight.bmp"), 1, 32);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("uziOffLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("uziOffLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("uziOffRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("uziOffRight.bmp"), 1, 10);
		}

		// HomingMissile
		if (false == ResourcesManager::GetInst().IsLoadTexture("homingOnLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("homingOnLeft.bmp"), 1, 7);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("homingOnRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("homingOnRight.bmp"), 1, 7);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("homingAimLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("homingAimLeft.bmp"), 1, 32);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("homingAimRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("homingAimRight.bmp"), 1, 32);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("homingOffLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("homingOffLeft.bmp"), 1, 7);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("homingOffRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("homingOffRight.bmp"), 1, 7);
		}

		//Sheep
		if (false == ResourcesManager::GetInst().IsLoadTexture("sheepOnLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("sheepOnLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("sheepOnRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("sheepOnRight.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("sheepOffLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("sheepOffLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("sheepOffRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("sheepOffRight.bmp"), 1, 10);
		}

		// Granade
		if (false == ResourcesManager::GetInst().IsLoadTexture("grnOnLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("grnOnLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("grnOnRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("grnOnRight.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("grnAimLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("grnAimLeft.bmp"), 1, 32);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("grnAimRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("grnAimRight.bmp"), 1, 32);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("grnOffLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("grnOffLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("grnOffRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("grnOffRight.bmp"), 1, 10);
		}

		// Teleport
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportOnLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportOnLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportOnRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportOnRight.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportFireLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportFireLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportFireRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportFireRight.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportMoveLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportMoveLeft.bmp"), 1, 48);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportMoveRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportMoveRight.bmp"), 1, 48);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportOffLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportOffLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportOffRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportOffRight.bmp"), 1, 10);
		}

		//AirStrike
		if (false == ResourcesManager::GetInst().IsLoadTexture("AirStrikeOnLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("AirStrikeOnLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("AirStrikeOnRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("AirStrikeOnRight.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("AirStrikeFireLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("AirStrikeFireLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("AirStrikeFireRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("AirStrikeFireRight.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("AirStrikeOffLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("AirStrikeOffLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("AirStrikeOffRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("AirStrikeOffRight.bmp"), 1, 10);
		}

		// grider
		if (false == ResourcesManager::GetInst().IsLoadTexture("girderOnLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("girderOnLeft.bmp"), 1, 15);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("girderOnRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("girderOnRight.bmp"), 1, 15);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("girderOffLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("girderOffLeft.bmp"), 1, 15);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("girderOffRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("girderOffRight.bmp"), 1, 15);
		}

		// HolyGranade
		if (false == ResourcesManager::GetInst().IsLoadTexture("HolyGranadeOnLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("HolyGranadeOnLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("HolyGranadeOnRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("HolyGranadeOnRight.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("HolyGranadeOffLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("HolyGranadeOffLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("HolyGranadeOffRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("HolyGranadeOffRight.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("HolyGranadeAimLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("HolyGranadeAimLeft.bmp"), 1, 32);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("HolyGranadeAimRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("HolyGranadeAimRight.bmp"), 1, 32);
		}

		
		
		// DamageFly
		if (false == ResourcesManager::GetInst().IsLoadTexture("wfly1_L.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("wfly1_L.bmp"), 1, 32);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("wfly1_R.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("wfly1_R.bmp"), 1, 32);
		}

		// Die
		if (false == ResourcesManager::GetInst().IsLoadTexture("wdieLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("wdieLeft.bmp"), 1, 60);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("wdieRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("wdieRight.bmp"), 1, 60);
		}

		// GraveStone
		if (false == ResourcesManager::GetInst().IsLoadTexture("GraveStone.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("GraveStone.bmp"), 5, 12); 
		}

		// WinMotion
		if (false == ResourcesManager::GetInst().IsLoadTexture("winLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("winLeft.bmp"), 1, 14);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("winRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("winRight.bmp"), 1, 14);
		}

		// Diving
		if (false == ResourcesManager::GetInst().IsLoadTexture("DivingLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("DivingLeft.bmp"), 1, 3);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("DivingRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("DivingRight.bmp"), 1, 3);
		}

		// CrossHairRenderer Resources
		if (false == ResourcesManager::GetInst().IsLoadTexture("crshairb_L.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Misc\\Aim_Taget\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("crshairb_L.bmp"), 1, 32);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("crshairb_R.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Misc\\Aim_Taget\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("crshairb_R.bmp"), 1, 32);
		}

		// Gauge Resources
		if (false == ResourcesManager::GetInst().IsLoadTexture("blob.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Effects\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("blob.bmp"), 1, 16);
		}
	}

	{  //Grider 이미지
		Gride_Renderer = CreateRenderer(GetOrder());

		if (false == ResourcesManager::GetInst().IsLoadTexture("grdl0.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl0.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl1.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl2.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl3.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl4.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl5.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl6.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl7.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl8.bmp"));

			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds0.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds1.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds2.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds3.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds4.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds5.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds6.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds7.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds8.bmp"));

			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl0b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl1b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl2b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl3b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl4b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl5b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl6b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl7b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl8b.bmp"));

			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds0b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds1b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds2b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds3b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds4b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds5b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds6b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds7b.bmp"));
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds8b.bmp"));
		}

		Gride_Renderer->SetTexture("grds0.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds0b.bmp");
		Gride_Renderer->Off();
	}

	// Gauge Texture
	{
		GaugeRenderer0 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer0->SetSprite("blob.bmp", 0);
		GaugeRenderer0->SetRenderScale({ 64, 64 });
		GaugeRenderer1 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer1->SetSprite("blob.bmp", 1);
		GaugeRenderer1->SetRenderScale({ 64, 64 });
		GaugeRenderer2 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer2->SetSprite("blob.bmp", 2);
		GaugeRenderer2->SetRenderScale({ 64, 64 });
		GaugeRenderer3 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer3->SetSprite("blob.bmp", 3);
		GaugeRenderer3->SetRenderScale({ 64, 64 });
		GaugeRenderer4 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer4->SetSprite("blob.bmp", 4);
		GaugeRenderer4->SetRenderScale({ 64, 64 });
		GaugeRenderer5 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer5->SetSprite("blob.bmp", 5);
		GaugeRenderer5->SetRenderScale({ 64, 64 });
		GaugeRenderer6 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer6->SetSprite("blob.bmp", 6);
		GaugeRenderer6->SetRenderScale({ 64, 64 });
		GaugeRenderer7 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer7->SetSprite("blob.bmp", 7);
		GaugeRenderer7->SetRenderScale({ 64, 64 });
		GaugeRenderer8 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer8->SetSprite("blob.bmp", 8);
		GaugeRenderer8->SetRenderScale({ 64, 64 });
		GaugeRenderer9 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer9->SetSprite("blob.bmp", 9);
		GaugeRenderer9->SetRenderScale({ 64, 64 });
		GaugeRenderer10 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer10->SetSprite("blob.bmp", 10);
		GaugeRenderer10->SetRenderScale({ 64, 64 });
		GaugeRenderer11 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer11->SetSprite("blob.bmp", 11);
		GaugeRenderer11->SetRenderScale({ 64, 64 });
		GaugeRenderer12 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer12->SetSprite("blob.bmp", 12);
		GaugeRenderer12->SetRenderScale({ 64, 64 });
		GaugeRenderer13 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer13->SetSprite("blob.bmp", 13);
		GaugeRenderer13->SetRenderScale({ 64, 64 });
		GaugeRenderer14 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer14->SetSprite("blob.bmp", 14);
		GaugeRenderer14->SetRenderScale({ 64, 64 });
		GaugeRenderer15 = CreateRenderer(RenderOrder::Gauge);
		GaugeRenderer15->SetSprite("blob.bmp", 15);
		GaugeRenderer15->SetRenderScale({ 64, 64 });
		AllGaugeOff();
	}

	MainRenderer = CreateRenderer(RenderOrder::Player);
	CrossHairRenderer = CreateRenderer(RenderOrder::CrossHair);

	// Animation
	{
		// Left
		MainRenderer->CreateAnimation("Left_Idle", "idleLeft.bmp", 0, 5, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Move", "walkLeft.bmp", 0, 14, 0.1f, true);
		MainRenderer->CreateAnimation("Left_JumpReady", "jumpReadyLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_JumpUp", "flyUpLeft.bmp", 0, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Jump", "flyLinkLeft.bmp", 0, 6, 0.1f, false);
		//MainRenderer->CreateAnimation("Left_JumpDown", "flyDownLeft.bmp", 0, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Falling", "flyDownLeft.bmp", 0, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Damaging", "wfly1_L.bmp", 0, 31, 0.05f, false);
		MainRenderer->CreateAnimation("Left_Death", "wdieLeft.bmp", 0, 59, 0.05f, false);
		MainRenderer->CreateAnimation("Left_BazookaOn", "bazOnLeft.bmp", 0, 6, 0.05f, false);
		MainRenderer->CreateAnimation("Left_BazookaOff", "bazOffLeft.bmp", 0, 6, 0.05f, false);
		MainRenderer->CreateAnimation("Left_UziOn", "uziOnLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_UziOff", "uziOffLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_HomingMissileOn", "homingOnLeft.bmp", 0, 6, 0.05f, false);
		MainRenderer->CreateAnimation("Left_HomingMissileOff", "homingOffLeft.bmp", 0, 6, 0.05f, false);
		MainRenderer->CreateAnimation("Left_SheepOn", "sheepOnLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_Sheep", "sheepOnLeft.bmp", 9, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_SheepOff", "sheepOffLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_GranadeOn", "grnOnLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_GranadeOff", "grnOffLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_TeleportOn", "teleportOnLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_Teleport", "teleportOnLeft.bmp", 9, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_TeleportFire", "teleportFireLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_TeleportMoveOn", "teleportMoveLeft.bmp", 0, 47, 0.01f, false);
		MainRenderer->CreateAnimation("Left_TeleportMoveOff", "teleportMoveLeft.bmp", 47, 0, 0.01f, false);
		MainRenderer->CreateAnimation("Left_TeleportOff", "teleportOffLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_AirStrikeOn", "AirStrikeOnLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_AirStrike", "AirStrikeOnLeft.bmp", 9, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_AirStrikeFire", "AirStrikeFireLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_AirStrikeOff", "AirStrikeOffLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_GirderOn", "girderOnLeft.bmp", 0, 14, 0.05f, false);
		MainRenderer->CreateAnimation("Left_Girder", "girderOnLeft.bmp", 14, 14, 0.05f, false);
		MainRenderer->CreateAnimation("Left_GirderOff", "girderOffLeft.bmp", 0, 14, 0.05f, false);
		MainRenderer->CreateAnimation("Left_DonkeyOn", "AirStrikeOnLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_Donkey", "AirStrikeOnLeft.bmp", 9, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_DonkeyFire", "AirStrikeFireLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_DonkeyOff", "AirStrikeOffLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_HolyGranadeOn", "HolyGranadeOnLeft.bmp", 0, 9, 0.1f, false);
		MainRenderer->CreateAnimation("Left_HolyGranadeOff", "HolyGranadeOffLeft.bmp", 0, 9, 0.1f, false);
		MainRenderer->CreateAnimation("Left_SuperSheepOn", "sheepOnLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_SuperSheep", "sheepOnLeft.bmp", 9, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_SuperSheepOff", "sheepOffLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_GraveStone", "GraveStone.bmp", 0, 59, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Win", "winLeft.bmp", 0, 13, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Diving1", "DivingLeft.bmp", 0, 2, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Diving2", "DivingLeft.bmp", 2, 0, 0.1f, false);


		// Right
		MainRenderer->CreateAnimation("Right_Idle", "idleRight.bmp", 0, 5, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Move", "walkRight.bmp", 0, 14, 0.2f, true);
		MainRenderer->CreateAnimation("Right_JumpReady", "jumpReadyRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_JumpUp", "flyUpRight.bmp", 0, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Jump", "flyLinkRight.bmp", 0, 6, 0.1f, false);
		//MainRenderer->CreateAnimation("Right_JumpDown", "flyDownRight.bmp", 0, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Falling", "flyDownRight.bmp", 0, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Damaging", "wfly1_R.bmp", 0, 31, 0.05f, false);
		MainRenderer->CreateAnimation("Right_Death", "wdieRight.bmp", 0, 59, 0.05f, false);
		MainRenderer->CreateAnimation("Right_BazookaOn", "bazOnRight.bmp", 0, 6, 0.05f, false);
		MainRenderer->CreateAnimation("Right_BazookaOff", "bazOffRight.bmp", 0, 6, 0.05f, false);
		MainRenderer->CreateAnimation("Right_UziOn", "uziOnRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_UziOff", "uziOffRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_HomingMissileOn", "homingOnRight.bmp", 0, 6, 0.05f, false);
		MainRenderer->CreateAnimation("Right_HomingMissileOff", "homingOffRight.bmp", 0, 6, 0.05f, false);
		MainRenderer->CreateAnimation("Right_SheepOn", "sheepOnRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_Sheep", "sheepOnRight.bmp", 9, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_SheepOff", "sheepOffRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_GranadeOn", "grnOnRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_GranadeOff", "grnOffRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_TeleportOn", "teleportOnRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_Teleport", "teleportOnRight.bmp", 9, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_TeleportFire", "teleportFireRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_TeleportMoveOn", "teleportMoveRight.bmp", 0, 47, 0.01f, false);
		MainRenderer->CreateAnimation("Right_TeleportMoveOff", "teleportMoveRight.bmp", 47, 0, 0.01f, false);
		MainRenderer->CreateAnimation("Right_TeleportOff", "teleportOffRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_AirStrikeOn", "AirStrikeOnRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_AirStrike", "AirStrikeOnRight.bmp", 9, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_AirStrikeFire", "AirStrikeFireRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_AirStrikeOff", "AirStrikeOffRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_GirderOn", "girderOnRight.bmp", 0, 14, 0.05f, false);
		MainRenderer->CreateAnimation("Right_Girder", "girderOnRight.bmp", 14, 14, 0.05f, false);
		MainRenderer->CreateAnimation("Right_GirderOff", "girderOffRight.bmp", 0, 14, 0.05f, false);
		MainRenderer->CreateAnimation("Right_DonkeyOn", "AirStrikeOnRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_Donkey", "AirStrikeOnRight.bmp", 9, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_DonkeyFire", "AirStrikeFireRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_DonkeyOff", "AirStrikeOffRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_HolyGranadeOn", "HolyGranadeOnRight.bmp", 0, 9, 0.1f, false);
		MainRenderer->CreateAnimation("Right_HolyGranadeOff", "HolyGranadeOffRight.bmp", 0, 9, 0.1f, false);
		MainRenderer->CreateAnimation("Right_SuperSheepOn", "sheepOnRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_SuperSheep", "sheepOnRight.bmp", 9, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_SuperSheepOff", "sheepOffRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_GraveStone", "GraveStone.bmp", 0, 59, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Win", "winRight.bmp", 0, 13, 0.03f, true);
		MainRenderer->CreateAnimation("Right_Diving1", "DivingRight.bmp", 0, 2, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Diving2", "DivingRight.bmp", 2, 0, 0.1f, false);

		// BazookaAnimation
		for (int i = 0; i < 32; i++)
		{
			MainRenderer->CreateAnimation("Left_Bazooka" + std::to_string(i), "bazAimLeft.bmp", i, i, 0.1f, false);
			MainRenderer->CreateAnimation("Right_Bazooka" + std::to_string(i), "bazAimRight.bmp", i, i, 0.1f, false);
		}
		// UziAnimation
		for (int i = 0; i < 32; i++)
		{
			MainRenderer->CreateAnimation("Left_Uzi" + std::to_string(i), "uziAimLeft.bmp", i, i, 0.2f, false);
			MainRenderer->CreateAnimation("Right_Uzi" + std::to_string(i), "uziAimRight.bmp", i, i, 0.2f, false);
		}
		//UziFireAnimation
		for (int i = 0; i < 32; i++)
		{
			MainRenderer->CreateAnimation("Left_UziFire" + std::to_string(i), "uziFireLeft.bmp", i, i, 0.5f, false);
			MainRenderer->CreateAnimation("Right_UziFire" + std::to_string(i), "uziFireRight.bmp", i, i, 0.5f, false);
		}
		// HomingMissileAnimation
		for (int i = 0; i < 32; i++)
		{
			MainRenderer->CreateAnimation("Left_HomingMissile" + std::to_string(i), "homingAimLeft.bmp", i, i, 0.1f, false);
			MainRenderer->CreateAnimation("Right_HomingMissile" + std::to_string(i), "homingAimRight.bmp", i, i, 0.1f, false);
		}
		// GranadeAnimation
		for (int i = 0; i < 32; i++)
		{
			MainRenderer->CreateAnimation("Left_Granade" + std::to_string(i), "grnAimLeft.bmp", i, i, 0.1f, false);
			MainRenderer->CreateAnimation("Right_Granade" + std::to_string(i), "grnAimRight.bmp", i, i, 0.1f, false);
		}
		// HolyGranadeAnimation
		for (int i = 0; i < 32; i++)
		{
			MainRenderer->CreateAnimation("Left_HolyGranade" + std::to_string(i), "HolyGranadeAimLeft.bmp", i, i, 0.1f, false);
			MainRenderer->CreateAnimation("Right_HolyGranade" + std::to_string(i), "HolyGranadeAimRight.bmp", i, i, 0.1f, false);
		}

		// CrossHairAnimation
		for (int i = 0; i < 32; i++)
		{
			CrossHairRenderer->CreateAnimation("Left_CrossHair" + std::to_string(i), "crshairb_L.bmp", i, i, 0.1f, false);
			CrossHairRenderer->CreateAnimation("Right_CrossHair" + std::to_string(i), "crshairb_R.bmp", i, i, 0.1f, false);
		}

	}
	
	{
		//Collision
		PlayerBodyCollision = CreateCollision(CollisionOrder::PlayerBody);

		PlayerBodyCollision->SetCollisionScale({ 20, 25 });
		PlayerBodyCollision->SetCollisionType(CollisionType::Rect);
		PlayerBodyCollision->SetCollisionPos({ 0, -10 });
	}

	MainRenderer->SetRenderPos({ 0, -15 });

	Dir = PlayerDir::Right;
	ChangeState(PlayerState::Idle);

	// 길이 : 92
	//CrossHairRenderer->SetRenderPos({ 0 , -107 });
	ChangeCrossHairAnimation("CrossHair0");
	CrossHairRenderer->Off();



	PlayerInfoUI = GetLevel()->CreateActor<UI_PlayerInfo>();
	
	// 색깔 적용 테스트용
	for (int i = 0; i < AllPlayer.size(); i++)
	{
		PlayerInfoUI->SetPlayerColorIndex(i);
	}

}


void Player::Update(float _Delta)
{	
	CameraFocus(_Delta);

	if (IsTurnPlayer == false)
	{
		// GameEngineInput::Reset;
	}

	SetDirPosNormalize();
	StateUpdate(_Delta);

	

	// UI 테스트용 임시 코드
	PlayerInfoUI->SetPos({ GetPos().X - GetLevel()->GetMainCamera()->GetPos().X,  (GetPos().Y - GetLevel()->GetMainCamera()->GetPos().Y) - 70});
	PlayerInfoUI->UpdateData_PlayerInfoUI(&Hp, IsTurnPlayer, TurnPlayerIndex);

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

	//std::string Text = "";
	//Text += std::to_string(Hp);
	//TextOutA(dc, ActorCameraPos().iX(), (ActorCameraPos().iY() - 50), Text.c_str(), static_cast<int>(Text.size()));
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
		case PlayerState::JumpReady:
			JumpReadyStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Falling:
			FallingStart();
			break;
		case PlayerState::Damaging:
			DamagingStart();
			break;
		case PlayerState::Death:
			DeathStart();
			break;
		case PlayerState::DeathEnd:
			DeathEndStart();
			break;
		case PlayerState::BazookaOn:
			BazookaOnStart();
			break;
		case PlayerState::Bazooka:
			BazookaStart();
			break;
		case PlayerState::BazookaFire:
			BazookaFireStart();
			break;
		case PlayerState::BazookaOff:
			BazookaOffStart();
			break;
		case PlayerState::UziOn:
			UziOnStart();
			break;
		case PlayerState::Uzi:
			UziStart();
			break;
		case PlayerState::UziFire:
			UziFireStart();
			break;
		case PlayerState::UziOff:
			UziOffStart();
			break;
		case PlayerState::HomingMissileOn:
			HomingMissileOnStart();
			break;
		case PlayerState::HomingMissile:
			HomingMissileStart();
			break;
		case PlayerState::HomingMissileFire:
			HomingMissileFireStart();
			break;
		case PlayerState::HomingMissileOff:
			HomingMissileOffStart();
			break;
		case PlayerState::SheepOn:
			SheepOnStart();
			break;
		case PlayerState::Sheep:
			SheepStart();
			break;
		case PlayerState::SheepFire:
			SheepFireStart();
			break;
		case PlayerState::SheepOff:
			SheepOffStart();
			break;
		case PlayerState::GranadeOn:
			GranadeOnStart();
			break;
		case PlayerState::Granade:
			GranadeStart();
			break;
		case PlayerState::GranadeFire:
			GranadeFireStart();
			break;
		case PlayerState::GranadeOff:
			GranadeOffStart();
			break;
		case PlayerState::TeleportOn:
			TeleportOnStart();
			break;
		case PlayerState::Teleport:
			TeleportStart();
			break;
		case PlayerState::TeleportFire:
			TeleportFireStart();
			break;
		case PlayerState::TeleportMove:
			TeleportMoveStart();
			break;
		case PlayerState::TeleportOff:
			TeleportOffStart();
			break;
		case PlayerState::AirStrikeOn:
			AirStrikeOnStart();
			break;
		case PlayerState::AirStrike:
			AirStrikeStart();
			break;
		case PlayerState::AirStrikeFire:
			AirStrikeFireStart();
			break;
		case PlayerState::AirStrikeOff:
			AirStrikeOffStart();
			break;
		case PlayerState::GirderOn:
			GirderOnStart();
			break;
		case PlayerState::Girder:
			GirderStart();
			break;
		case PlayerState::GirderOff:
			GirderOffStart();
			break;
		case PlayerState::DonkeyOn:
			DonkeyOnStart();
			break;
		case PlayerState::Donkey:
			DonkeyStart();
			break;
		case PlayerState::DonkeyFire:
			DonkeyFireStart();
			break;
		case PlayerState::DonkeyOff:
			DonkeyOffStart();
			break;
		case PlayerState::HolyGranadeOn:
			HolyGranadeOnStart();
			break;
		case PlayerState::HolyGranade:
			HolyGranadeStart();
			break;
		case PlayerState::HolyGranadeFire:
			HolyGranadeFireStart();
			break;
		case PlayerState::HolyGranadeOff:
			HolyGranadeOffStart();
			break;
		case PlayerState::SuperSheepOn:
			SuperSheepOnStart();
			break;
		case PlayerState::SuperSheep:
			SuperSheepStart();
			break;
		case PlayerState::SuperSheepOff:
			SuperSheepOffStart();
			break;
		case PlayerState::Win:
			WinStart();
			break;
		case PlayerState::Diving:
			DivingStart();
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
	case PlayerState::JumpReady:
		return JumpReadyUpdate(_Delta);
	case PlayerState::Jump:
		return JumpUpdate(_Delta);
	case PlayerState::Falling:
		return FallingUpdate(_Delta);
	case PlayerState::Damaging:
		return DamagingUpdate(_Delta);
	case PlayerState::Death:
		return DeathUpdate(_Delta);
	case PlayerState::DeathEnd:
		return DeathEndUpdate(_Delta);
	case PlayerState::BazookaOn:
		return BazookaOnUpdate(_Delta);
	case PlayerState::Bazooka:
		return BazookaUpdate(_Delta);
	case PlayerState::BazookaFire:
		return BazookaFireUpdate(_Delta);
	case PlayerState::BazookaOff:
		return BazookaOffUpdate(_Delta);
	case PlayerState::UziOn:
		return UziOnUpdate(_Delta);
	case PlayerState::Uzi:
		return UziUpdate(_Delta);
	case PlayerState::UziFire:
		return UziFireUpdate(_Delta);
	case PlayerState::UziOff:
		return UziOffUpdate(_Delta);
	case PlayerState::HomingMissileOn:
		return HomingMissileOnUpdate(_Delta);
	case PlayerState::HomingMissile:
		return HomingMissileUpdate(_Delta);
	case PlayerState::HomingMissileFire:
		return HomingMissileFireUpdate(_Delta);
	case PlayerState::HomingMissileOff:
		return HomingMissileOffUpdate(_Delta);
	case PlayerState::SheepOn:
		return SheepOnUpdate(_Delta);
	case PlayerState::Sheep:
		return SheepUpdate(_Delta);
	case PlayerState::SheepFire:
		return SheepFireUpdate(_Delta);
	case PlayerState::SheepOff:
		return SheepOffUpdate(_Delta);
	case PlayerState::GranadeOn:
		return GranadeOnUpdate(_Delta);
	case PlayerState::Granade:
		return GranadeUpdate(_Delta);
	case PlayerState::GranadeFire:
		return GranadeFireUpdate(_Delta);
	case PlayerState::GranadeOff:
		return GranadeOffUpdate(_Delta);
	case PlayerState::TeleportOn:
		return TeleportOnUpdate(_Delta);
	case PlayerState::Teleport:
		return TeleportUpdate(_Delta);
	case PlayerState::TeleportFire:
		return TeleportFireUpdate(_Delta);
	case PlayerState::TeleportMove:
		return TeleportMoveUpdate(_Delta);
	case PlayerState::TeleportOff:
		return TeleportOffUpdate(_Delta);
	case PlayerState::AirStrikeOn:
		return AirStrikeOnUpdate(_Delta);
	case PlayerState::AirStrike:
		return AirStrikeUpdate(_Delta);
	case PlayerState::AirStrikeFire:
		return AirStrikeFireUpdate(_Delta);
	case PlayerState::AirStrikeOff:
		return AirStrikeOffUpdate(_Delta);
	case PlayerState::GirderOn:
		return GirderOnUpdate(_Delta);
	case PlayerState::Girder:
		return GirderUpdate(_Delta);
	case PlayerState::GirderOff:
		return GirderOffUpdate(_Delta);
	case PlayerState::DonkeyOn:
		return DonkeyOnUpdate(_Delta);
	case PlayerState::Donkey:
		return DonkeyUpdate(_Delta);
	case PlayerState::DonkeyFire:
		return DonkeyFireUpdate(_Delta);
	case PlayerState::DonkeyOff:
		return DonkeyOffUpdate(_Delta);
	case PlayerState::HolyGranadeOn:
		return HolyGranadeOnUpdate(_Delta);
	case PlayerState::HolyGranade:
		return HolyGranadeUpdate(_Delta);
	case PlayerState::HolyGranadeFire:
		return HolyGranadeFireUpdate(_Delta);
	case PlayerState::HolyGranadeOff:
		return HolyGranadeOffUpdate(_Delta);
	case PlayerState::SuperSheepOn:
		return SuperSheepOnUpdate(_Delta);
	case PlayerState::SuperSheep:
		return SuperSheepUpdate(_Delta);
	case PlayerState::SuperSheepOff:
		return SuperSheepOffUpdate(_Delta);
	case PlayerState::Win:
		return WinUpdate(_Delta);
	case PlayerState::Diving:
		return DivingUpdate(_Delta);
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

void Player::ChangeCrossHairAnimation(const std::string& _State)
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
	CrossHairRenderer->ChangeAnimation(AnimationName);
}

void Player::ChangeCrossHairRenderPos(int _iCurAngle)
{
	switch (_iCurAngle)
	{
	case -90:
		ChangeCrossHairAnimation("CrossHair31");
		break;
	case -84:
		ChangeCrossHairAnimation("CrossHair30");
		break;
	case -78:
		ChangeCrossHairAnimation("CrossHair29");
		break;
	case -73:
		ChangeCrossHairAnimation("CrossHair28");
		break;
	case -67:
		ChangeCrossHairAnimation("CrossHair27");
		break;
	case -61:
		ChangeCrossHairAnimation("CrossHair26");
		break;
	case -56:
		ChangeCrossHairAnimation("CrossHair25");
		break;
	case -50:
		ChangeCrossHairAnimation("CrossHair24");
		break;
	case -45:
		ChangeCrossHairAnimation("CrossHair23");
		break;
	case -39:
		ChangeCrossHairAnimation("CrossHair22");
		break;
	case -33:
		ChangeCrossHairAnimation("CrossHair21");
		break;
	case -28:
		ChangeCrossHairAnimation("CrossHair20");
		break;
	case -22:
		ChangeCrossHairAnimation("CrossHair19");
		break;
	case -16:
		ChangeCrossHairAnimation("CrossHair18");
		break;
	case -11:
		ChangeCrossHairAnimation("CrossHair17");
		break;
	case -5:
		ChangeCrossHairAnimation("CrossHair16");
		break;
	case 0:
		ChangeCrossHairAnimation("CrossHair15");
		break;
	case 5:
		ChangeCrossHairAnimation("CrossHair14");
		break;
	case 11:
		ChangeCrossHairAnimation("CrossHair13");
		break;
	case 16:
		ChangeCrossHairAnimation("CrossHair12");
		break;
	case 22:
		ChangeCrossHairAnimation("CrossHair11");
		break;
	case 28:
		ChangeCrossHairAnimation("CrossHair10");
		break;
	case 33:
		ChangeCrossHairAnimation("CrossHair9");
		break;
	case 39:
		ChangeCrossHairAnimation("CrossHair8");
		break;
	case 45:
		ChangeCrossHairAnimation("CrossHair7");
		break;
	case 50:
		ChangeCrossHairAnimation("CrossHair6");
		break;
	case 56:
		ChangeCrossHairAnimation("CrossHair5");
		break;
	case 61:
		ChangeCrossHairAnimation("CrossHair4");
		break;
	case 67:
		ChangeCrossHairAnimation("CrossHair3");
		break;
	case 73:
		ChangeCrossHairAnimation("CrossHair2");
		break;
	case 78:
		ChangeCrossHairAnimation("CrossHair1");
		break;
	case 84:
		ChangeCrossHairAnimation("CrossHair0");
		break;
	}
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

		if (LengthX >= 0)
		{
			LengthX *= -1;
		}
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

		if (LengthX <= 0)
		{
			LengthX *= -1;
		}
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
				float4 Dir = MovePos1.X >= 0.0f ? float4::RIGHT : float4::LEFT;
				while (RGB(0, 0, 255) != GetGroundColor(RGB(255, 255, 255), MovePos1 + XPos))
				{
					XPos += Dir;
					
					if (abs(XPos.X) > 20.0f)
					{
						break;
					}
				}

				float4 YPos = float4::ZERO;
				while (RGB(0, 0, 255) != GetGroundColor(RGB(255, 255, 255), MovePos1 + YPos))
				{
					YPos.Y += 1;

					if (YPos.Y > 30.0f)
					{
						break;
					}
				}

				if (abs(XPos.X) >= YPos.Y)
				{
					while (RGB(0, 0, 255) != GetGroundColor(RGB(255, 255, 255), MovePos1))
					{
						MovePos1.Y += 1;
					}
				}

			}
			AddPos(MovePos1);
		}
	}
}

void Player::InputMove()
{
	
	if (true == GameEngineInput::IsPress(VK_LEFT)
		|| true == GameEngineInput::IsPress(VK_RIGHT))
	{

		CrossHairRenderer->Off();
		DirCheck();
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		CrossHairRenderer->Off();
		ChangeState(PlayerState::JumpReady);
		return;
	}
}

void Player::ChangeWeapon()
{
	if (true == GameEngineInput::IsDown('2'))
	{
		ChangeState(PlayerState::BazookaOn);
		return;
	}
	
	if (true == GameEngineInput::IsDown('3'))
	{
		ChangeState(PlayerState::UziOn);
		return;
	}

	if (true == GameEngineInput::IsDown('4'))
	{
		ChangeState(PlayerState::HomingMissileOn);
		return;
	}

	if (true == GameEngineInput::IsDown('5'))
	{
		ChangeState(PlayerState::SheepOn);
		return;
	}

	if (true == GameEngineInput::IsDown('6'))
	{
		ChangeState(PlayerState::GranadeOn);
		return;
	}

	if (true == GameEngineInput::IsDown('7'))
	{
		ChangeState(PlayerState::TeleportOn);
		return;
	}

	if (true == GameEngineInput::IsDown('8'))
	{
		//ChangeState(PlayerState::AirStrikeOn);
		ChangeState(PlayerState::HolyGranadeOn);
		return;
	}

	if (true == GameEngineInput::IsDown('9'))
	{
		ChangeState(PlayerState::GirderOn);
		//ChangeState(PlayerState::DonkeyOn);
		return;
	}



	//Debug Key
	//if (true == GameEngineInput::IsDown(VK_F4))
	//{
	//	Hp -= 100;
	//}
}

void Player::DamagingCheck()
{
	std::vector<GameEngineCollision*> _Col;
	if (true == PlayerBodyCollision->Collision(CollisionOrder::Bomb, _Col
		, CollisionType::Rect
		, CollisionType::CirCle)/* ||
		true == PlayerBodyCollision->Collision(CollisionOrder::Weapon, _Col
		, CollisionType::Rect
		, CollisionType::CirCle)*/
	)
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();
		}
		if (0 >= DamageCount)
		{
			ChangeState(PlayerState::Damaging);
		}
	}
	else
	{
		DamageCount = 0;
	}
}

void Player::ChangeAimAngle(float _Delta)
{
	// 오른쪽 각도 조절
	if (PlayerDir::Right == Dir)
	{
		if (true == GameEngineInput::IsPress(VK_UP))
		{
			CurAngle -= (5.625f * _Delta * AngleSpeed);
			LengthY -= (5.75f * _Delta * AngleSpeed);

			if (0 <= LengthY)
			{
				LengthX += (5.75f * _Delta * AngleSpeed);
			}
			else
			{
				LengthX -= (5.75f * _Delta * AngleSpeed);
			}

			if (CurAngle <= RIGHT_UP_MAXANGLE)
			{
				CurAngle = RIGHT_UP_MAXANGLE;
				LengthX = 0;
				LengthY = -92;
			}
		}

		if (true == GameEngineInput::IsPress(VK_DOWN))
		{
			CurAngle += (5.625f * _Delta * AngleSpeed);
			LengthY += (5.75f * _Delta * AngleSpeed);

			if (0 <= LengthY)
			{
				LengthX -= (5.75f * _Delta * AngleSpeed);
			}
			else
			{
				LengthX += (5.75f * _Delta * AngleSpeed);
			}

			if (CurAngle >= RIGHT_DOWN_MAXANGLE)
			{
				CurAngle = RIGHT_DOWN_MAXANGLE;
				LengthX = 0;
				LengthY = 92;
			}
		}
	}

	// 왼쪽 각도조절
	if (PlayerDir::Left == Dir)
	{
		if (true == GameEngineInput::IsPress(VK_UP))
		{		
			CurAngle += (5.625f * _Delta * AngleSpeed);
			LengthY -= (5.75f * _Delta * AngleSpeed);

			if (0 <= LengthY)
			{
				LengthX -= (5.75f * _Delta * AngleSpeed);
			}
			else
			{
				LengthX += (5.75f * _Delta * AngleSpeed);
			}

			if (CurAngle >= LEFT_UP_MAXANGLE)
			{
				CurAngle = LEFT_UP_MAXANGLE;
				LengthX = 0;
				LengthY = -92;
			}
		}
		
		if (true == GameEngineInput::IsPress(VK_DOWN))
		{
			CurAngle -= (5.625f * _Delta * AngleSpeed);
			LengthY += (5.75f * _Delta * AngleSpeed);

			if (0 <= LengthY)
			{
				LengthX += (5.75f * _Delta * AngleSpeed);
			}
			else
			{
				LengthX -= (5.75f * _Delta * AngleSpeed);
			}

			if (CurAngle <= LEFT_DOWN_MAXANGLE)
			{
				CurAngle = LEFT_DOWN_MAXANGLE;
				LengthX = 0;
				LengthY = -92;
			}
		}
	}

}

void Player::SetGauge(float _Delta)
{
	float4 GaugePos;
	GaugePos = CrossHairPos;
	GaugePos.Normalize();

	if (0.1f <= ChargingTime)
	{
		GaugeRenderer0->On();
		GaugeRenderer0->SetRenderPos({ GaugePos.X * 5.75f * 1, (GaugePos.Y * 5.75f * 1) - 15 });

		float4 DebugPos = GaugeRenderer0->GetRenderPos();
		int a = 0;
	}
	if (0.2f <= ChargingTime)
	{
		GaugeRenderer1->On();
		GaugeRenderer1->SetRenderPos({ GaugePos.X * 5.75f * 2, (GaugePos.Y * 5.75f * 2) - 15 });
	}
	if (0.3f <= ChargingTime)
	{
		GaugeRenderer2->On();
		GaugeRenderer2->SetRenderPos({ GaugePos.X * 5.75f * 3, (GaugePos.Y * 5.75f * 3) - 15 });
	}
	if (0.4f <= ChargingTime)
	{
		GaugeRenderer3->On();
		GaugeRenderer3->SetRenderPos({ GaugePos.X * 5.75f * 4, (GaugePos.Y * 5.75f * 4) - 15 });
	}
	if (0.5f <= ChargingTime)
	{
		GaugeRenderer4->On();
		GaugeRenderer4->SetRenderPos({ GaugePos.X * 5.75f * 5, (GaugePos.Y * 5.75f * 5) - 15 });
	}
	if (0.6f <= ChargingTime)
	{
		GaugeRenderer5->On();
		GaugeRenderer5->SetRenderPos({ GaugePos.X * 5.75f * 6, (GaugePos.Y * 5.75f * 6) - 15 });
	}
	if (0.7f <= ChargingTime)
	{
		GaugeRenderer6->On();
		GaugeRenderer6->SetRenderPos({ GaugePos.X * 5.75f * 7, (GaugePos.Y * 5.75f * 7) - 15 });
	}
	if (0.8f <= ChargingTime)
	{
		GaugeRenderer7->On();
		GaugeRenderer7->SetRenderPos({ GaugePos.X * 5.75f * 8, (GaugePos.Y * 5.75f * 8) - 15 });
	}
	if (0.9f <= ChargingTime)
	{
		GaugeRenderer8->On();
		GaugeRenderer8->SetRenderPos({ GaugePos.X * 5.75f * 9, (GaugePos.Y * 5.75f * 9) - 15 });
	}
	if (1.0f <= ChargingTime)
	{
		GaugeRenderer9->On();
		GaugeRenderer9->SetRenderPos({ GaugePos.X * 5.75f * 10, (GaugePos.Y * 5.75f * 10) - 15 });
	}
	if (1.1f <= ChargingTime)
	{
		GaugeRenderer10->On();
		GaugeRenderer10->SetRenderPos({ GaugePos.X * 5.75f * 11, (GaugePos.Y * 5.75f * 11) - 15 });
	}
	if (1.2f <= ChargingTime)
	{
		GaugeRenderer11->On();
		GaugeRenderer11->SetRenderPos({ GaugePos.X * 5.75f * 12, (GaugePos.Y * 5.75f * 12) - 15 });
	}
	if (1.3f <= ChargingTime)
	{
		GaugeRenderer12->On();
		GaugeRenderer12->SetRenderPos({ GaugePos.X * 5.75f * 13, (GaugePos.Y * 5.75f * 13) - 15 });
	}
	if (1.4f <= ChargingTime)
	{
		GaugeRenderer13->On();
		GaugeRenderer13->SetRenderPos({ GaugePos.X * 5.75f * 14, (GaugePos.Y * 5.75f * 14) - 15 });
	}
	if (1.5f <= ChargingTime)
	{
		GaugeRenderer14->On();
		GaugeRenderer14->SetRenderPos({ GaugePos.X * 5.75f * 15, (GaugePos.Y * 5.75f * 15) - 15 });
	}
	if (1.6f <= ChargingTime)
	{
		GaugeRenderer15->On();
		GaugeRenderer15->SetRenderPos({ GaugePos.X * 5.75f * 16, (GaugePos.Y * 5.75f * 16) - 15 });
	}

}

void Player::AllGaugeOff()
{
	GaugeRenderer0->Off();
	GaugeRenderer1->Off();
	GaugeRenderer2->Off();
	GaugeRenderer3->Off();
	GaugeRenderer4->Off();
	GaugeRenderer5->Off();
	GaugeRenderer6->Off();
	GaugeRenderer7->Off();
	GaugeRenderer8->Off();
	GaugeRenderer9->Off();
	GaugeRenderer10->Off();
	GaugeRenderer11->Off();
	GaugeRenderer12->Off();
	GaugeRenderer13->Off();
	GaugeRenderer14->Off();
	GaugeRenderer15->Off();
}