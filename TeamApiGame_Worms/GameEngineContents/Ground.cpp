#include "Ground.h"
#include "Hole.h"
#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>

#define STAGE_SCALE float4{4000.0f,3000.0f}

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
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" );


		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_DebugFileName));

		//GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}


	GameEngineWindowTexture* NewTexture = ResourcesManager::GetInst().FindTexture(_FileName);
	GameEngineWindowTexture* NewDebugTexture = ResourcesManager::GetInst().FindTexture(_DebugFileName);

	GameEngineWindowTexture* Texture = Renderer->GetTexture();
	GameEngineWindowTexture* DebugTexture = DebugRenderer->GetTexture();



	//GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	float4 Scale = STAGE_SCALE;
	//float4 Scale = Texture->GetScale();
	/*Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Scale);
	DebugRenderer->SetTexture(_DebugFileName);
	DebugRenderer->SetRenderScale(Scale);*/


	
	Texture->TransCopy(NewTexture, Texture->GetScale().Half(), NewTexture->GetScale(), float4::ZERO, NewTexture->GetScale());
	//Renderer->SetRenderScale(STAGE_SCALE);


	DebugTexture->TransCopy(NewDebugTexture, DebugTexture->GetScale().Half(), NewDebugTexture->GetScale(), float4::ZERO, NewDebugTexture->GetScale(),NULL);

	//DebugRenderer->SetRenderScale(STAGE_SCALE);




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

void Ground::ContactGround(float4 _Pos,float4 _HoleScale)
{
	Hole* NewHole = GetLevel()->CreateActor<Hole>();
	NewHole->SetPos(_Pos);
	NewHole->SetScale(_HoleScale);
	NewHole->AddHoleAtGround(Renderer, DebugRenderer);
}

GameEngineWindowTexture* Ground::GetGroundTexture()
{
	return Renderer->GetTexture();
}

GameEngineWindowTexture* Ground::GetPixelGroundTexture()
{
	return DebugRenderer->GetTexture();
}


void Ground::Start()
{

	{
	Renderer = CreateRenderer(RenderOrder::Ground);
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().TextureCreate("StageTexture",STAGE_SCALE);
	Texture->FillTexture(RGB(255, 0, 255));
	Renderer->SetTexture("StageTexture");

	}

	{
	DebugRenderer = CreateRenderer(RenderOrder::Ground);
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().TextureCreate("StagePixelTexture", STAGE_SCALE);
	Texture->FillTexture(RGB(255,255,255));
	DebugRenderer->SetTexture("StagePixelTexture");
	}


	Renderer->On();
	DebugRenderer->Off();
}

void Ground::Update(float _Delta)
{
}

void Ground::Release()
{
}
