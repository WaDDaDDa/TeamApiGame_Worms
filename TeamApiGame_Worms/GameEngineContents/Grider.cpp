#include "Grider.h"
#include "MouseObject.h"
#include"PlayLevel.h"
#include "Ground.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>

Grider::Grider()
{
}

Grider::~Grider()
{
}


void Grider::Start()
{
	Renderer = CreateRenderer(GetOrder());


	if (false == ResourcesManager::GetInst().IsLoadTexture("grdl0.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Image\\Weapons\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl0.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl1.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl2.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl3.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl4.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl5.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl6.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl7.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl8.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds0.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds1.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds2.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds3.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds4.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds5.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds6.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds7.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds8.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl0b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl1b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl2b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl3b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl4b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl5b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl6b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl7b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grdl8b.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds0b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds1b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds2b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds3b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds4b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds5b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds6b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds7b.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("grds8b.bmp"));
	}

	Renderer->SetTexture("grds0.bmp");
	PixelTexture = ResourcesManager::GetInst().FindTexture("grds0b.bmp");

}

void Grider::Update(float _Delta)
{
	if (PlayerState::Girder != GetMaster()->GetState())
	{
		Death();
	}
	

	SetPos(MouseObject::GetPlayMousePos());

	



	{

		if (true==GameEngineInput::IsDown(VK_RIGHT))
		{
			GridState NewState = static_cast<GridState>(static_cast<int>(State) + 1);

			if (18 == static_cast<int>(NewState))
			{
				NewState = GridState::s0;
			}
			ChangeState(NewState);

		}

		if (true==GameEngineInput::IsDown(VK_LEFT))
		{
			GridState NewState = static_cast<GridState>(static_cast<int>(State) - 1);

			if (-1 == static_cast<int>(NewState))
			{
				NewState = GridState::l8;
			}

			ChangeState(NewState);
		}


	}

	if (true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		GameEngineWindowTexture* GroundTexture = dynamic_cast<PlayLevel*>(GetLevel())->GetGround()->GetGroundTexture();
		GameEngineWindowTexture* GroundPIxelTexture = dynamic_cast<PlayLevel*>(GetLevel())->GetGround()->GetPixelGroundTexture();

		GriderConstruct(GroundTexture, GroundPIxelTexture);
	}


}

void Grider::ChangeState(GridState _State)
{

	switch (_State)
	{
	case GridState::s0:
		Renderer->SetTexture("grds0.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grds0b.bmp");
		break;
	case GridState::s1:
		Renderer->SetTexture("grds1.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grds1b.bmp");

		break;
	case GridState::s2:
		Renderer->SetTexture("grds2.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grds2b.bmp");

		break;
	case GridState::s3:
		Renderer->SetTexture("grds3.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grds3b.bmp");

		break;
	case GridState::s4:
		Renderer->SetTexture("grds4.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grds4b.bmp");

		break;
	case GridState::s5:
		Renderer->SetTexture("grds5.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grds5b.bmp");

		break;
	case GridState::s6:
		Renderer->SetTexture("grds6.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grds6b.bmp");

		break;
	case GridState::s7:
		Renderer->SetTexture("grds7.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grds7b.bmp");

		break;
	case GridState::s8:
		Renderer->SetTexture("grds8.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grds8b.bmp");

		break;
	case GridState::l0:
		Renderer->SetTexture("grdl0.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grdl0b.bmp");
		
		break;
	case GridState::l1:
		Renderer->SetTexture("grdl1.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grdl1b.bmp");

		break;
	case GridState::l2:
		Renderer->SetTexture("grdl2.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grdl2b.bmp");

		break;
	case GridState::l3:
		Renderer->SetTexture("grdl3.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grdl3b.bmp");

		break;
	case GridState::l4:
		Renderer->SetTexture("grdl4.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grdl4b.bmp");

		break;
	case GridState::l5:
		Renderer->SetTexture("grdl5.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grdl5b.bmp");

		break;
	case GridState::l6:
		Renderer->SetTexture("grdl6.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grdl6b.bmp");

		break;
	case GridState::l7:
		Renderer->SetTexture("grdl7.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grdl7b.bmp");

		break;
	case GridState::l8:
		Renderer->SetTexture("grdl8.bmp");
		PixelTexture = ResourcesManager::GetInst().FindTexture("grdl8b.bmp");

		break;
	default:
		break;
	}

	State = _State;

}

void Grider::GriderConstruct(GameEngineWindowTexture* _GroundTexture, GameEngineWindowTexture* _GroundPixelTexture)
{


	float4 TexturePos = GetPos();
	float4 TextureScale = Renderer->GetTexture()->GetScale();

	_GroundTexture->TransCopy(Renderer->GetTexture(), TexturePos, TextureScale, float4::ZERO, TextureScale);
	_GroundPixelTexture->TransCopy(PixelTexture, TexturePos, TextureScale, float4::ZERO, TextureScale);


}

