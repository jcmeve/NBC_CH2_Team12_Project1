#pragma once
class Character;
class Monster;
class Actor;
class BattleManager {
    //spawn monster, drop item when player win
    bool Enter(Character& player);
    bool Loop(Actor& player, Actor& monster);
        

private:
    BattleManager();
    BattleManager& operator=(const BattleManager& other) = delete;
    BattleManager(const BattleManager& other) = delete;
    BattleManager& operator=(const BattleManager&& other) = delete;
    BattleManager(const BattleManager&& other) = delete;
    friend class GameManager;

};

