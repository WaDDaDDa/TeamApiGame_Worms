#include "GravityActor.h"
#include <math.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>

GravityActor::GravityActor()
{
}

GravityActor::~GravityActor()
{
}

void GravityActor::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� �ȼ��浹�� �Ϸ��� �߽��ϴ�.");
	}
}

int GravityActor::GetGroundColor(unsigned int _DefaultColor, float4 _Pos)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�� üũ�� �ؽ�ó�� �������� �ʽ��ϴ�.");
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}

void GravityActor::CameraFocus(float _Delta)
{
	if (true != IsTurnPlayer)
	{
		return;
	}

	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();

	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	float CameraRangeX = CameraPos.X;
	float CameraRangeY = CameraPos.Y;

	float ImageX = GetGroundTexture()->GetScale().X - 1280.0f;
	float ImageY = GetGroundTexture()->GetScale().Y - 720.0f;

	float4 CameraTargetPos = GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() };
	
	float4 CameraDir = CameraTargetPos - CameraPos;

	if (abs(CameraDir.X) <= 50.0f && abs(CameraDir.Y) <= 50.0f)
	{
		GetLevel()->GetMainCamera()->SetPos(CameraTargetPos);
	}
	else
	{
		CameraDir.Normalize();
		GetLevel()->GetMainCamera()->AddPos(CameraDir * CameraSpeed * _Delta);
	}



	// ī�޶� ���� �������� ��������.
	if (0.0f >= GetLevel()->GetMainCamera()->GetPos().X)
	{
		GetLevel()->GetMainCamera()->SetPos({ 0.0f, GetLevel()->GetMainCamera()->GetPos().Y });
	}
	// ī�޶� ���� ������ �ִ�ġ�� ��������.
	if (ImageX <= GetLevel()->GetMainCamera()->GetPos().X)
	{
		GetLevel()->GetMainCamera()->SetPos({ ImageX, GetLevel()->GetMainCamera()->GetPos().Y });
	}
	// ī�޶� ���� �Ʒ� �ִ�ġ�� ��������.
	if (ImageY <= GetLevel()->GetMainCamera()->GetPos().Y)
	{
		GetLevel()->GetMainCamera()->SetPos({ GetLevel()->GetMainCamera()->GetPos().X, ImageY });
	}
	// ī�޶� ���� �� �ִ�ġ�� ��������.
	if (0.0f >= GetLevel()->GetMainCamera()->GetPos().Y)
	{
		GetLevel()->GetMainCamera()->SetPos({ GetLevel()->GetMainCamera()->GetPos().X, 0.0f });
	}
}

float4 GravityActor::ActorCameraPos()
{
	return GetPos() - GetLevel()->GetMainCamera()->GetPos();
}

void GravityActor::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	GravityVector += float4::DOWN * GravityPower * _Delta;

	AddPos(GravityVector * _Delta);
}

void GravityActor::GroundCheck(float _Delta)
{
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));

	// ��ġ�� ����̸� �߷��ۿ�.
	// ��� ����̸� �����̴�.
	if (RGB(255, 255, 255) == Color)
	{
		Gravity(_Delta);
	}
	else // �������� �ƴϴ� = ��������ִ�.
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

		// üũ�� ����ϳ���  ����� �ƴ϶�� ��ĭ�ø��� �ݺ��Ѵ�.
		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			AddPos(float4::UP);
		}
		GravityReset();
	}
}