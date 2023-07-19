#include "MouseObject.h"
#pragma region Headers

#include "ContentsEnum.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include "Bullet.h"
#include "Monster.h"
#include "PlayUIManager.h"
#include <GameEnginePlatform/GameEngineInput.h>

#pragma endregion


MouseObject::MouseObject() 
{
}

MouseObject::~MouseObject() 
{
}

void MouseObject::Start() 
{
	GameEngineRenderer* CursorRender = CreateRenderer("HPBar.bmp", RenderOrder::Play);
	// 난 UI를 이걸 안하고 있다.
	CursorRender->UICameraSetting();

	CursorRender->SetRenderScale({ 40, 40 });
	CursorRender->SetTexture("HPBar.bmp");

	IconRender = CreateRenderer("HPBar.bmp", RenderOrder::Play);
	IconRender->SetRenderPos({ 100, 100 });
	IconRender->SetRenderScale({ 60, 60 });
	IconRender->SetTexture("HPBar.bmp");

	IconRender->Off();

	// CollisionOrder

	// 이녀석은 UI
	// GameEngineCollision* Col = CreateCollision();
}

void MouseObject::Update(float _Delta)
{
 	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
	SetPos(MousePos);

	if (/*아이콘이랑 제대로 충돌 상태고*/ /*&& */GameEngineInput::IsPress(VK_LBUTTON)
		&& false == IconRender->IsUpdate())
	{
		// InvenSelectIconRender = 인벤토리의 아이콘 랜더러는 off
		IconRender->On();
	}

	// 사실 이걸 누가하건
	// 인벤토리에서 하건
	// 마우스 오브젝트가 인벤토리를 알아내서 하건
	// 아무런 의미없어.
	// 누가하든 되면 된다.
	// 성향이야.
	// 최악 => 이딴걸로 1시간 이상고민하는놈.

	if (/*아이콘이랑 제대로 충돌 상태고*/ /*&& */GameEngineInput::IsUp(VK_LBUTTON)
		&& true == IconRender->IsUpdate())
	{
		// InvenSelectIconRender->On();
		// NewSelectICon->SetTexture(InvenSelectIconRender->GetTexture());
		// InvenSelectIconRender->SetTexture(nullptr);
		// 인벤토리의 아이콘 랜더러는 off
		IconRender->Off();
	}

	// 다른 인벤토리랑 이미 충돌하고 있다면
}

void MouseObject::Render(float _Delta) 
{

}