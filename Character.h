#pragma once
#include "Pawn.h"
#include <string>
#include <memory>
#include <map>

class Inventory;

class Character : public Pawn
{
private:
	int level;
	int maxHealth;
	int experience;
	int gold;
	std::unique_ptr<Inventory> inventory;

	std::map<std::wstring, int> killRecord;

public:
	Character(std::wstring name);
	~Character();
	void Init();

	void TakeDamage(int damage) override;
	void displayStatus();
	void levelUp();
	void useItem(int index);

	int getLevel() const;
	int getExperience() const;
	int getGold() const;

	void addExperience(int exp);
	void addGold(int amount);
	void RemoveGold(int amount);

	void RecordKill(std::wstring monsterName);
	void ShowKillLog();
	virtual void ReCalc() override;

	Inventory* getInventory() const;

	void Tick(float deltaTime) override;


};