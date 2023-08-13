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

#pragma region 플레이어 이름 리소스 로딩

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

#pragma region HP 관련 리소스 & 국기 리소스 로딩 

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

#pragma region Arrow 리소스 로딩 & 애니메이션 생성

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

	//// 렌더러 설정
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

	// 현재 플레이어 HP 값에 따라서 렌더러에 출력되는 텍스트의 위치를 조정해줍니다
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

	// 현재 플레이어 HP 값을 텍스트로 출력합니다
	PlayerHpTextRenderer->SetText(std::to_string(CurPlayerHp), 16);


//	PlayerInfoUI->SetPos(CurUIPos);


	// 현재 플레이어가 턴 플레이어라면 화살표 UI를 활성, 아닌 경우 비활성합니다.
	if (true == _IsTurnPlayer)
	{
		PlayerArrowRenderer->On();
	}
	else
	{
		PlayerArrowRenderer->Off();
	}
}