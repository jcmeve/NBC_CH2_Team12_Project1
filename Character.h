#pragma once
#include "Actor.h"
#include <string>
#include <memory>

class Inventory;

class Character : public Actor
{
private:
	int level;
	int maxHealth;
	int experience;
	int gold;
	std::unique_ptr<Inventory> inventory;

public:
	Character(std::string name);
	~Character();

	void TakeDamage(int damage) override;
	void displayStatus();
	void levelUp();
	void useItem(int index);

	Inventory* getInventory() const;

};