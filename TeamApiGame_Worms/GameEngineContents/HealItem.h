#pragma once
#include "GameItem.h"

enum class HealItemState
{
    Create,
    Idle,
    Fly,
    Col,
    Max,
};

class HealItem : public GameItem
{
public:
    HealItem();
    ~HealItem();

    HealItem(const HealItem& _Other) = delete;
    HealItem(HealItem&& _Other) noexcept = delete;
    HealItem& operator=(const HealItem& _Other) = delete;
    HealItem& operator=(HealItem&& _Other) noexcept = delete;

    HealItemState GetState()
    {
        return State;
    }

protected:
    void ChangeState(HealItemState _State);
    void StateUpdate(float _Delta);

    void CreateStart();
    void CreateUpdate(float _Delta);
    void FlyStart();
    void FlyUpdate(float _Delta);
    void IdleStart();
    void IdleUpdate(float _Delta);
    void ColStart();
    void ColUpdate(float _Delta);
    void MaxStart();
    void MaxUpdate(float _Delta);

private:
    class GameEngineRenderer* Renderer = nullptr;
    class GameEngineCollision* BodyCollision = nullptr;

    HealItemState State = HealItemState::Max;

    bool AniSwitch = true;

    void Start() override;
    void LevelStart() override;
    void Update(float _Delta) override;
};

