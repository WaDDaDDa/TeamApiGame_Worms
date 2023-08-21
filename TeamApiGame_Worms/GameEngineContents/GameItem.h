#pragma once
#include "GravityActor.h"

class GameItem : public GravityActor
{
public:
    GameItem();
    ~GameItem();

    GameItem(const GameItem& _Other) = delete;
    GameItem(GameItem&& _Other) noexcept = delete;
    GameItem& operator=(const GameItem& _Other) = delete;
    GameItem& operator=(GameItem&& _Other) noexcept = delete;

protected:

private:


};

