#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineWindowTexture;
class GravityActor : public GameEngineActor
{
public:
	// constrcuter destructer
	GravityActor();
	~GravityActor();

	// delete Function
	GravityActor(const GravityActor& _Other) = delete;
	GravityActor(GravityActor&& _Other) noexcept = delete;
	GravityActor& operator=(const GravityActor& _Other) = delete;
	GravityActor& operator=(GravityActor&& _Other) noexcept = delete;

	GameEngineWindowTexture* GetGroundTexture()
	{
		return GroundTexture;
	}

	void SetGroundTexture(const std::string& _GroundTextureName);

	void SetGroundTexture(GameEngineWindowTexture* _GroundTexture)
	{
		GroundTexture = _GroundTexture;
	}

	int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);


	float4 ActorCameraPos();

	virtual void GroundCheck(float _Delta);

	void SwitchIsTurnPlayer()
	{
		IsTurnPlayer = !IsTurnPlayer;
	}
	// GravityActor들의 제어권 (카메라 포커싱, 턴플레이어의 행동권)
	bool IsTurnPlayer = false;

	void IsWindOn()
	{
		IsWind = true;
	}


protected:
	virtual void CameraFocus(float _Delta);

	void SetGravityPower(float _Power)
	{
		GravityPower = _Power;
	}


private:
	class GameEngineWindowTexture* GroundTexture = nullptr;


	// Gravity
public:
	virtual void Gravity(float _Delta);

	void GravityReset()
	{
		GravityVector = float4::ZERO;
	}

	float4 GetGravityVector()
	{
		return GravityVector;
	}

	void SetGravityVector(float4 _GravityVector)
	{
		GravityVector = _GravityVector;
	}

private:
	bool MouseFocus = false;
	bool IsGravity = true;
	bool IsWind = false;
	float CameraSpeed = 2500.0f;
	float GravityPower = 1000.0f;
	float4 GravityVector = float4::ZERO;
};

