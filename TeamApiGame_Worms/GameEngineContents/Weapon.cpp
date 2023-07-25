#include "Weapon.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
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

	GravityDir = float4::UP;
	GravityDir += Dir * 0.5f;
	SetGravityVector(GravityDir * 200.0f);

}

void Weapon::Update(float _Delta)
{
	Gravity(_Delta);

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (Color != RGB(255, 255, 255))
		{
			Renderer->Off();
		}
	}
}

