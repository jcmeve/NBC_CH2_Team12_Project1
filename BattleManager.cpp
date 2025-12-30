#include "BattleManager.h"
#include "Actor.h"
#include "Monster.h"
#include "Character.h"

bool BattleManager::Enter(Character& player) {
    return false;
}

void BattleManager::Tick(float deltaTime) {


}


BattleManager::BattleManager():Actor("BattlleManager") {}
