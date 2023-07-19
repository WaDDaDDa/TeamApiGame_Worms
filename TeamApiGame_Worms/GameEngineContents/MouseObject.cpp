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
	// �� UI�� �̰� ���ϰ� �ִ�.
	CursorRender->UICameraSetting();

	CursorRender->SetRenderScale({ 40, 40 });
	CursorRender->SetTexture("HPBar.bmp");

	IconRender = CreateRenderer("HPBar.bmp", RenderOrder::Play);
	IconRender->SetRenderPos({ 100, 100 });
	IconRender->SetRenderScale({ 60, 60 });
	IconRender->SetTexture("HPBar.bmp");

	IconRender->Off();

	// CollisionOrder

	// �̳༮�� UI
	// GameEngineCollision* Col = CreateCollision();
}

void MouseObject::Update(float _Delta)
{
 	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
	SetPos(MousePos);

	if (/*�������̶� ����� �浹 ���°�*/ /*&& */GameEngineInput::IsPress(VK_LBUTTON)
		&& false == IconRender->IsUpdate())
	{
		// InvenSelectIconRender = �κ��丮�� ������ �������� off
		IconRender->On();
	}

	// ��� �̰� �����ϰ�
	// �κ��丮���� �ϰ�
	// ���콺 ������Ʈ�� �κ��丮�� �˾Ƴ��� �ϰ�
	// �ƹ��� �ǹ̾���.
	// �����ϵ� �Ǹ� �ȴ�.
	// �����̾�.
	// �־� => �̵��ɷ� 1�ð� �̻����ϴ³�.

	if (/*�������̶� ����� �浹 ���°�*/ /*&& */GameEngineInput::IsUp(VK_LBUTTON)
		&& true == IconRender->IsUpdate())
	{
		// InvenSelectIconRender->On();
		// NewSelectICon->SetTexture(InvenSelectIconRender->GetTexture());
		// InvenSelectIconRender->SetTexture(nullptr);
		// �κ��丮�� ������ �������� off
		IconRender->Off();
	}

	// �ٸ� �κ��丮�� �̹� �浹�ϰ� �ִٸ�
}

void MouseObject::Render(float _Delta) 
{

}