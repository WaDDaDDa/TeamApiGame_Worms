#include "GravityActor.h"
#include "Wind.h"
#include <math.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "MouseObject.h"

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
		MsgBoxAssert("존재하지 않는 텍스처로 픽셀충돌을 하려고 했습니다.");
	}
}

int GravityActor::GetGroundColor(unsigned int _DefaultColor, float4 _Pos)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("땅 체크용 텍스처가 존재하지 않습니다.");
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
	
	float4 MousePos = MouseObject::GetPlayMousePos();
	float MouseX = MousePos.X;
	float MouseY = MousePos.Y;

	// 키입력이있다면 마우스포커스 false
	if (true == GameEngineInput::AllKeyCheck())
	{
		MouseFocus = false;
	}

	// 마우스로 화면 이동
	if (1200.0f < MouseX - CameraRangeX)
	{
		MouseFocus = true;
	}
	else if (80.0f > MouseX - CameraRangeX)
	{
		MouseFocus = true;
	}

	if (-80.0f < CameraRangeY - MouseY)
	{
		MouseFocus = true;
	}
	else if (-640.0f > CameraRangeY - MouseY)
	{
		MouseFocus = true;
	}

	// 플레이어 포커싱
	if (MouseFocus == true)
	{	// 마우스로 화면 이동
		if (1200.0f < MouseX - CameraRangeX)
		{
			GetLevel()->GetMainCamera()->AddPos(float4::RIGHT * CameraSpeed * _Delta);
		}
		else if (80.0f > MouseX - CameraRangeX)
		{
			GetLevel()->GetMainCamera()->AddPos(float4::LEFT * CameraSpeed * _Delta);
		}

		if (-80.0f < CameraRangeY - MouseY)
		{
			GetLevel()->GetMainCamera()->AddPos(float4::UP * CameraSpeed * _Delta);
		}
		else if (-640.0f > CameraRangeY - MouseY)
		{
			GetLevel()->GetMainCamera()->AddPos(float4::DOWN * CameraSpeed * _Delta);
		}

		//MouseFocus = false;
	}
	else if (abs(CameraDir.X) <= 50.0f && abs(CameraDir.Y) <= 50.0f)
	{
		GetLevel()->GetMainCamera()->SetPos(CameraTargetPos);
	}
	else
	{
		CameraDir.Normalize();
		GetLevel()->GetMainCamera()->AddPos(CameraDir * CameraSpeed * _Delta);
	}


	// 카메라가 맵의 왼쪽으로 못나가게.
	if (0.0f >= GetLevel()->GetMainCamera()->GetPos().X)
	{
		GetLevel()->GetMainCamera()->SetPos({ 0.0f, GetLevel()->GetMainCamera()->GetPos().Y });
	}
	// 카메라가 맵의 오른쪽 최대치를 못나가게.
	if (ImageX <= GetLevel()->GetMainCamera()->GetPos().X)
	{
		GetLevel()->GetMainCamera()->SetPos({ ImageX, GetLevel()->GetMainCamera()->GetPos().Y });
	}
	// 카메라가 맵의 아래 최대치를 못나가게.
	if (ImageY <= GetLevel()->GetMainCamera()->GetPos().Y)
	{
		GetLevel()->GetMainCamera()->SetPos({ GetLevel()->GetMainCamera()->GetPos().X, ImageY });
	}
	// 카메라가 맵의 위 최대치를 못나가게.
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

	if (true == IsWind)
	{
		GravityVector += float4::DOWN * GravityPower * _Delta + Wind::GetWind()->GetWindVector();
	}
	else
	{
		GravityVector += float4::DOWN * GravityPower * _Delta;
	}


	AddPos(GravityVector * _Delta);
}

void GravityActor::GroundCheck(float _Delta)
{
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));

	// 위치가 흰색이면 중력작용.
	// 모두 흰색이면 공중이다.
	if (RGB(255, 255, 255) == Color)
	{
		Gravity(_Delta);
	}
	else // 모두흰색이 아니다 = 땅에닿아있다.
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

		// 체크중 어느하나라도  흰색이 아니라면 한칸올리기 반복한다.
		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			AddPos(float4::UP);
		}

		GravityReset();
	}
}