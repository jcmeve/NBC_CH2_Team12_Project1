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
	Pawn(std::wstring name, int health, int dmg);
	~Pawn();
	int GetHealth() const;
	int GetDamage() const;
	virtual void Attack(Pawn& pawn) ;
	bool IsDead() const;
	virtual void TakeDamage(int damage);
};

