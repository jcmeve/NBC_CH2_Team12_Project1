#pragma once
#include "Actor.h"
#include <string>
#include <vector>

class Item;

class Character : public Actor
{
private:
	static Character* instance;

	int level;
	int maxHealth;
	int experience;
	int gold;
	std::vector<Item*> inventory;

	Character(std::string name);

public:
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;

	static Character* getInstance(std::string name = "");

	void takeDamage(int damage) override;
	void displayStatus();
	void levelUp();
	void useItem(int index);
};

