#include "Monster.h"
#include "GameManager.h"
#include <random>

Monster::Monster(std::wstring name) : Pawn(name, 0, 0, 0.5f) {}
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
	health = GenerateRandomValue(minHP, maxHP);

	int minDmg = playerLevel * 5;
	int maxDmg = playerLevel * 10;
	dmg = GenerateRandomValue(minDmg, maxDmg);

	float attackSpeed = 0.5; //나중에 매개변수로 수정

	GM::GetLogger().Log(L"몬스터 초기화 완료!");
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