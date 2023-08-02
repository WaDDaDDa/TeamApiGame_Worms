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

    class Player* GetTurnPlayer()
    {
        return TurnPlayer;
    }

    void ChangeTurnPlayer();

    static GameTurn MainGameTurn;

protected:

private:
    Player* TurnPlayer = nullptr;

    void Start() override;

    void Update(float _Delta) override;

    void Render(float _Delta) override;

    // 턴플레이어 넘버
    int StartValue = 0;
    // 턴플레이어 제한시간.
    float TurnPlayTime = 20.0f;

};

