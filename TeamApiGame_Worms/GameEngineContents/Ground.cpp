#include "Ground.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

Ground::Ground()
{
}

Ground::~Ground()
{
}

void Ground::Init(const std::string& _FileName, const std::string& _DebugFileName)
{
	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}


	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	float4 Scale = Texture->GetScale();
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Scale);
	DebugRenderer->SetTexture(_DebugFileName);
	DebugRenderer->SetRenderScale(Scale);
	SetPos({ Scale.hX(), Scale.hY() });


}

void Ground::SwitchRender()
{
}

void Ground::Start()
{
	Renderer = CreateRenderer(GetOrder());

	DebugRenderer = CreateRenderer(RenderOrder::BackGround);

	Renderer->On();
	DebugRenderer->Off();
}

void Ground::Update(float _Delta)
{
}

void Ground::Release()
{
}
