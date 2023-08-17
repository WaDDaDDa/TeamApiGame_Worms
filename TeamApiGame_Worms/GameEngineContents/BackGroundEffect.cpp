#include "BackGroundEffect.h"
#include "ContentsEnum.h"
#include "ContentsDefine.h"
#include "Wind.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#define CHANGINGWINDTIME 0.5f

BackGroundEffect::BackGroundEffect()
{
}

BackGroundEffect::~BackGroundEffect()
{
}

void BackGroundEffect::Start()
{

	GameEngineRenderer* Renderer = CreateRenderer(RenderOrder::BackGroundEffect);


	if (false == ResourcesManager::GetInst().IsLoadTexture("debris.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("debris.Bmp"), 1, 128);

	}

	Renderer->CreateAnimation("BackGroundEffect", "debris.Bmp", 0, 127, 0.01f, true);
	Renderer->ChangeAnimation("BackGroundEffect");

	DownPower = GameEngineRandom::MainRandom.RandomFloat(50.0f, 140.0f);
	HorizonPower = GameEngineRandom::MainRandom.RandomFloat( 1.0f,100.0f);
	WindRatio = GameEngineRandom::MainRandom.RandomFloat(0.8f, 1.2f);
	
	HorizonVector = Dir* HorizonPower;

}

void BackGroundEffect::Update(float _Delta)
{

	{
		if (WindCheck != Wind::GetWind()->GetWindVector())
		{

			if (Dir != Wind::GetWind()->GetWindDir())
			{

				HorizonVector = float4::LerpClimp(Dir * (HorizonPower + WindPower * WindRatio), float4::ZERO, CurTime / CHANGINGWINDTIME);



				if (HorizonVector == float4::ZERO)
				{
					CurTime = 0.0f;
					Dir = Wind::GetWind()->GetWindDir();
					WindCheck = float4::ZERO;
				}
				CurTime += _Delta;
			}

			else
			{

				if (WindCheck == float4::ZERO)
				{

					HorizonVector = float4::LerpClimp(float4::ZERO, Dir * (HorizonPower + Wind::GetWind()->GetWindPower() * WindRatio), CurTime / CHANGINGWINDTIME);

				}
				else
				{
					HorizonVector = float4::LerpClimp(Dir * (HorizonPower + WindPower), Dir * (HorizonPower + Wind::GetWind()->GetWindPower() * WindRatio), CurTime / CHANGINGWINDTIME);

				}



				if (HorizonVector == Dir * (HorizonPower + Wind::GetWind()->GetWindPower() * WindRatio))
				{
					CurTime = 0.0f;
					WindCheck = Wind::GetWind()->GetWindVector();
					WindPower = Wind::GetWind()->GetWindPower();
				}


				CurTime += _Delta;
			}

		}


		float4 DownVector = float4::DOWN * DownPower * _Delta;

		AddPos(DownVector + (HorizonVector * _Delta));
	}

	{
		if (-10.0f > GetPos().X ||
			BACKGROUND_SCALE.X + 10.0f < GetPos().X ||
			1870.0f<GetPos().Y)
		{
			Death();
		}

	}

	
}

void BackGroundEffect::Render(float _Delta)
{

	/*{
		HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

		std::string Text2 = "HorizonVector : ";
		Text2 += std::to_string(HorizonVector.X);

		 



		TextOutA(dc, 2, 40, Text2.c_str(), static_cast<int>(Text2.size()));
	}*/
}
