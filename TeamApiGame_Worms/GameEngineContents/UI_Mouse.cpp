#include "UI_Mouse.h"
#pragma region Headers
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#pragma endregion

#define MOUSE_WITDH	32
#define MOUSE_HEIGHT 32

UI_Mouse::UI_Mouse()
{
}

UI_Mouse::~UI_Mouse()
{
}

void UI_Mouse::Start()
{
	// ���콺 ���� ���� ������ �����ϴ� �⺻ Ŀ���� OFF ���ݴϴ�.
	GameEngineWindow::MainWindow.CursorOff();

	// ���콺 ���ҽ� �ε�
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("UI_MOUSE.bmp");

	if (false == IsResource)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_MOUSE.bmp"));
	}

	// ������ ����
	MainRenderer = CreateUIRenderer("UI_MOUSE.bmp", RenderOrder::UI);
	MainRenderer->SetRenderScale({ MOUSE_WITDH, MOUSE_HEIGHT });

	// �浹ü ����
	MainCollision = CreateCollision(CollisionOrder::UI);
	MainCollision->SetCollisionScale({ MOUSE_WITDH, MOUSE_HEIGHT });
	MainCollision->SetCollisionType(CollisionType::CirCle);

}

void UI_Mouse::Update(float _Delta)
{
	float4 MosuePos = GameEngineWindow::MainWindow.GetMousePos();
	MainRenderer->SetRenderPos(MosuePos);
}

void UI_Mouse::Render(float _Delta)
{
}
