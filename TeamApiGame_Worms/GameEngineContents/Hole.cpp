#include "Hole.h"
#include "Ground.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

Hole::Hole()
{
}

Hole::~Hole()
{
}

void Hole::AddHoleAtGround(GameEngineRenderer* _GroundTexture, GameEngineRenderer* _GroundPixelTexture)
{
	if (nullptr == Texture)
	{
		MsgBoxAssert("Hole의 텍스쳐가 nullptr입니다");
	}

	GameEngineWindowTexture* GroundTexture = _GroundTexture->GetTexture();
	GameEngineWindowTexture* GroundPixelTexture = _GroundPixelTexture->GetTexture();

	float4 TexturePos = GetPos();
	float4 TextureScale =Texture->GetScale();
	
	 GroundTexture->TransCopy(Texture, TexturePos, TextureScale, float4::ZERO, TextureScale, RGB(255, 255, 255));
	GroundPixelTexture->TransCopy(Texture, TexturePos, TextureScale, float4::ZERO, TextureScale, RGB(255, 255, 255));



	Off();
}

void Hole::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("MagentaHole.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MagentaHole.Bmp"));


	}

	Texture = ResourcesManager::GetInst().FindTexture("MagentaHole.Bmp");

}

