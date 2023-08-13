#include "UI_PlayerInfo.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "ContentsEnum.h"
#include "GameTurn.h"

UI_PlayerInfo* UI_PlayerInfo::PlayerInfoUI = nullptr;

UI_PlayerInfo::UI_PlayerInfo()
{
	PlayerInfoUI = this;
}

UI_PlayerInfo::~UI_PlayerInfo()
{
}

void UI_PlayerInfo::Start()
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\PlayerInfoUI\\");

#pragma region �÷��̾� �̸� ���ҽ� �ε�

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

#pragma region HP ���� ���ҽ� & ���� ���ҽ� �ε� 

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_PlayerHPBase.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_PlayerHPBase.bmp"));
	}

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

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_BottomFlagKOR.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_BottomFlagKOR.bmp"));
	}


#pragma endregion

#pragma region Arrow ���ҽ� �ε� & �ִϸ��̼� ����

	if (false == ResourcesManager::GetInst().IsLoadTexture("PlayerSelectArrowBlue.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("PlayerSelectArrowBlue.bmp"), 1, 30);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("PlayerSelectArrowGreen.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("PlayerSelectArrowGreen.bmp"), 1, 30);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("PlayerSelectArrowMint.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("PlayerSelectArrowMint.bmp"), 1, 30);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("PlayerSelectArrowPink.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("PlayerSelectArrowPink.bmp"), 1, 30);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("PlayerSelectArrowRed.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("PlayerSelectArrowRed.bmp"), 1, 30);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("PlayerSelectArrowYellow.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("PlayerSelectArrowYellow.bmp"), 1, 30);
	}

#pragma endregion

	//// ������ ����
	PlayerNameRenderer = CreateUIRenderer("UI_BottomNameTagB.bmp", RenderOrder::UI);
	PlayerNameRenderer->SetRenderScale({ 50, 17 });


	PlayerHpBaseRenderer = CreateUIRenderer("UI_PlayerHPBase.bmp", RenderOrder::UI);
	PlayerHpBaseRenderer->SetRenderScale({ 40, 17 });
	PlayerHpBaseRenderer->SetRenderPos({ 0, 20 });

	PlayerHpTextRenderer = CreateUIRenderer(RenderOrder::UI);
	PlayerHpTextRenderer->SetText("000", 16);
	PlayerHpTextRenderer->SetRenderPos({ -13, 12 });

	PlayerArrowRenderer = CreateUIRenderer(RenderOrder::UI);
	PlayerArrowRenderer->CreateAnimation("PlayerArrow_Blue", "PlayerSelectArrowBlue.bmp", 0, 29, 0.05f, true);
	PlayerArrowRenderer->SetRenderScale({ 50, 50 });
	PlayerArrowRenderer->ChangeAnimation("PlayerArrow_Blue");
	PlayerArrowRenderer->SetRenderPos({0, -30});
	PlayerArrowRenderer->Off();
}

void UI_PlayerInfo::Update(float _Delta)
{



}

//	void UpdateData_PlayerInfoUI(float4* _PlayerPos, int* _PlayerHp, bool _IsTurnPlayer);
void UI_PlayerInfo::UpdateData_PlayerInfoUI(int* _PlayerHp, bool _IsTurnPlayer)
{
	PlayerHp = _PlayerHp;
	CurPlayerHp = *_PlayerHp;

	//PlayerPos = _PlayerPos;
	//CurPlayerPos = *PlayerPos;


//	float4 CurUIPos = { CurPlayerPos.X - GetLevel()->GetMainCamera()->GetPos().X,  (CurPlayerPos.Y - GetLevel()->GetMainCamera()->GetPos().Y) - 70 };

	// ���� �÷��̾� HP ���� ���� �������� ��µǴ� �ؽ�Ʈ�� ��ġ�� �������ݴϴ�
	if (CurPlayerHp > 100)
	{
		PlayerHpTextRenderer->SetRenderPos({ -13, 12 });
	}
	else if (CurPlayerHp < 100 && CurPlayerHp > 10)
	{
		PlayerHpTextRenderer->SetRenderPos({ -10, 12 });
	}
	else if (CurPlayerHp < 10)
	{
		PlayerHpTextRenderer->SetRenderPos({ -5, 12 });
	}

	// ���� �÷��̾� HP ���� �ؽ�Ʈ�� ����մϴ�
	PlayerHpTextRenderer->SetText(std::to_string(CurPlayerHp), 16);


//	PlayerInfoUI->SetPos(CurUIPos);


	// ���� �÷��̾ �� �÷��̾��� ȭ��ǥ UI�� Ȱ��, �ƴ� ��� ��Ȱ���մϴ�.
	if (true == _IsTurnPlayer)
	{
		PlayerArrowRenderer->On();
	}
	else
	{
		PlayerArrowRenderer->Off();
	}
}