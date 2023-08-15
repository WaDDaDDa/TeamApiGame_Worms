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

    void ChangeTurnPlayer(float _Delta);
    void ChangeTurnPlayer(int _Value);

    static GameTurn MainGameTurn;

    float GetTurnPlayTime() const
    {
        return TurnPlayTime;
    }

    float GetTurnTime()
    {
        return TurnTime;
    }

protected:

private:
    Player* TurnPlayer = nullptr;

    void Start() override;
    void Init();

    void Update(float _Delta) override;

    void Render(float _Delta) override;

    // ���÷��̾� �ѹ�
    int StartValue = 0;
    // ���� �÷��̾� �ѹ�
    int PrevValue = 0;
    // ���÷��̾� ���ѽð�.
    float TurnPlayTime = 20.0f;
    // ���� �ð�
    static float TurnTime;
};

