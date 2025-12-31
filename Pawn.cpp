#include "Pawn.h"
#include "GameManager.h"
Pawn::Pawn(std::wstring name, int health, int dmg) : Actor(name), health(health), dmg(dmg), isDead(false) {
}

Pawn::~Pawn() {

}

void Pawn::Init()
{
	isDead = false;
}

int Pawn::GetHealth() const {
	return health;
}

int Pawn::GetDamage() const {
	return dmg;
}

void Pawn::Attack(Pawn& target) {
	
	target.TakeDamage(GetDamage());
	GM::GetDisplay().WriteString(GetName() + L" -> " + target.GetName());
}

bool Pawn::IsDead() const {
	return isDead;
}


void Pawn::TakeDamage(int damage) {
	if (isDead)
	{
		return;
	}

	health -= damage;

	if (health <= 0)
	{
		health = 0;
		isDead = true;
	}
}