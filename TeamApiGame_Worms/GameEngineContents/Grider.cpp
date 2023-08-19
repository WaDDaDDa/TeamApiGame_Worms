//#include "Grider.h"
//#include "MouseObject.h"
//#include"PlayLevel.h"
//#include "Ground.h"
//#include "GameTurn.h"
//
//#include <GameEnginePlatform/GameEngineInput.h>
//#include <GameEngineCore/GameEngineRenderer.h>
//#include <GameEnginePlatform/GameEngineWindowTexture.h>
//#include <GameEngineCore/ResourcesManager.h>
//
//Grider::Grider()
//{
//}
//
//Grider::~Grider()
//{
//}
//
//
//void Grider::Start()
//{
//	Gride_Renderer = CreateRenderer(GetOrder());
//
//
//	if (false == ResourcesManager::GetInst().IsLoadTexture("grdl0.bmp"))
//	{
//		GameEnginePath FilePath;
//		FilePath.SetCurrentPath();
//		FilePath.MoveParentToExistsChild("ContentsResources");
//		FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl0.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl1.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl2.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl3.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl4.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl5.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl6.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl7.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl8.bmp"));
//
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds0.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds1.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds2.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds3.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds4.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds5.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds6.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds7.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds8.bmp"));
//
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl0b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl1b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl2b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl3b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl4b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl5b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl6b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl7b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl8b.bmp"));
//
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds0b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds1b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds2b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds3b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds4b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds5b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds6b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds7b.bmp"));
//		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds8b.bmp"));
//	}
//
//	Gride_Renderer->SetTexture("grds0.bmp");
//	Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds0b.bmp");
//
//}
//
//void Grider::Update(float _Delta)
//{
//	if (PlayerState::Girder != GetMaster()->GetState() )
//	{
//		size_t PlayerCount = Player::GetAllPlayer().size();
//		int PlayerStateCount = 0;
//		for (size_t i = 0; i < PlayerCount; i++)
//		{
//			if (PlayerState::Idle == Player::GetAllPlayer()[i]->GetState() || PlayerState::DeathEnd == Player::GetAllPlayer()[i]->GetState())
//			{
//				PlayerStateCount++;
//			}
//		}
//
//		if (PlayerStateCount == PlayerCount)
//		{
//			// 무기사용이 종료되면 다시 플레이어로 돌아간다.
//			Master->SwitchIsTurnPlayer();
//			Master->ChangeState(PlayerState::GirderOff);
//			Death();
//		}
//			return;
//
//	}
//	
//	CameraFocus(_Delta);
//
//	SetPos(MouseObject::GetPlayMousePos());
//
//	
//
//
//
//	{
//
//		if (true==GameEngineInput::IsDown(VK_RIGHT))
//		{
//			GridState NewState = static_cast<GridState>(static_cast<int>(Gride_State) + 1);
//
//			if (18 == static_cast<int>(NewState))
//			{
//				NewState = GridState::s0;
//			}
//			ChangeGride_State(NewState);
//
//		}
//
//		if (true==GameEngineInput::IsDown(VK_LEFT))
//		{
//			GridState NewState = static_cast<GridState>(static_cast<int>(Gride_State) - 1);
//
//			if (-1 == static_cast<int>(NewState))
//			{
//				NewState = GridState::l8;
//			}
//
//			ChangeGride_State(NewState);
//		}
//
//
//	}
//
//	if (true == GameEngineInput::IsDown(VK_LBUTTON))
//	{
//		GameEngineWindowTexture* GroundTexture = dynamic_cast<PlayLevel*>(GetLevel())->GetGround()->GetGroundTexture();
//		GameEngineWindowTexture* GroundPIxelTexture = dynamic_cast<PlayLevel*>(GetLevel())->GetGround()->GetPixelGroundTexture();
//
//		GriderConstruct(GroundTexture, GroundPIxelTexture);
//	}
//
//
//}
//
//void Grider::ChangeGride_State(GridState _State)
//{
//
//	switch (_State)
//	{
//	case GridState::s0:
//		Gride_Renderer->SetTexture("grds0.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds0b.bmp");
//		break;
//	case GridState::s1:
//		Gride_Renderer->SetTexture("grds1.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds1b.bmp");
//
//		break;
//	case GridState::s2:
//		Gride_Renderer->SetTexture("grds2.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds2b.bmp");
//
//		break;
//	case GridState::s3:
//		Gride_Renderer->SetTexture("grds3.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds3b.bmp");
//
//		break;
//	case GridState::s4:
//		Gride_Renderer->SetTexture("grds4.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds4b.bmp");
//
//		break;
//	case GridState::s5:
//		Gride_Renderer->SetTexture("grds5.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds5b.bmp");
//
//		break;
//	case GridState::s6:
//		Gride_Renderer->SetTexture("grds6.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds6b.bmp");
//
//		break;
//	case GridState::s7:
//		Gride_Renderer->SetTexture("grds7.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds7b.bmp");
//
//		break;
//	case GridState::s8:
//		Gride_Renderer->SetTexture("grds8.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds8b.bmp");
//
//		break;
//	case GridState::l0:
//		Gride_Renderer->SetTexture("grdl0.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl0b.bmp");
//		
//		break;
//	case GridState::l1:
//		Gride_Renderer->SetTexture("grdl1.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl1b.bmp");
//
//		break;
//	case GridState::l2:
//		Gride_Renderer->SetTexture("grdl2.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl2b.bmp");
//
//		break;
//	case GridState::l3:
//		Gride_Renderer->SetTexture("grdl3.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl3b.bmp");
//
//		break;
//	case GridState::l4:
//		Gride_Renderer->SetTexture("grdl4.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl4b.bmp");
//
//		break;
//	case GridState::l5:
//		Gride_Renderer->SetTexture("grdl5.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl5b.bmp");
//
//		break;
//	case GridState::l6:
//		Gride_Renderer->SetTexture("grdl6.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl6b.bmp");
//
//		break;
//	case GridState::l7:
//		Gride_Renderer->SetTexture("grdl7.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl7b.bmp");
//
//		break;
//	case GridState::l8:
//		Gride_Renderer->SetTexture("grdl8.bmp");
//		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl8b.bmp");
//
//		break;
//	default:
//		break;
//	}
//
//	Gride_State = _State;
//
//}
//
//void Grider::GriderConstruct(GameEngineWindowTexture* _GroundTexture, GameEngineWindowTexture* _GroundPixelTexture)
//{
//
//
//	float4 TexturePos = GetPos();
//	float4 TextureScale = Gride_Renderer->GetTexture()->GetScale();
//
//	_GroundTexture->TransCopy(Gride_Renderer->GetTexture(), TexturePos, TextureScale, float4::ZERO, TextureScale);
//	_GroundPixelTexture->TransCopy(Gride_PixelTexture, TexturePos, TextureScale, float4::ZERO, TextureScale);
//
//
//}
//
