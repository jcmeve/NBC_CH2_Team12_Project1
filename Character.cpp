#include "Character.h"
#include "Inventory.h"
#include "Item.h"
#include <iostream>

Character::Character(std::string name) :
	Actor(name, 200, 30), level(1), maxHealth(200), experience(0), gold(0)
{
	inventory = std::make_unique<Inventory>();
}

Character::~Character()
{
}

void Character::takeDamage(int damage)
{
}

void Character::displayStatus()
{
	std::cout << "============= Player's Status =============" << std::endl;
	std::cout << "이름: " << name << std::endl;
	std::cout << "레벨: " << level << ", 현재 경험치: " << experience << "/100" << std::endl;
	std::cout << "소지 골드: " << gold << std::endl;
	std::cout << "HP: " << health << "/" << maxHealth << std::endl;
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

void Character::heal(int amount)
{
	health += amount;
}

void Character::IncreasePotion(int amount)
{
	dmg += amount;
}