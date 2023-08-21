#include "Player.h"
#include "Grider.h"
#include "MouseObject.h"
#include"PlayLevel.h"
#include "Ground.h"
#include "GameTurn.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>

void Player::ChangeGride_State(GridState _State)
{

	switch (_State)
	{
	case GridState::s0:
		Gride_Renderer->SetTexture("grds0.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds0b.bmp");
		break;
	case GridState::s1:
		Gride_Renderer->SetTexture("grds1.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds1b.bmp");

		break;
	case GridState::s2:
		Gride_Renderer->SetTexture("grds2.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds2b.bmp");

		break;
	case GridState::s3:
		Gride_Renderer->SetTexture("grds3.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds3b.bmp");

		break;
	case GridState::s4:
		Gride_Renderer->SetTexture("grds4.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds4b.bmp");

		break;
	case GridState::s5:
		Gride_Renderer->SetTexture("grds5.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds5b.bmp");

		break;
	case GridState::s6:
		Gride_Renderer->SetTexture("grds6.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds6b.bmp");

		break;
	case GridState::s7:
		Gride_Renderer->SetTexture("grds7.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds7b.bmp");

		break;
	case GridState::s8:
		Gride_Renderer->SetTexture("grds8.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grds8b.bmp");

		break;
	case GridState::l0:
		Gride_Renderer->SetTexture("grdl0.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl0b.bmp");

		break;
	case GridState::l1:
		Gride_Renderer->SetTexture("grdl1.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl1b.bmp");

		break;
	case GridState::l2:
		Gride_Renderer->SetTexture("grdl2.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl2b.bmp");

		break;
	case GridState::l3:
		Gride_Renderer->SetTexture("grdl3.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl3b.bmp");

		break;
	case GridState::l4:
		Gride_Renderer->SetTexture("grdl4.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl4b.bmp");

		break;
	case GridState::l5:
		Gride_Renderer->SetTexture("grdl5.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl5b.bmp");

		break;
	case GridState::l6:
		Gride_Renderer->SetTexture("grdl6.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl6b.bmp");

		break;
	case GridState::l7:
		Gride_Renderer->SetTexture("grdl7.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl7b.bmp");

		break;
	case GridState::l8:
		Gride_Renderer->SetTexture("grdl8.bmp");
		Gride_PixelTexture = ResourcesManager::GetInst().FindTexture("grdl8b.bmp");

		break;
	default:
		break;
	}

	Gride_State = _State;

}

void Player::GriderConstruct(GameEngineWindowTexture* _GroundTexture, GameEngineWindowTexture* _GroundPixelTexture)
{

	float4 TexturePos = MouseObject::GetPlayMousePos();
	float4 TextureScale = Gride_Renderer->GetTexture()->GetScale();

	_GroundTexture->TransCopy(Gride_Renderer->GetTexture(), TexturePos, TextureScale, float4::ZERO, TextureScale);
	_GroundPixelTexture->TransCopy(Gride_PixelTexture, TexturePos, TextureScale, float4::ZERO, TextureScale);


}

