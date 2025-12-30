#pragma once
#include "Actor.h"
#include <string>
class Pawn : public Actor {
protected:
	int health;
	int dmg;
	std::wstring ascii;
	bool isDead;
public:
	Pawn(std::string name, int health, int dmg);
	~Pawn();
	int GetHealth() const;
	int GetDamage() const;
	void Attack(Pawn& pawn);
	bool IsDead() const;
	virtual void TakeDamage(int damage);
};

