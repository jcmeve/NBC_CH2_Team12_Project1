#include "Pawn.h"
Pawn::Pawn(std::string name, int health, int dmg) : Actor(name), health(health), dmg(dmg), isDead(false) {
}

Pawn::~Pawn() {

}



int Pawn::GetHealth() const {
	return health;
}

int Pawn::GetDamage() const {
	return dmg;
}

void Pawn::Attack(Pawn& target) {


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