#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameTurn : public GameEngineActor
{
public:
    GameTurn();
    ~GameTurn();

    GameTurn(const GameTurn& _Other) = delete;
    GameTurn(GameTurn&& _Other) noexcept = delete;
    GameTurn& operator=(const GameTurn& _Other) = delete;
    GameTurn& operator=(GameTurn&& _Other) noexcept = delete;

protected:

private:
    class Player* TurnPlayer = nullptr;

    void Start() override;

    void Update(float _Delta) override;

    void Render(float _Delta) override;

    void ChangeTurnPlayer();

    void CameraFocus(float _Delta);

    // ���÷��̾� �ѹ�
    int StartValue = 0;
    // ���÷��̾� ���ѽð�.
    float TurnPlayTime = 10.0f;
};
