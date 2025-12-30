#include "Actor.h"
//HP system, attack, stats

Actor::Actor(std::string name, int health, int dmg) : name(name), health(health), dmg(dmg), isDead(false)
{
}

Actor::~Actor()
{
}

const std::string& Actor::GetName() const
{
	return name;
}

int Actor::GetHealth() const
{
	return health;
}

int Actor::GetDamage() const
{
	return dmg;
}

void Actor::Attack(Actor& target)
{


}

bool Actor::IsDead() const
{
	return isDead;
}

void Actor::TakeDamage(int damage)
{
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