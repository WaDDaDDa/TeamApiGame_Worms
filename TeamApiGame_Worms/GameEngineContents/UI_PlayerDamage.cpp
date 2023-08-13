#include "UI_PlayerDamage.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"

UI_PlayerDamage::UI_PlayerDamage()
{

}

UI_PlayerDamage::~UI_PlayerDamage()
{

}

void UI_PlayerDamage::Start()
{
	// 리소스 로딩
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_PlayerHPBase.bmp"))
	{	
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\\PlayerInfoUI\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_PlayerHPBase.bmp"));
	}

	MainRenderer = CreateUIRenderer("UI_PlayerHPBase.bmp", RenderOrder::UI);
	MainRenderer->SetRenderScale({ 40, 20 });
	MainRenderer->SetRenderPos({ 0, 0 });

	DamageTextRenderer = CreateUIRenderer(RenderOrder::UI);
	DamageTextRenderer->SetText("000", 16);
	DamageTextRenderer->SetRenderPos({ -30, 0 });
}

void UI_PlayerDamage::Update(float _Delta)
{
	if (GetLiveTime() < 1.0f)
	{
		AddPos(float4::UP * 100.0f * _Delta);
	}

	if (GetLiveTime() > 1.5f)
	{
		Death();
	}
}

void UI_PlayerDamage::UpdateData_PlayerDamageUI(float4 _TargetPos, int _PlayerDamage)
{
	MainRenderer->SetRenderPos(_TargetPos);
	DamageTextRenderer->SetRenderPos({ _TargetPos.X - 10,  _TargetPos.Y - 10 });

	int Damage = static_cast<int>(_PlayerDamage);
	DamageTextRenderer->SetText(std::to_string(Damage));
}