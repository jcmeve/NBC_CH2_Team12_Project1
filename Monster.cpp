#include "Monster.h"
#include <random>

int Monster::GenerateRandomStat(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

Monster::Monster(std::string name, int playerLevel) : Actor(name, 0, 0)
{
	int minHP = playerLevel * 20;
	int maxHP = playerLevel * 30;
	health = generateRandomStat(minHP, maxHP);

	int minDmg = playerLevel * 5;
	int maxDmg = playerLevel * 10;
	dmg = generateRandomStat(minDmg, maxDmg);
}

Monster::~Monster()
{

}

void Monster::TakeDamage(int damage)
{
}