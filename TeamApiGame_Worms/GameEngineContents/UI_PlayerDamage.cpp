#include "UI_PlayerDamage.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include "ContentsDefine.h"
#include <GameEnginePlatform/GameEngineWindow.h>

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
		FilePath.MoveChild("ContentsResources\\UI\\PlayerInfoUI\\");

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
	if (GetLiveTime() < 0.5f)
	{
		AddPos(float4::UP * 100.0f * _Delta);
	}

	if (GetLiveTime() > 0.5f)
	{
		Death();
	}
}

void UI_PlayerDamage::UpdateData_PlayerDamageUI(float4 _TargetPos, int _PlayerDamage, int _PlayerIndex)
{
	HDC hdc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	MainRenderer->SetRenderPos(_TargetPos);

	if (_PlayerDamage > 10)
	{
		DamageTextRenderer->SetRenderPos({ _TargetPos.X - 10,  _TargetPos.Y - 10 });
	}
	else if (_PlayerDamage < 10)
	{
		DamageTextRenderer->SetRenderPos({ _TargetPos.X - 5,  _TargetPos.Y - 10 });
	}

	int Damage = static_cast<int>(_PlayerDamage);

	switch (_PlayerIndex)
	{
	case 0:
		DamageTextRenderer->SetText(std::to_string(Damage), 20, PLAYER_COLOR_RED);
		break;

	case 1:
		DamageTextRenderer->SetText(std::to_string(Damage), 20, PLAYER_COLOR_BLUE);
		break;

	case 2:
		DamageTextRenderer->SetText(std::to_string(Damage), 20, PLAYER_COLOR_GREEN);
		break;

	case 3:
		DamageTextRenderer->SetText(std::to_string(Damage), 20, PLAYER_COLOR_YELLOW);
		break;

	case 4:
		DamageTextRenderer->SetText(std::to_string(Damage), 20, PLAYER_COLOR_PINK);
		break;

	case 5:
		DamageTextRenderer->SetText(std::to_string(Damage), 20, PLAYER_COLOR_CYAN);
		break;

	default:
		break;
	}


}