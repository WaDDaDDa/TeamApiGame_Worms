#include "Ground.h"
#include "Hole.h"
#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>

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

	SetOrder(RenderOrder::Ground);
}

void Ground::SwitchRender()
{

	SwitchRenderValue = !SwitchRenderValue;

	if (SwitchRenderValue)
	{
		Renderer->On();
		DebugRenderer->Off();
	}
	else {
		Renderer->Off();
		DebugRenderer->On();
	}
}

void Ground::ContactGround(float4 _Pos)
{
	Hole* NewHole = GetLevel()->CreateActor<Hole>();
	NewHole->SetPos(_Pos);
	NewHole->AddHoleAtGround(Renderer, DebugRenderer);
	
	
}

GameEngineWindowTexture* Ground::GetGroundTexture()
{
	return Renderer->GetTexture();
}


void Ground::Start()
{
	Renderer = CreateRenderer(RenderOrder::Ground);

	DebugRenderer = CreateRenderer(RenderOrder::Ground);

	Renderer->On();
	DebugRenderer->Off();
}

void Ground::Update(float _Delta)
{
}

void Ground::Release()
{
}
