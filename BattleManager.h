#pragma once
class Character;
class Monster;
#include"Actor.h"
class BattleManager : public Actor{
    //spawn monster, drop item when player win
    bool Enter(Character& player);
    // Actor을(를) 통해 상속됨
    void Tick(float deltaTime) override;
    BattleManager();
};

