#include "BackLand.h"
#include "ContentsDefine.h"
#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include<GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineWindow.h>

BackLand::BackLand()
{
}

BackLand::~BackLand()
{
}

void BackLand::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Back.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Back.Bmp"));


	}

	GameEngineRenderer* Renderer1 = CreateRenderer(RenderOrder::BackLand);
	GameEngineRenderer* Renderer2 = CreateRenderer(RenderOrder::BackLand);
	GameEngineRenderer* Renderer3 = CreateRenderer(RenderOrder::BackLand);
	GameEngineRenderer* Renderer4 = CreateRenderer(RenderOrder::BackLand);

	Renderer1->SetTexture("Back.Bmp");
	Renderer2->SetTexture("Back.Bmp");
	Renderer3->SetTexture("Back.Bmp");
	Renderer4->SetTexture("Back.Bmp");

	Renderer1->SetRenderPos({ -960.0f,0.0f });
	Renderer2->SetRenderPos({ -320.0f,0.0f });
	Renderer3->SetRenderPos({ 320.0f,0.0f });
	Renderer4->SetRenderPos({ 960.0f,0.0f });

	//BasicPos={ PLAY_GROUND_SCALE.hX(),1700.0f};
	

}

void BackLand::Update(float _Delta)
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos() + GameEngineWindow::MainWindow.GetScale().Half();

	float4 ChangedPos = float4{ PLAY_GROUND_SCALE.hX() + ((CameraPos.X - 1500.0f) / 2),1700.0f};
	
	
	SetPos(ChangedPos);
	

}
