#include "Weapon.h"
#include "Ground.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "PlayLevel.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

void Weapon::Start()
{
	Renderer = CreateRenderer(RenderOrder::Weapon);

	if(false == ResourcesManager::GetInst().IsLoadTexture("PistolBullet.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Worms\\Weapon\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("PistolBullet.bmp"));
	}

	Renderer->SetTexture("PistolBullet.bmp");

	SetDir(Player::DirPos);

	//GravityDir = float4::UP;
	GravityDir += Dir * 30.0f;
	SetGravityVector(GravityDir * 10.0f);

}

void Weapon::Update(float _Delta)
{
	Gravity(_Delta);

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (Color != RGB(255, 255, 255))
		{
			Renderer->Off();
			
			// PlayLevel에서 만 존재하는 것에만 사용할수 있는예제코드
			PlayLevel* CurPlayLevel=dynamic_cast<PlayLevel*>(GetLevel());
			CurPlayLevel->GetGround()->ContactGround(GetPos());
			
		}
	}
}

