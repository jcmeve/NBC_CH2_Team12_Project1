#pragma once
#include "Actor.h"
#include <string>

class Monster : public Actor
{
public:
	//몬스터 스탯 계산
	Monster(std::string name, int playerLevel);
	virtual ~Monster();

	void takeDamage(int damage) override;
};