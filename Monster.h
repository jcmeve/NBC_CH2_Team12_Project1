#pragma once
#include "Actor.h"
#include <string>

class Monster : public Actor
{
public:
	Monster(std::string name, int playerLevel);
	virtual ~Monster();

void TakeDamage(int damage) override;

private:
	int GenerateRandomStat(int min, int max);
};