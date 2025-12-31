#include "Character.h"
#include "Inventory.h"
#include "Item.h"
#include <iostream>

Character::Character(std::wstring name) :
	Pawn(name, 200, 30), level(1), maxHealth(200), experience(0), gold(0)
{
	inventory = std::make_unique<Inventory>();
}

Character::~Character()
{
}

void Character::TakeDamage(int damage)
{
}

void Character::displayStatus()
{
	std::wcout << "============= Player's Status =============" << std::endl;
	std::wcout << "이름: " << name << std::endl;
	std::wcout << "레벨: " << level << ", 현재 경험치: " << experience << "/100" << std::endl;
	std::wcout << "소지 골드: " << gold << std::endl;
	std::wcout << "HP: " << health << "/" << maxHealth << std::endl;
}

void Character::levelUp()
{
	level++;
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

void Character::Tick(float deltaTime) {
}
