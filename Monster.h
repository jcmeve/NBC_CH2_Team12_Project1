#pragma once
#include "Actor.h"
#include <string>

class Monster : public Actor
{
public:
	Monster(std::string name, int playerLevel);
	virtual ~Monster();

	void takeDamage(int damage) override;

private:
	int generateRandomStat(int min, int max);
};