#include "Actor.h"
//HP system, attack, stats

Actor::Actor(std::string name, int health, int attack) : name(name), health(health), attack(attack), isDead(false)
{
}

Actor::~Actor()
{
}

const std::string& Actor::getName() const
{
	return name;
}

int Actor::getHealth() const
{
	return health;
}

int Actor::getAttack() const
{
	return attack;
}

bool Actor::IsDead() const
{
	return isDead;
}

void Actor::takeDamage(int damage)
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