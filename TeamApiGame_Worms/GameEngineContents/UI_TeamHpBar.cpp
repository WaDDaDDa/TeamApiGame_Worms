#include "UI_TeamHpBar.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "GameStateManager.h"

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

#pragma region 렌더러 초기 세팅
	TeamFlagRenderer = CreateUIRenderer("UI_BottomFlagKOR.bmp", RenderOrder::UI);
	TeamFlagRenderer->SetRenderScale({ 20, 17 });

	TeamNameRenderer = CreateUIRenderer("UI_BottomNameTagB.bmp", RenderOrder::UI);
	TeamNameRenderer->SetRenderScale({ 38, 17 });
	TeamNameRenderer->SetRenderPos({ -30, 0 });

	TeamHpRenderer = CreateUIRenderer("UI_BottomHPbarB.bmp", RenderOrder::UI);

	float ScaleX = static_cast<float>(GameStateManager::GameState->GetWormMaxHp());
	TeamHpRenderer->SetRenderScale({ ScaleX, 17 });
	TeamHpRenderer->SetRenderPos({ 61, 0 });

#pragma endregion

}

void UI_TeamHpBar::Update(float _Delta)
{

	if (CurHpBarAmount <= TargetHpBarAmount)
	{
		CurHpBarAmount = TargetHpBarAmount;
	}

	// step2. 줄어든 체력만큼 렌더러의 Scalse.X값을 변동합니다.
	if (trigger_UpdateHP) // 이 변수가 true일 경우, 체력바의 Scale값을 줄입니다.
	{
		// step1. 줄어든 체력을 구합니다. 값을 조금씩 줄입니다.
		CurHpBarAmount -= 1 * _Delta * 100.0f;

		// step3. 위 코드에서 줄인 값에 맞춰 HP 렌더러의 스케일을 변경합니다.
		TeamHpRenderer->SetRenderScale({ CurHpBarAmount, 17 });
	}

	// step4. 변경된 렌더러 스케일 값만큼 옮겨진 X값 위치를 변경해줍니다.
	TeamHpRenderer->SetRenderPos({ 10.0f + (CurHpBarAmount / 2), TeamHpRenderer->GetRenderPos().Y });

	// 현재 HP 값에 따라 내림차순 정렬된 HP Bar들을 순서에 맞춰서 위치를 이동시킵니다.
	if (true == trigger_SortHp)
	{
		MoveSortedHpBars(_Delta);
	}


}


void UI_TeamHpBar::InitDecreaseHpBar(int _DamagedHp)
{
	TargetHpBarAmount = static_cast<float>(_DamagedHp);

	// 받은 데미지가 반영된 체력을 저장해줍니다.
	CurHpBarAmount -= TargetHpBarAmount;

	// HpBar렌더러를 줄어들게 합니다.
	// 만약 데미지를 받은 상태의 HP가 0보다 작거나 같은 경우에는 HP바 렌더러를 아예 꺼버립니다.
	if (_DamagedHp > 0)
	{
		DecreaseHpBar();
	}

	/* **** 0이 된 상태에서 연속 공격을 받으면 체력바가 올라갔다 내려갔다 하는 현상이 가끔 있음.
	 **** 따라서 필요에 따라 아래 코드를 사용하면 0이 되는 순간 렌더러가 아예 꺼져버리기 때문에 눈에 보이진 않음
	 **** 단, 조금씩 렌더러가 줄어드는 효과 없이 바로 렌더러가 꺼진다는 문제가 있음 => 몇 번 더 테스트해보고 이상 없으면 지우기*/
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

}

void UI_TeamHpBar::InitMoveSortedHpbars(float4 _StartPos, float4 _DestPos, float _MoveSpeed)
{
	StartMoveHpBarPos = _StartPos;
	DestMoveHpBarPos = _DestPos;
	MoveSpeed = _MoveSpeed;

	MoveLerpDeltaTime = 0.0f;
	
	trigger_SortHp = true;
}

void UI_TeamHpBar::MoveSortedHpBars(float _Delta)
{
	MoveDeltaTime = _Delta;
	MoveLerpDeltaTime += MoveDeltaTime;

	CurHpBarPos = GetPos();

	float4 NextHpBarPos = float4::LerpClimp(CurHpBarPos, DestMoveHpBarPos, MoveLerpDeltaTime);
	SetPos(NextHpBarPos);

	if (CurHpBarPos.X > DestMoveHpBarPos.X - 1.0f && CurHpBarPos.X < DestMoveHpBarPos.X + 1.0f &&
		CurHpBarPos.Y > DestMoveHpBarPos.Y - 1.0f && CurHpBarPos.Y < DestMoveHpBarPos.Y + 1.0f)
	{
		SetPos(DestMoveHpBarPos);

		trigger_SortHp = false;
	}


}