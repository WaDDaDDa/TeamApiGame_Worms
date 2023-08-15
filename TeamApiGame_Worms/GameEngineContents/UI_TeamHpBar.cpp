#include "UI_TeamHpBar.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineTime.h>

UI_TeamHpBar::UI_TeamHpBar()
{
}

UI_TeamHpBar::~UI_TeamHpBar()
{
}

void UI_TeamHpBar::Start()
{
#pragma region 리소스 로딩
#pragma region 플레이어 이름 리소스 로딩

	// 리소스 로딩
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\PlayerInfoUI\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomNameTagR.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomNameTagR.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomNameTagB.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomNameTagB.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomNameTagG.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomNameTagG.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomNameTagY.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomNameTagY.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomNameTagP.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomNameTagP.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomNameTagS.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomNameTagS.bmp"));
	}

#pragma endregion

#pragma region Hp바 & 국기 리소스 로딩

	// HP바
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomHPbarB.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomHPbarB.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomHPbarG.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomHPbarG.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomHPbarP.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomHPbarP.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomHPbarR.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomHPbarR.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomHPbarS.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomHPbarS.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomHPbarY.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomHPbarY.bmp"));
	}

	// 국기 리소스
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomFlagKOR.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomFlagKOR.bmp"));
	}

#pragma endregion
#pragma endregion

	TeamFlagRenderer = CreateUIRenderer("UI_BottomFlagKOR.bmp", RenderOrder::UI);
	TeamFlagRenderer->SetRenderScale({ 20, 17 });

	TeamNameRenderer = CreateUIRenderer("UI_BottomNameTagB.bmp", RenderOrder::UI);
	TeamNameRenderer->SetRenderScale({ 38, 17 });
	TeamNameRenderer->SetRenderPos({ -30, 0 });

	TeamHpRenderer = CreateUIRenderer("UI_BottomHPbarB.bmp", RenderOrder::UI);
	TeamHpRenderer->SetRenderScale({ 100, 17 });
	TeamHpRenderer->SetRenderPos({ 61, 0 });
}

void UI_TeamHpBar::Update(float _Delta)
{

	if (CurPlayerHp <= TargetPlayerHp)
	{
		CurPlayerHp = TargetPlayerHp;
	}

	// step1. 줄어든 체력을 구합니다.
	float Ratio = CurPlayerHp / MaxPlayerHp; // 피격 후 변동 값 (=피격 후 체력의 비율) => Scale x값은 Ratio값까지 줄어들게 됩니다.

	// step2. 줄어든 체력만큼 렌더러의 Scalse.X값을 변동합니다.
	if (trigger_UpdateHP) // 이 변수가 true일 경우, 체력바의 Scale값을 줄입니다.
	{
		if (CurPlayerHp <= Ratio) // Scale값이 목표치만큼 줄어들었다면
		{
			trigger_UpdateHP = false; // 더이상 값이 줄어들지 않도록 비활성화합니다.
		}

		else  // 만약 아직 목표치에 도달하지 못했을 경우(Ratio값까지 값이 줄어 들지 않은 상황)
		{
			CurPlayerHp -= 1 * GameEngineTime::MainTimer.GetDeltaTime(); // 값을 조금씩 줄입니다.

			if (CurPlayerHp < 0.0f) // 줄어드는 값이 음수가 되는 것을 막기 위해 -가 되는 순간 값을 0으로 고정시켜줍니다.
			{
				TeamHpRenderer->SetRenderScale({ 0, 17 });
			}

		}

		TeamHpRenderer->SetRenderScale({ CurPlayerHp, 17 });  // 위 코드에서 줄인 값에 맞춰 HP 렌더러의 Scale값을 줄입니다.

		float PivotX = (HpBarWidth - HpBarWidth * Ratio) / 2;

		TeamHpRenderer->SetRenderPos({ TeamHpRenderer->GetRenderPos().X - PivotX, TeamHpRenderer->GetRenderPos().Y });
	
		trigger_UpdateHP = false;
	}

}


void UI_TeamHpBar::InitDecreaseHpBar(int _DamagedHp)
{
	TargetPlayerHp = static_cast<float>(_DamagedHp);

	// 받은 데미지가 반영된 체력을 저장해줍니다.
	CurPlayerHp -= TargetPlayerHp;

	// HpBar렌더러를 줄어들게 합니다.
	// 만약 데미지를 받은 상태의 HP가 0보다 작거나 같은 경우에는 HP바 렌더러를 아예 꺼버립니다.
	if (_DamagedHp > 0)
	{
		DecreaseHpBar();
	}
	else if (_DamagedHp <= 0)
	{
		TeamHpRenderer->Off();
	}

}

// 목표 : 줄어든 체력 만큼 HpBar의 렌더러를 줄입니다.
void UI_TeamHpBar::DecreaseHpBar()
{

	// step0. Hp바를 변동시킬 수 있는 상황인지 먼저 체크하여 활성화해줍니다.
	trigger_UpdateHP = true;

	// Scale.X의 기본값이 될 값을 설정해줍니다. (추후에 입력받은 값으로 바뀌도록 변경할 예정)
	HpBarWidth = 100.0f;

}