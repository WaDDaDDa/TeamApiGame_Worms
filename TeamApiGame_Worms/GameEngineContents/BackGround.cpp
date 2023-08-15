#include "BackGround.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include<GameEnginePlatform/GameEngineWindowTexture.h>

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
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" + _FileName);

		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	
	
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(_Scale);
	
	SetPos({ _Scale.hX(), _Scale.hY() });
	
}


void BackGround::Init(const std::string& _FileName)
{
	float4 Scale = GameEngineWindow::MainWindow.GetScale();

	Init(_FileName, Scale);

}

void BackGround::VerticalPatternInit(const std::string& _FileName)
{
	float4 Scale = GameEngineWindow::MainWindow.GetScale();
	
	return VerticalPatternInit(_FileName, Scale);

	/*if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" + _FileName);

		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);


	if (false == ResourcesManager::GetInst().IsLoadTexture("VerticalPattern" + _FileName))
	{
		GameEngineWindowTexture* NewTexture = ResourcesManager::GetInst().TextureCreate("VerticalPattern" +_FileName,Scale);

	}

	GameEngineWindowTexture* NewTexture = ResourcesManager::GetInst().FindTexture("VerticalPattern" + _FileName);

	

	float4 DrawScale={Texture->GetScale().X, Scale.Y};
	int Cutcount = static_cast<int>(Scale.X / Texture->GetScale().X);

	for (int i = 0; i <= Cutcount; i++)
	{
		float4 DrawPos = { Texture->GetScale().X*i, Scale.hY()};
		NewTexture->TransCopy(Texture, DrawPos, DrawScale, float4::ZERO, Texture->GetScale(),NULL);
	}

		Renderer->SetTexture("VerticalPattern" + _FileName);
		Renderer->SetRenderScale(Scale);

		SetPos({ Scale.hX(), Scale.hY() });*/
}

void BackGround::VerticalPatternInit(const std::string& _FileName, const float4 _Scale)
{
	float4 Scale = _Scale;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" + _FileName);

		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);


	if (false == ResourcesManager::GetInst().IsLoadTexture("VerticalPattern" + _FileName))
	{
		GameEngineWindowTexture* NewTexture = ResourcesManager::GetInst().TextureCreate("VerticalPattern" + _FileName, Scale);

	}

	GameEngineWindowTexture* NewTexture = ResourcesManager::GetInst().FindTexture("VerticalPattern" + _FileName);



	float4 DrawScale = { Texture->GetScale().X, Scale.Y };
	int Cutcount = static_cast<int>(Scale.X / Texture->GetScale().X);

	for (int i = 0; i <= Cutcount; i++)
	{
		float4 DrawPos = { Texture->GetScale().X * i, Scale.hY() };
		NewTexture->TransCopy(Texture, DrawPos, DrawScale, float4::ZERO, Texture->GetScale(), NULL);
	}

	Renderer->SetTexture("VerticalPattern" + _FileName);
	Renderer->SetRenderScale(Scale);

	SetPos({ Scale.hX(), Scale.hY() });


}
