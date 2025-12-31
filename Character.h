#pragma once
#include "Pawn.h"
#include <string>
#include <memory>

class Inventory;

class Character : public Pawn
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

	void Init() override;

	void TakeDamage(int damage) override;
	void displayStatus();
	void levelUp();
	void useItem(int index);

	Inventory* getInventory() const;


	// Actor을(를) 통해 상속됨
	void Tick(float deltaTime) override;

};