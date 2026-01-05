#pragma once
#include "Actor.h"
#include "Enums.h"
#include <string>
#include <vector>
#include <map>
class Buff;



class Pawn : public Actor {
protected:
	enum class EMotion {
		IDLE1, IDLE2, ATTACK, DIE, DEFENSE
	};
	std::wstring EmotionToString(EMotion motion);
	int health;
	int maxHealth;
	int originDmg;
	int originDef;
	int dmg;
	int def;
	float attackSpeed;
	float attackTimer = 0.0f;
	bool isAttacking = false;

	std::map< EMotion, std::vector<std::wstring>> ascii;
	const float idleMotionPeriod = 0.5f;
	float idleMotionTimer;
	int idleMotionIdx;
	
	bool isDead;

	short posX;
	short posY;
	bool isReverse;

	std::vector<Buff*> buffs;

public:
	Pawn(std::wstring name, int health, int dmg, int def, float attackSpeed);
	~Pawn();

	void Init();
	virtual bool LoadAscii(std::wstring fileName) = 0;
	int GetHealth() const;
	int GetDamage() const;
	int GetDefence() const;
	int GetMaxHealth() const;
	int GetOriginDamage() const;
	int GetOriginDefence() const;
	float GetAttackSpeed() const;

	void InitAttackTimer();

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

