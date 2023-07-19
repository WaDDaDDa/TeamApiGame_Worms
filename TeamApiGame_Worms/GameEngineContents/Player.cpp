#include "Player.h"
#pragma region Headers

#include "ContentsEnum.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include "Bullet.h"
#include "Monster.h"
#include "PlayUIManager.h"
#include <GameEnginePlatform/GameEngineInput.h>

#pragma endregion

Player* Player::MainPlayer = nullptr;

Player::Player() 
{
}

Player::~Player() 
{
}


void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		// ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Left_Player.bmp"));

		GameEngineWindowTexture* T = ResourcesManager::GetInst().TextureCreate("Fade", {1280, 720});
		T->FillTexture(RGB(255, 0 , 0));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Left_Player_Mask.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Right_Player_Mask.bmp"));

		GameEngineSprite* Sprite0 = ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Player.bmp"), 5, 17);
		Sprite0->SetMaskTexture("Left_Player_Mask.bmp");

		GameEngineSprite* Sprite1 = ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Player.bmp"), 5, 17);
		Sprite1->SetMaskTexture("Right_Player_Mask.bmp");
		
		FolderPath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().CreateSpriteFolder("FolderPlayer", FolderPath.PlusFilePath("FolderPlayer"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Test.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));
	}

	{

		MainRenderer = CreateRenderer(200);
		MainRenderer->CreateAnimation("Test", "FolderPlayer");
		MainRenderer->CreateAnimation("Left_Idle", "Left_Player.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Idle", "Right_Player.bmp", 0, 2, 1.0f, true);
		MainRenderer->CreateAnimation("Left_Run", "Left_Player.bmp", 3, 6, 0.1f, true);
		// MainRenderer->CreateAnimation("Right_Run", "Right_Player.bmp", 20, 0, 0.1f, true);

		MainRenderer->CreateAnimationToFrame("Right_Run", "Right_Player.bmp", {20, 19, 18, 17, 16, 15}, 0.1f, true);
		MainRenderer->ChangeAnimation("Test");
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetAngle(45.0f);
	}

	{
		HPRender = CreateRenderer("HPBar.bmp", RenderOrder::Play);
		HPRender->SetRenderPos({ 0, -200 });
		HPRender->SetRenderScale({ 40, 40 });
		HPRender->SetTexture("HPBar.bmp");
		// Ptr->SetText("�����ʤ��Ӥ�����ä��Ӥ�����ä��Ӥ�����ä������뷯���Ӥ������Τø���", 40);
	}

	{
		/*GameEngineRenderer* Ptr = CreateRenderer("Fade", 6000);
		Ptr->SetRenderScale({ 1280, 720 });*/
	}

	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollsion->SetCollisionScale({100, 100});
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}


	// SetGroundTexture("StageTestPixel.bmp");

	

	// State = PlayerState::Idle;

	ChanageState(PlayerState::Idle);
	Dir = PlayerDir::Right;
}

void Player::Update(float _Delta)
{
	if (true == MainRenderer->IsAnimation("Left_Idle")
		&& true == MainRenderer->IsAnimationEnd())
	{
		int a = 0;
	}


	static float RollAngle = 45.0f;
	RollAngle += _Delta * 360.0f;
	float4 Range = float4::GetUnitVectorFromDeg(RollAngle);
	HPRender->SetRenderPos(Range * 200.0f);

	//std::vector<GameEngineCollision*> _Col;
	//if (true == BodyCollsion->Collision(CollisionOrder::MonsterBody, _Col
	//	, CollisionType::Rect // ���� �簢������ ����
	//	, CollisionType::CirCle // ��뵵 �簢������ ����
	//))
	//{
	//	for (size_t i = 0; i < _Col.size(); i++)
	//	{
	//		GameEngineCollision* Collison = _Col[i];

	//		GameEngineActor* Actor = Collison->GetActor();

	//		Actor->Death();
	//	}
	//	// ���� ���Ͷ� �浹�Ѱž�.
	//}

	// ����
	BodyCollsion->CollisionCallBack(
		CollisionOrder::MonsterBody
		, CollisionType::Rect // ���� �簢������ ����
		, CollisionType::CirCle
		, [](GameEngineCollision* _this, GameEngineCollision* _Other)
		{

			//GameEngineActor* thisActor = _this->GetActor();
			//Player* PlayerPtr = dynamic_cast<Player*>(thisActor);

			//GameEngineActor* Monster = _Other->GetActor();
			//Monster* PlayerPtr = dynamic_cast<Monster*>(thisActor);

			// �����̶� �׳� �� �˴ϴ�.
			// ���⼭ �������� �ָ� �� 1���� �ش�.
			// _Other->GetActor()->
			// _Other->GetActor()->Death();
		}
	);


	if (true == GameEngineInput::IsDown('L'))
	{
		// GameEngineSound::SoundLoad("C:\\AAAA\\AAAA\\A\\AAA.Mp3");
		// GameEngineSound::SoundPlay("AAA.Mp3");
		// GameEngineSound::PlayBgm("AAA.Mp3");
		// GameEngineSound::StopBgm("AAA.Mp3");

		// GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(1.0f * _Delta);

		if (0.0f != GameEngineTime::MainTimer.GetTimeScale(UpdateOrder::Monster))
		{
			GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Monster, 0.0f);
		}
		else {
			GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Monster, 1.0f);
		}

		// Monster::AllMonsterDeath();
	}

	if (true == GameEngineInput::IsPress('Y'))
	{
		// GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		GameEngineLevel::CollisionDebugRenderSwitch();
	}

	if (0.0f == GameEngineTime::MainTimer.GetTimeScale(0))
	{
		return;
	}

	StateUpdate(_Delta);

	CameraFocus();

	// Gravity();
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Run:
		return RunUpdate(_Delta);
	case PlayerState::Jump:
		return JumpUpdate(_Delta);
		break;
	default:
		break;
	}

}

void Player::ChanageState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}


void Player::DirCheck()
{

	// �ڵ���� ���������� ����Ǳ� ������ 
	// D�� �������·� A������������ ������ȯ�� ����������
	// A�� �������·� D�� ������������ A�� ó���� ���� �̷������ ������ȯ�� �����ʱ⶧���� ������ �߻��ߴ�.

	// ������ �����ϴ� Ű���� ��� ������� �׻��� �״�� ����. �Ʒ��� D�� �����϶� Left�� �Ǵ� ���� ����.
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		return;
	}

	// A�� ���Ȱų� D�� �����̶�� Left�� ������ȯ �ε� �������־ Left�� �ٶ󺸴� ������ ����.
	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsFree('D'))
	{
		Dir = PlayerDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	// D�� ���Ȱų� A�� �����̸� Right�� ���� ��ȯ.
	if (true == GameEngineInput::IsDown('D') || true == GameEngineInput::IsFree('A'))
	{
		Dir = PlayerDir::Right;
		ChangeAnimationState(CurState);
		return;
	}


	// ���� �ִ� �ڵ�.
	/*PlayerDir CheckDir = PlayerDir::Left;

	if (true == GameEngineInput::IsDown('A'))
	{
		CheckDir = PlayerDir::Left;
	}
	else if (true == GameEngineInput::IsDown('D'))
	{
		CheckDir = PlayerDir::Right;
	}

	bool ChangeDir = false;

	if (CheckDir != PlayerDir::Max)
	{
		Dir = CheckDir;
		ChangeDir = true;
	}

	if (CheckDir != PlayerDir::Max && true == ChangeDir)
	{
		ChangeAnimationState(CurState);
	}*/

}

void Player::ChangeAnimationState(const std::string& _StateName)
{
	// "Idle"
	// _StateName

	std::string AnimationName;

	switch (Dir)
	{
	case PlayerDir::Right:
		AnimationName = "Right_";
		break;
	case PlayerDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}



void Player::LevelStart() 
{
	MainPlayer = this;
}

void Player::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	{
		std::string Text = "";
		Text += "�÷��̾� �׽�Ʈ �� : ";
		Text += std::to_string(1.0f / _Delta);
		TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));
	}

	{
		float4 PlayerPos = GameEngineWindow::MainWindow.GetScale().Half();
		float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
		float4 Dir = PlayerPos - MousePos;

		std::string Text = "";
		Text += "���콺 �ޱ� �� : ";
		Text += std::to_string(Dir.AngleDeg());
		TextOutA(dc, 2, 20, Text.c_str(), static_cast<int>(Text.size()));
	}

	CollisionData Data;

	Data.Pos = ActorCameraPos();
	Data.Scale = { 5,5 };
	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	Data.Pos = ActorCameraPos() + LeftCheck;
	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	Data.Pos = ActorCameraPos() + RightCheck;
	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
}