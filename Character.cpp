#include "Character.h"
#include "Inventory.h"
#include "Item.h"
#include "GameManager.h"
#include <iostream>

Character::Character(std::wstring name) :
	Pawn(name, 0, 0), level(1), maxHealth(200), experience(0), gold(0)
{
}

Character::~Character()
{
}

void Character::Init()
{
	Pawn::Init();
	this->level = 1;
	this->maxHealth = 200;
	this->health = maxHealth;
	this->dmg = 30;
	this->experience = 0;
	this->gold = 0;

	this->inventory = std::make_unique<Inventory>();

	GM::GetLogger().Log(L"플레이어 초기화 완료!");
}

void Character::TakeDamage(int damage)
{
	Pawn::TakeDamage(damage);
}

void Character::displayStatus()
{

	std::wstring wName(name.begin(), name.end());

	Logger& logger = GM::GetLogger();
	logger.Log(L"=============== Player's Status ===============");
	logger.Log(L"이름: " + wName);

	std::wstring levelStr = L"레벨: " + std::to_wstring(level) + L" | 경험치: " + std::to_wstring(experience) + L"/100";
	logger.Log(levelStr);

	std::wstring hpStr = L"현재 체력: " + std::to_wstring(health) + L"/" + std::to_wstring(maxHealth);
	logger.Log(hpStr);

	std::wstring goldStr = L"소지 골드: " + std::to_wstring(gold);
	logger.Log(goldStr);

}

void Character::levelUp()
{
	if (level < 10)
	{
		level++;
		maxHealth += level * 20;
		dmg += level * 5;
		health = maxHealth;
	}
}

void Character::useItem(int index)
{
	//1. Item* itemToUse = inventory->getItem(index)
	//2. itemToUse->use(this)
	//3. inventory->removeItem(index)
}

Inventory* Character::getInventory() const
{
	return inventory.get();
}

int Character::getLevel() const
{
	return level;
}

int Character::getExperience() const
{
	return experience;
}

int Character::getGold() const
{
	return gold;
}

void Character::addExperience(int exp)
{
	experience += exp;
	GM::GetLogger().Log(L"경험치 +" + std::to_wstring(exp) + L" 획득! (현재: " + std::to_wstring(experience) + L"/100)");

	while (experience >= 100 && level < 10)
	{
		experience -= 100;
		levelUp();
		GM::GetLogger().Log(L"레벨 업! 현재 레벨: " + std::to_wstring(level));
	}
}

void Character::addGold(int amount)
{
	gold += amount;
}

void Character::Tick(float deltaTime) {
	Pawn::Tick(deltaTime);
}
