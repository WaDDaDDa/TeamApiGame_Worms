#include "MouseObject.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include <GameEngineCore/GameEngineCollision.h>

float4 MouseObject::PlayMousePos = float4::ZERO;

MouseObject::MouseObject()
{
}

MouseObject::~MouseObject()
{
}

void MouseObject::Start()
{
	CrossHairRenderer = CreateRenderer(RenderOrder::Mouse);

	if(false == ResourcesManager::GetInst().IsLoadTexture("CrossHair.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Worms\\Weapon\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("CrossHair.bmp"));
	}

	CrossHairRenderer->SetTexture("CrossHair.bmp");
	CrossHairRenderer->SetRenderScaleToTexture();

	Collision = CreateCollision(CollisionOrder::Mouse);
	Collision->SetCollisionScale({ 100, 100 });
	Collision->SetCollisionType(CollisionType::CirCle);

}
void MouseObject::Update(float _Delta)
{
	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	PlayMousePos = CameraPos + MousePos;
	SetPos(PlayMousePos);
}
void MouseObject::Render(float _Delta)
{

}
