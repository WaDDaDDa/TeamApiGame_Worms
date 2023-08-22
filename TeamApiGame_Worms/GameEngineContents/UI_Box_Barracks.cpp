#include "UI_Box_Barracks.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "GameStateManager.h"

#include "UI_Box_Teams.h"

#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineInput.h>

UI_Box_Barracks* UI_Box_Barracks::BoxBarracksUI = nullptr;
UI_Box_Barracks::UI_Box_Barracks()
{
	BoxBarracksUI = this;
}

UI_Box_Barracks::~UI_Box_Barracks()
{
}

void UI_Box_Barracks::Start()
{
#pragma region 리소스 로딩
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\Lobby\\");

	// Box 레이아웃 세팅용 리소스
	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Barracks.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Barracks.bmp"));
	}

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

#pragma endregion

#pragma region 렌더러 초기 세팅

	MainRenderer = CreateRenderer("UI_Barracks.bmp", RenderOrder::UI);
	MainRenderer->SetRenderScale({ 530, 250 });

	MainCollision = CreateCollision(CollisionOrder::UI);
	MainCollision->SetCollisionType(CollisionType::Rect);
	MainCollision->SetCollisionScale({ 480, 180 });
	MainCollision->SetCollisionPos({ 0, 18 });

	float4 StartPos = { -190, -55 };

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
			AllTeamRenderers.push_back(TeamRenderer);
			AllTeamRenderPos.push_back(initPos);
			break;

		case 1:
			TeamRenderer->SetTexture("UI_Teams_2Up.bmp");
			TeamRenderer->SetRenderPos(initPos);
			AllTeamRenderers.push_back(TeamRenderer);
			AllTeamRenderPos.push_back(initPos);
			break;

		case 2:
			TeamRenderer->SetTexture("UI_Teams_3Up.bmp");
			TeamRenderer->SetRenderPos(initPos);
			AllTeamRenderers.push_back(TeamRenderer);
			AllTeamRenderPos.push_back(initPos);
			break;

		case 3:
			TeamRenderer->SetTexture("UI_Teams_4Up.bmp");
			TeamRenderer->SetRenderPos(initPos);
			AllTeamRenderers.push_back(TeamRenderer);
			AllTeamRenderPos.push_back(initPos);
			break;

		case 4:
			TeamRenderer->SetTexture("UI_Teams_5Up.bmp");
			TeamRenderer->SetRenderPos(initPos);
			AllTeamRenderers.push_back(TeamRenderer);
			AllTeamRenderPos.push_back(initPos);
			break;

		case 5:
			TeamRenderer->SetTexture("UI_Teams_6Up.bmp");
			TeamRenderer->SetRenderPos(initPos);
			AllTeamRenderers.push_back(TeamRenderer);
			AllTeamRenderPos.push_back(initPos);
			break;

		default:
			break;
		}
	}

#pragma endregion

	ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);
}

void UI_Box_Barracks::Update(float _Delta)
{
	MainRenderer->SetText(std::to_string(m_SelectIndex));
	StateUpdate();
	CheckButtonCollision();
}

void UI_Box_Barracks::AddPlayerTeam()
{
	if (m_SelectIndex < 5)
	{
		++m_SelectIndex;
	}

	else
	{
		m_SelectIndex = 6;
	}

	ChangePlayerTeamLayout(m_SelectIndex);


	UI_Box_Teams::BoxTeamUI->ChangePlayerTeamLayout(m_SelectIndex);

	GameStateManager::GameState->SetTeamNumber(m_SelectIndex);
	
	ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
}

void UI_Box_Barracks::ChangePlayerTeamLayout(int _CurPlayerSelectIndex)
{

	for (size_t i = 0; i < _CurPlayerSelectIndex; i++)
	{
		AllTeamRenderers[i]->Off();

		for (size_t j = _CurPlayerSelectIndex; j < AllTeamRenderers.size(); j++)
		{
			AllTeamRenderers[j]->SetRenderPos(AllTeamRenderPos[j - i - 1]);
		}
	}
}

void UI_Box_Barracks::StateUpdate()
{
	switch (ButtonState)
	{
	case BUTTON_STATE::BUTTON_STATE_HOVERED:
		CheckButtonClick();
		break;

	case BUTTON_STATE::BUTTON_STATE_UNHOVERED:
		break;

	case BUTTON_STATE::BUTTON_STATE_CLICKED:
		AddPlayerTeam();
		break;

	default:
		break;
	}
}

void UI_Box_Barracks::ChangeState(BUTTON_STATE _ButtonState)
{
	ButtonState = _ButtonState;
}

void UI_Box_Barracks::CheckButtonClick()
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


void UI_Box_Barracks::CheckButtonCollision()
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
				UI_Box_Barracks* ButtonPtr = dynamic_cast<UI_Box_Barracks*>(thisActor);

				ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_HOVERED);
			}

			, [](GameEngineCollision* _this, GameEngineCollision* _Other)
				{

				}

				, [](GameEngineCollision* _this, GameEngineCollision* _Other)
					{
						GameEngineActor* thisActor = _this->GetActor();
						UI_Box_Barracks* ButtonPtr = dynamic_cast<UI_Box_Barracks*>(thisActor);

						ButtonPtr->ChangeState(BUTTON_STATE::BUTTON_STATE_UNHOVERED);
					}
				);

	}
}

