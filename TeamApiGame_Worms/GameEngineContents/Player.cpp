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
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("sheepOnLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("sheepOnRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("sheepOnRight.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("sheepOffLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("sheepOffLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("sheepOffRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("sheepOffRight.bmp"), 1, 10);
		}

		// Granade
		if (false == ResourcesManager::GetInst().IsLoadTexture("grnOnLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("grnOnLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("grnOnRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
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
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("grnOffLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("grnOffRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("grnOffRight.bmp"), 1, 10);
		}

		// Teleport
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportOnLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportOnLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportOnRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportOnRight.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportFireLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportFireLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportFireRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportFireRight.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportMoveLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportMoveLeft.bmp"), 1, 48);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportMoveRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportMoveRight.bmp"), 1, 48);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportOffLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportOffLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("teleportOffRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("teleportOffRight.bmp"), 1, 10);
		}

		//AirStrike
		if (false == ResourcesManager::GetInst().IsLoadTexture("AirStrikeOnLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("AirStrikeOnLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("AirStrikeOnRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("AirStrikeOnRight.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("AirStrikeOffLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("AirStrikeOffLeft.bmp"), 1, 10);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("AirStrikeOffRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("AirStrikeOffRight.bmp"), 1, 10);
		}

		// grider
		if (false == ResourcesManager::GetInst().IsLoadTexture("girderOnLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("girderOnLeft.bmp"), 1, 15);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("girderOnRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("girderOnRight.bmp"), 1, 15);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("girderOffLeft.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("girderOffLeft.bmp"), 1, 15);
		}
		if (false == ResourcesManager::GetInst().IsLoadTexture("girderOffRight.bmp"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsREsources");
			FilePath.MoveChild("ContentsResources\\Image\\Worms\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("girderOffRight.bmp"), 1, 15);
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
	}


	MainRenderer = CreateRenderer(RenderOrder::Player);

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
		MainRenderer->CreateAnimation("Left_AirStrikeOff", "AirStrikeOffLeft.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Left_GirderOn", "girderOnLeft.bmp", 0, 14, 0.05f, false);
		MainRenderer->CreateAnimation("Left_Girder", "girderOnLeft.bmp", 14, 14, 0.05f, false);
		MainRenderer->CreateAnimation("Left_GirderOff", "girderOffLeft.bmp", 0, 14, 0.05f, false);
		MainRenderer->CreateAnimation("Left_GraveStone", "GraveStone.bmp", 0, 59, 0.1f, true);


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
		MainRenderer->CreateAnimation("Right_AirStrikeOff", "AirStrikeOffRight.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_GirderOn", "girderOnRight.bmp", 0, 14, 0.05f, false);
		MainRenderer->CreateAnimation("Right_Girder", "girderOnRight.bmp", 14, 14, 0.05f, false);
		MainRenderer->CreateAnimation("Right_GirderOff", "girderOffRight.bmp", 0, 14, 0.05f, false);
		MainRenderer->CreateAnimation("Right_GraveStone", "GraveStone.bmp", 0, 59, 0.1f, true);

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
	PlayerInfoUI->UpdateData_PlayerInfoUI(&Hp, IsTurnPlayer);

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
		DirCheck();
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(PlayerState::JumpReady);
		return;
	}
}

void Player::ChangeWeapon()
{
	if (true == GameEngineInput::IsDown('2'))
	{
		ChangeState(PlayerState::BazookaOn);
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
		ChangeState(PlayerState::AirStrikeOn);
	}

	if (true == GameEngineInput::IsDown('9'))
	{
		ChangeState(PlayerState::GirderOn);
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