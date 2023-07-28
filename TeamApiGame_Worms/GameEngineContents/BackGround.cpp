#include "BackGround.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}



void BackGround::Start()
{
	Renderer = CreateRenderer(RenderOrder::BackGround);
	

}

void BackGround::Update(float _Delta)
{
}

void BackGround::Release()
{
}

void BackGround::Init(const std::string& _FileName,const float4 _Scale)
{
	

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(_Scale);
	
	SetPos({ _Scale.hX(), _Scale.hY() });
	
}

void BackGround::Init(const std::string& _FileName)
{
	float4 Scale = GameEngineWindow::MainWindow.GetScale();

	Init(_FileName, Scale);

}

