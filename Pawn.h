#pragma once
#include "Actor.h"
#include "Enums.h"
#include <string>
#include <vector>
class Buff;
class Pawn : public Actor {
protected:
	int health;
	int maxHealth;
	int originDmg;
	int originDef;
	int dmg;
	int def;
	float attackSpeed;

	std::vector<std::wstring> ascii;
	bool isDead;

	short posX;
	short posY;
	bool isReverse;

	std::vector<Buff*> buffs;

public:
	Pawn(std::wstring name, int health, int dmg, int def, float attackSpeed);
	~Pawn();

	void Init();
	bool LoadAscii(std::wstring fileName);
	int GetHealth() const;
	int GetDamage() const;
	int GetDefence() const;
	int GetMaxHealth() const;
	int GetOriginDamage() const;
	int GetOriginDefence() const;
	float GetAttackSpeed() const;

	bool IsDead() const;
	bool CanAttack(Pawn* target);
	virtual void Attack(Pawn& pawn);
	virtual void TakeDamage(int damage);
	void UseItem(std::wstring _name, int _turn, const std::vector<std::pair<STATS, int>>& _effects);

	void AddBuff(std::wstring _name, int _duration, const std::vector<std::pair<STATS, int>>& _effects);
	void ClearBuff();
	void RemoveBuff(Buff* buff);
	void IncreaseStats(int _maxHp, int _dmg, int _def);
	void Heal(int amount);
	virtual void ReCalc();
	
	void SetPos(short x, short y, bool reverse);

	// Actor을(를) 통해 상속됨
	void Tick(float deltaTime) override;
};

