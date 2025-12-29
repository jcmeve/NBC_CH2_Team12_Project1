#pragma once
#include "Actor.h"
#include <string>

class Monster : public Actor
{
public:
	Monster(int playerLevel);
	virtual ~Monster();

	void takeDamage(int damage) override;
};