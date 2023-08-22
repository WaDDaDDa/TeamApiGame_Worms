#include "UI_Box_Teams.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "GameStateManager.h"

#include "UI_Box_Barracks.h"

#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineInput.h>

UI_Box_Teams* UI_Box_Teams::BoxTeamUI = nullptr;
UI_Box_Teams::UI_Box_Teams()
{
	BoxTeamUI = this;
}

UI_Box_Teams::~UI_Box_Teams()
{
}

void UI_Box_Teams::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Teams.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\UI\\Lobby\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Teams.bmp"));


		// 팀 버튼 세팅용 리소스
		if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Teams_1Up.bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Teams_1Up.bmp"));
		}

		if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Teams_2Up.bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Teams_2Up.bmp"));
		}

		if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Teams_3Up.bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Teams_3Up.bmp"));
		}

		if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Teams_4Up.bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Teams_4Up.bmp"));
		}

		if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Teams_5Up.bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Teams_5Up.bmp"));
		}

		if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Teams_6Up.bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Teams_6Up.bmp"));
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::UI);

	MainRenderer->SetRenderScale({ 530, 250 });

	MainRenderer->SetTexture("UI_Teams.bmp");

//	GameStateManager::GameState->SetTeamNumber(6);



	MainCollision = CreateCollision(CollisionOrder::UI);
	MainCollision->SetCollisionType(CollisionType::Rect);
	MainCollision->SetCollisionScale({ 350, 210 });
	MainCollision->SetCollisionPos({ -80, 8 });

	float4 StartPos = { -190, -70 };

	// 플레이어 최대 인원만큼 렌더러를 생성합니다.
	for (int PlayerIndex = 0; PlayerIndex < 6; PlayerIndex++)
	{
		GameEngineRenderer* TeamRenderer = CreateRenderer(RenderOrder::UI);
		TeamRenderer->SetRenderScale({ 80, 24 });
		float4 initPos = { StartPos.X, StartPos.Y + 30 * PlayerIndex };

		switch (PlayerIndex)
		{
		case 0:
			TeamRenderer->SetTexture("UI_Teams_1Up.bmp");
			TeamRenderer->SetRenderPos(initPos);
			AllSelectedTeamRenderers.push_back(TeamRenderer);
			AllSelectedTeamRenderPos.push_back(initPos);
			break;

		case 1:
			TeamRenderer->SetTexture("UI_Teams_2Up.bmp");
			TeamRenderer->SetRenderPos(initPos);
			AllSelectedTeamRenderers.push_back(TeamRenderer);
			AllSelectedTeamRenderPos.push_back(initPos);
			break;

		case 2:
			TeamRenderer->SetTexture("UI_Teams_3Up.bmp");
			TeamRenderer->SetRenderPos(initPos);
			AllSelectedTeamRenderers.push_back(TeamRenderer);
			AllSelectedTeamRenderPos.push_back(initPos);
			break;

		case 3:
			TeamRenderer->SetTexture("UI_Teams_4Up.bmp");
			TeamRenderer->SetRenderPos(initPos);
			AllSelectedTeamRenderers.push_back(TeamRenderer);
			AllSelectedTeamRenderPos.push_back(initPos);
			break;

		case 4:
			TeamRenderer->SetTexture("UI_Teams_5Up.bmp");
			TeamRenderer->SetRenderPos(initPos);
			AllSelectedTeamRenderers.push_back(TeamRenderer);
			AllSelectedTeamRenderPos.push_back(initPos);
			break;

		case 5:
			TeamRenderer->SetTexture("UI_Teams_6Up.bmp");
			TeamRenderer->SetRenderPos(initPos);
			AllSelectedTeamRenderers.push_back(TeamRenderer);
			AllSelectedTeamRenderPos.push_back(initPos);
			break;

		default:
			break;
		}

		AllSelectedTeamRenderers[PlayerIndex]->Off();
	}

	ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);

}

void UI_Box_Teams::Update(float _Delta)
{

	MainRenderer->SetText(std::to_string(m_SelectIndex));
	StateUpdate();
	CheckButtonCollision();
}

void UI_Box_Teams::RemovePlayerTeam()
{
//	m_SelectIndex = GameStateManager::GameState->GetTeamNumber();

	if (m_SelectIndex > 0)
	{
		--m_SelectIndex;
	}

	else
	{
		m_SelectIndex = 0;
	}
	 

//	UI_Box_Barracks::BoxBarracksUI->m_SelectIndex = 6 - m_SelectIndex;

//	GameStateManager::GameState->SetTeamNumber(m_SelectIndex);

	ChangePlayerTeamLayout(m_SelectIndex);

	//UI_Box_Barracks::BoxBarracksUI->ChangePlayerTeamLayout(m_SelectIndex);

	ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
}

void UI_Box_Teams::ChangePlayerTeamLayout(int _CurPlayerSelectIndex)
{

	m_SelectIndex = GameStateManager::GameState->GetTeamNumber();

	for (size_t i = 0; i < _CurPlayerSelectIndex; i++)
	{
		AllSelectedTeamRenderers[i]->On();

		for (size_t j = AllSelectedTeamRenderers.size(); j < _CurPlayerSelectIndex; j++)
		{
			AllSelectedTeamRenderers[j]->SetRenderPos(AllSelectedTeamRenderPos[j - i - 1]);
		}
	}
}

void UI_Box_Teams::StateUpdate()
{
	m_SelectIndex = GameStateManager::GameState->GetTeamNumber();

	switch (ButtonState)
	{
	case BUTTON_STATE::BUTTON_STATE_HOVERED:
		CheckButtonClick();
		break;

	case BUTTON_STATE::BUTTON_STATE_UNHOVERED:
		break;

	case BUTTON_STATE::BUTTON_STATE_CLICKED:
		RemovePlayerTeam();
		break;

	default:
		break;
	}
}

void UI_Box_Teams::CheckButtonCollision()
{
	if (nullptr != MainCollision)
	{

		MainCollision->CollisionCallBack
		(
			CollisionOrder::Mouse
			, CollisionType::Rect // _this의 충돌체 타입
			, CollisionType::CirCle // _Other의 충돌체 타입
			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
			{
				GameEngineActor* thisActor = _this->GetActor();
				UI_Box_Teams* ButtonPtr = dynamic_cast<UI_Box_Teams*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
			}

			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
				{

				}

				, [](GameEngineCollision* _this, GameEngineCollision* _Other)
					{
						GameEngineActor* thisActor = _this->GetActor();
						UI_Box_Teams* ButtonPtr = dynamic_cast<UI_Box_Teams*>(thisActor);

						ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);
					}
				);

	}
}

void UI_Box_Teams::CheckButtonClick()
{
	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChangeState(BUTTON_STATE::BUTTON_STATE_CLICKED);
	}

	if (true == GameEngineInput::IsFree(VK_LBUTTON) && true == GameEngineInput::IsFree(VK_RBUTTON))
	{
		ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
	}
}

void UI_Box_Teams::ChangeState(BUTTON_STATE _ButtonState)
{
	ButtonState = _ButtonState;
}
