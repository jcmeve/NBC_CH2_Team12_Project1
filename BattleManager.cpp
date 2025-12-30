#include "BattleManager.h"
#include "Actor.h"
#include "Monster.h"
#include "Character.h"
bool BattleManager::Enter(Character& player) {
	Monster monster("Monster", 5);
	//    Monster monster(player.GetLevel());
	bool ret = Loop(player, monster);
	if (ret) {
		//Make Item
		//move to Character
	}
	else {
		//character dead animation
		//and sound
		//print message
	}
	return ret;
}

bool BattleManager::Loop(Actor& player, Actor& monster) {
	for (;;) {
		player.Attack(monster);
		if (monster.IsDead())
			return true;

		monster.Attack(player);
		if (player.IsDead())
			return false;
	}
	return false;
}

BattleManager::BattleManager() {
}
