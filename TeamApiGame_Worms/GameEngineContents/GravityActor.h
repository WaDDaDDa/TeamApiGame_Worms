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

	void CameraFocus();

	float4 ActorCameraPos();

	void GroundCheck(float _Delta);

protected:

private:
	class GameEngineWindowTexture* GroundTexture = nullptr;


	// Gravity
public:
	void Gravity(float _Delta);

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
	bool IsGravity = true;

	float GravityPower = 1000.0f;
	float4 GravityVector = float4::ZERO;

};
