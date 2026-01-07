#pragma once
#include "Pawn.h"
#include <string>
#include <memory>
#include <map>

class Inventory;
class Equipment;
class Character : public Pawn
{
private:
	int level;
	int experience;
	int gold;
	std::unique_ptr<Inventory> inventory;
	std::vector<const Equipment*> equipmentSlot;
	const static int equipmentSlotSize = 5;

	std::map<std::wstring, int> killRecord;

public:
	Character(std::wstring name);
	~Character();
	void Init();
	bool LoadAscii(std::wstring fileName)override;


	void TakeDamage(int damage) override;
	void displayStatus();
	void levelUp();
	bool TryUseRandomItem();

	int getLevel() const;
	int getExperience() const;
	int getGold() const;

	bool addExperience(int exp);
	void addGold(int amount);
	void RemoveGold(int amount);

	void PlayAudio(EAction action) override;

	std::wstring GetKillLogText() const;
	void RecordKill(std::wstring monsterName);
	void ShowKillLog();
	virtual void ReCalc() override;

	bool Equip(const Equipment* equipment);
	void Unequip(int idx);
	const Equipment* GetCurrentEquipment(int idx);
	int GetCurrentEquipmentSize();

	Inventory* getInventory() const;

	void Tick(float deltaTime) override;


};