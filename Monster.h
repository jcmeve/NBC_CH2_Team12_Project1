#pragma once
#include "Pawn.h"
#include <string>

class Monster : public Pawn
{
public:
	Monster(std::string name, int playerLevel);
	virtual ~Monster();

	void TakeDamage(int damage) override;

private:
	int GenerateRandomStat(int min, int max);

	// Actor을(를) 통해 상속됨
	void Tick(float deltaTime) override;
};