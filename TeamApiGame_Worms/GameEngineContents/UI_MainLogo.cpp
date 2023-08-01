#include "UI_MainLogo.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineWindow.h>

UI_MainLogo::UI_MainLogo()
{
}

UI_MainLogo::~UI_MainLogo()
{
}

void UI_MainLogo::Start()
{

	// 리소스 로딩
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");
	FilePath.MoveChild("ContentsResources\\UI\\Title\\");

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Title_Logo.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Title_Logo.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_TitleLogo_Actor.bmp"))
	{
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("UI_TitleLogo_Actor.bmp"), 5, 1);
	}


	if (false == ResourcesManager::GetInst().IsLoadTexture("Armageddon_1.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Armageddon_1.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Armageddon_2.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Armageddon_2.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Armageddon_3.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Armageddon_3.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Armageddon_4.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Armageddon_4.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Armageddon_5.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Armageddon_5.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Armageddon_6.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Armageddon_6.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Armageddon_7.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Armageddon_7.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Armageddon_8.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Armageddon_8.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Armageddon_9.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Armageddon_9.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Armageddon_10.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Armageddon_10.bmp"));
	}


	// 렌더러 세팅
	TitleRenderer = CreateUIRenderer("UI_Title_Logo.bmp", RenderOrder::UI);
	TitleRenderer->SetRenderScale({ 672, 200 });
	TitleRenderer->SetRenderPos({ 646, 124 });

	AnimRenderer = CreateUIRenderer(RenderOrder::UI);
	AnimRenderer->SetRenderScale({ 160, 140 });
	AnimRenderer->SetRenderPos({ 542, 124 });


	if (0 == AllText.size())
	{
		{
			GameEngineRenderer* NewTextRenderer = CreateUIRenderer("Armageddon_1.bmp", RenderOrder::UI);
			NewTextRenderer->SetRenderScale({ 70, 70 });
			NewTextRenderer->SetRenderPos({ 367, 238 });
			AllText.push_back(NewTextRenderer);
		}

		{
			GameEngineRenderer* NewTextRenderer = CreateUIRenderer("Armageddon_2.bmp", RenderOrder::UI);
			NewTextRenderer->SetRenderScale({ 70, 70 });
			NewTextRenderer->SetRenderPos({ 430, 238 });
			AllText.push_back(NewTextRenderer);
		}

		{
			GameEngineRenderer* NewTextRenderer = CreateUIRenderer("Armageddon_3.bmp", RenderOrder::UI);
			NewTextRenderer->SetRenderScale({ 70, 70 });
			NewTextRenderer->SetRenderPos({ 495, 238 });
			AllText.push_back(NewTextRenderer);
		}

		{
			GameEngineRenderer* NewTextRenderer = CreateUIRenderer("Armageddon_4.bmp", RenderOrder::UI);
			NewTextRenderer->SetRenderScale({ 70, 70 });
			NewTextRenderer->SetRenderPos({ 567, 238 });
			AllText.push_back(NewTextRenderer);
		}

		{
			GameEngineRenderer* NewTextRenderer = CreateUIRenderer("Armageddon_5.bmp", RenderOrder::UI);
			NewTextRenderer->SetRenderScale({ 70, 70 });
			NewTextRenderer->SetRenderPos({ 630, 238 });
			AllText.push_back(NewTextRenderer);
		}

		{
			GameEngineRenderer* NewTextRenderer = CreateUIRenderer("Armageddon_6.bmp", RenderOrder::UI);
			NewTextRenderer->SetRenderScale({ 70, 70 });
			NewTextRenderer->SetRenderPos({ 693, 238 });
			AllText.push_back(NewTextRenderer);
		}


		{
			GameEngineRenderer* NewTextRenderer = CreateUIRenderer("Armageddon_7.bmp", RenderOrder::UI);
			NewTextRenderer->SetRenderScale({ 70, 70 });
			NewTextRenderer->SetRenderPos({ 750, 238 });
			AllText.push_back(NewTextRenderer);
		}



		{
			GameEngineRenderer* NewTextRenderer = CreateUIRenderer("Armageddon_8.bmp", RenderOrder::UI);
			NewTextRenderer->SetRenderScale({ 70, 70 });
			NewTextRenderer->SetRenderPos({ 810, 238 });
			AllText.push_back(NewTextRenderer);
		}

		{
			GameEngineRenderer* NewTextRenderer = CreateUIRenderer("Armageddon_9.bmp", RenderOrder::UI);
			NewTextRenderer->SetRenderScale({ 70, 70 });
			NewTextRenderer->SetRenderPos({ 874, 238 });
			AllText.push_back(NewTextRenderer);
		}

		{
			GameEngineRenderer* NewTextRenderer = CreateUIRenderer("Armageddon_10.bmp", RenderOrder::UI);
			NewTextRenderer->SetRenderScale({ 70, 70 });
			NewTextRenderer->SetRenderPos({ 938, 238 });
			AllText.push_back(NewTextRenderer);
		}

	}

	for (int i = 0; i < AllText.size(); i++)
	{
		AllText[i]->Off();
	}

	// 애니메이션 생성 및 적용
	AnimRenderer->CreateAnimation("TITLE_LOGO_Anim", "UI_TitleLogo_Actor.bmp", 0, 4, 1.0f, false);
	AnimRenderer->ChangeAnimation("TITLE_LOGO_Anim");

}

void UI_MainLogo::Update(float _Delta)
{
	if (true == IsAllTextShow)
	{
		textTimer += _Delta;

		if (textTimer > 0.2f)
		{
			textTimer = 0.0f;

			AllText[textIndex]->On();

			++textIndex;

			if (textIndex >= 10)
			{
				IsAllTextShow = false;
			}
		}
	}
}
