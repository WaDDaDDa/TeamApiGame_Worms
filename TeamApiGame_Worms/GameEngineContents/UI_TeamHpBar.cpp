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
#pragma region ���ҽ� �ε�
#pragma region �÷��̾� �̸� ���ҽ� �ε�

	// ���ҽ� �ε�
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

#pragma region Hp�� & ���� ���ҽ� �ε�

	// HP��
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

	// ���� ���ҽ�
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomFlagKOR.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomFlagKOR.bmp"));
	}

#pragma endregion
#pragma endregion

#pragma region ������ �ʱ� ����
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

	// step2. �پ�� ü�¸�ŭ �������� Scalse.X���� �����մϴ�.
	if (trigger_UpdateHP) // �� ������ true�� ���, ü�¹��� Scale���� ���Դϴ�.
	{
		// step1. �پ�� ü���� ���մϴ�. ���� ���ݾ� ���Դϴ�.
		CurHpBarAmount -= 1 * _Delta * 100.0f;

		// step3. �� �ڵ忡�� ���� ���� ���� HP �������� �������� �����մϴ�.
		TeamHpRenderer->SetRenderScale({ CurHpBarAmount, 17 });
	}

	// step4. ����� ������ ������ ����ŭ �Ű��� X�� ��ġ�� �������ݴϴ�.
	TeamHpRenderer->SetRenderPos({ 10.0f + (CurHpBarAmount / 2), TeamHpRenderer->GetRenderPos().Y });

	// ���� HP ���� ���� �������� ���ĵ� HP Bar���� ������ ���缭 ��ġ�� �̵���ŵ�ϴ�.
	if (true == trigger_SortHp)
	{
		MoveSortedHpBars(_Delta);
	}


}


void UI_TeamHpBar::InitDecreaseHpBar(int _DamagedHp)
{
	TargetHpBarAmount = static_cast<float>(_DamagedHp);

	// ���� �������� �ݿ��� ü���� �������ݴϴ�.
	CurHpBarAmount -= TargetHpBarAmount;

	// HpBar�������� �پ��� �մϴ�.
	// ���� �������� ���� ������ HP�� 0���� �۰ų� ���� ��쿡�� HP�� �������� �ƿ� �������ϴ�.
	if (_DamagedHp > 0)
	{
		DecreaseHpBar();
	}

	/* **** 0�� �� ���¿��� ���� ������ ������ ü�¹ٰ� �ö󰬴� �������� �ϴ� ������ ���� ����.
	 **** ���� �ʿ信 ���� �Ʒ� �ڵ带 ����ϸ� 0�� �Ǵ� ���� �������� �ƿ� ���������� ������ ���� ������ ����
	 **** ��, ���ݾ� �������� �پ��� ȿ�� ���� �ٷ� �������� �����ٴ� ������ ���� => �� �� �� �׽�Ʈ�غ��� �̻� ������ �����*/
	else if (_DamagedHp <= 0)
	{
		TeamHpRenderer->Off();
	}

}

// ��ǥ : �پ�� ü�� ��ŭ HpBar�� �������� ���Դϴ�.
void UI_TeamHpBar::DecreaseHpBar()
{

	// step0. Hp�ٸ� ������ų �� �ִ� ��Ȳ���� ���� üũ�Ͽ� Ȱ��ȭ���ݴϴ�.
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