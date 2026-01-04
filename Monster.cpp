#include "Monster.h"
#include "GameManager.h"
#include "Utilities.h"

Monster::Monster(std::wstring name) : Pawn(name, 0, 0, 0, 1.0f) {}
Monster::~Monster() {}

void Monster::Init(int playerLevel)
{
	Pawn::Init();

	int minHP = playerLevel * 20;
	int maxHP = playerLevel * 30;
	this->maxHealth = Utilities::GenerateRandomValue(minHP, maxHP);
	this->health = maxHealth;


	int minDmg = playerLevel * 5;
	int maxDmg = playerLevel * 10;
	this->originDmg = Utilities::GenerateRandomValue(minDmg, maxDmg);
	dmg = originDmg;

	int minDef = playerLevel * 2;
	int maxDef = playerLevel * 5;
	this->originDef = Utilities::GenerateRandomValue(minDef, maxDef);
	def = originDef;

	this->attackSpeed = 60.0f; //나중에 매개변수로 수정
}

int Monster::dropGold()
{
	return Utilities::GenerateRandomValue(10, 20);
}

void Monster::TakeDamage(int damage)
{
	Pawn::TakeDamage(damage);
}

void Monster::Tick(float deltaTime) {
	Pawn::Tick(deltaTime);
}