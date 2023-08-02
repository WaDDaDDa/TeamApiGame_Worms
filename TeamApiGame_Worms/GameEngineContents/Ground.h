
#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineWindowTexture;
class GameEngineRenderer;
class Ground : public GameEngineActor
{
	friend class Hole;
public:
	Ground();
	~Ground();

	Ground(const Ground& _Other) = delete;
	Ground(Ground&& _Other) noexcept = delete;
	Ground& operator=(const Ground& _Other) = delete;
	Ground& operator=(const Ground&& _Other) noexcept = delete;

	void Init(const std::string& _FileName, const std::string& _DebugFileName);

	void SwitchRender();

	void ContactGround(float4 _Pos,float4 _HoleScale);
	
	GameEngineWindowTexture* GetGroundTexture();
	GameEngineWindowTexture* GetPixelGroundTexture();
	
protected:

private:
	
	bool SwitchRenderValue = true;
	std::string FileName;
	 GameEngineRenderer* Renderer;
	 GameEngineRenderer* DebugRenderer;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

};

