#include "LobbyLevel.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>


#include "BackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#pragma region UI���� ����� ��� & �Լ� ���� ����
#include "UI_Mouse.h"
#include "UI_Button.h"
#include "UI_Meteor.h"

#include "ContentsDefine.h"
#include "MouseObject.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineRandom.h>

#pragma endregion

LobbyLevel::LobbyLevel()
{
}

LobbyLevel::~LobbyLevel()
{
}

void LobbyLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<MouseObject>();
	CreateActor<UI_Mouse>();

	//BackGround
	{
		BackGround* BackGroundPtr = CreateActor<BackGround>();
		BackGroundPtr->VerticalPatternInit("Lobby_Backdrop.bmp");

	}
}

void LobbyLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}

void LobbyLevel::Start()
{
}

void LobbyLevel::Update(float _Delta)
{

	// ������ ȿ�� ����
	float MeteorPosX = GameEngineRandom::MainRandom.RandomFloat(-800, 1400);
	float MeteorPosY = GameEngineRandom::MainRandom.RandomFloat(-400, 0);

	MeteorCreateTimer += _Delta;

	if (MeteorCreateTimer > 0.2f)
	{
		UI_Meteor* Meteor = CreateActor<UI_Meteor>();
		Meteor->SetPos({ MeteorPosX, MeteorPosY });
		MeteorCreateTimer = 0.0f;
	}

}

void LobbyLevel::Release()
{
}

#pragma region UI �Լ� ������ ��Ͽ� �Լ�

#pragma endregion