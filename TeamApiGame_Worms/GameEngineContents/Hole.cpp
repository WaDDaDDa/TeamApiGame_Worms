#include "Hole.h"
#include "Ground.h"
#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
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
		MsgBoxAssert("Hole�� �ؽ��İ� nullptr�Դϴ�");
	}

	if (Scale == float4::ZERO)
	{
		MsgBoxAssert("Hole�� Scale�� �������� �ʾҽ��ϴ�.")
	}

	GameEngineWindowTexture* GroundTexture = _GroundTexture->GetTexture();
	GameEngineWindowTexture* GroundPixelTexture = _GroundPixelTexture->GetTexture();

	float4 TexturePos = GetPos();
	float4 TextureScale =Texture->GetScale();
	
	 GroundTexture->TransCopy(Texture, TexturePos, {128.0f,128.0f}, float4::ZERO, TextureScale, RGB(255,255,255));
	GroundPixelTexture->TransCopy(PixelTexture, TexturePos, { 128.0f,128.0f }, float4::ZERO, TextureScale);



	Death();
}

//���� �߽ɿ��� ���� �Ÿ� ����
float Hole::GetDistanceFromHoleCenter(float4 _Pos)
{
	float4 Vector = GetPos() - _Pos;

	if (Scale.Size()<=Vector.Size())
	{
		return -1;
	}
	
	return Vector.Size();
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
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("PixelMagentaHole.Bmp"));


	}
	 

	Texture = ResourcesManager::GetInst().FindTexture("MagentaHole.Bmp");
	PixelTexture = ResourcesManager::GetInst().FindTexture("PixelMagentaHole.Bmp");


	{
		GameEngineCollision* Collision = CreateCollision(CollisionOrder::Boom);
		Collision->SetCollisionType(CollisionType::CirCle);
		Collision->SetCollisionScale(Scale);

	}

}

