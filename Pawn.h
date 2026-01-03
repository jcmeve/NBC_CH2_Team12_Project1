#pragma once
#include "Actor.h"
#include <string>
#include <vector>
class Pawn : public Actor {
protected:
	int health;
	int dmg;
	float attackSpeed;

	std::vector<std::wstring> ascii;
	bool isDead;
public:
	Pawn(std::wstring name, int health, int dmg, float attackSpeed);
	~Pawn();

	void Init();
	bool LoadAscii(std::wstring fileName);
	int GetHealth() const;
	int GetDamage() const;
	float GetAttackSpeed() const;

	bool IsDead() const;
	bool CanAttack(Pawn* target);
	virtual void Attack(Pawn& pawn);
	virtual void TakeDamage(int damage);

	// Actor을(를) 통해 상속됨
	void Tick(float deltaTime) override;
};

