#include "Monster.h"
#include "GameManager.h"
#include <random>

Monster::Monster(std::wstring name) : Pawn(name, 0, 0, 0, 1.0f) {}
Monster::~Monster() {}

int Monster::GenerateRandomValue(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

void Monster::Init(int playerLevel)
{
	Pawn::Init();

	int minHP = playerLevel * 20;
	int maxHP = playerLevel * 30;
	this->health = GenerateRandomValue(minHP, maxHP);

	int minDmg = playerLevel * 5;
	int maxDmg = playerLevel * 10;
	this->dmg = GenerateRandomValue(minDmg, maxDmg);

	int minDef = playerLevel * 2;
	int maxDef = playerLevel * 5;
	this->def = GenerateRandomValue(minDef, maxDef);

	this->attackSpeed = 60.0f; //나중에 매개변수로 수정
}

int Monster::dropGold()
{
	return GenerateRandomValue(10, 20);
}

void Monster::TakeDamage(int damage)
{
	Pawn::TakeDamage(damage);
}

void Monster::Tick(float deltaTime) {}