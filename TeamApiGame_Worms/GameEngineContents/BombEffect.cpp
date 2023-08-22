#include "BombEffect.h"
#include "Ground.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "PlayLevel.h"
#include "GameTurn.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEnginecollision.h>

BombEffect::BombEffect()
{

}

BombEffect::~BombEffect()
{

}

void BombEffect::Start()
{
	
}

void BombEffect::LevelStart()
{

}

void BombEffect::Update(float _Delta)
{
	
}

void BombEffect::SetBombRange(float4 _BombRange)
{
	BombRange = _BombRange;

	BombCollision = CreateCollision(CollisionOrder::Bomb);
	BombCollision->SetCollisionScale(BombRange);
	BombCollision->SetCollisionType(CollisionType::CirCle);
	BombCollision->SetCollisionPos({ 0, 0 });
}

void BombEffect::SetShotHitRange(float4 _ShotHitRange)
{
	BombRange = _ShotHitRange;

	BombCollision = CreateCollision(CollisionOrder::ShotHit);
	BombCollision->SetCollisionScale(BombRange);
	BombCollision->SetCollisionType(CollisionType::CirCle);
	BombCollision->SetCollisionPos({ 0, 0 });
}