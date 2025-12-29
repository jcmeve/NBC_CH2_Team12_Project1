#pragma once
#include <string>

class Actor
{
protected:
	std::string name;
	int health;
	int attack;

public:
	Actor(std::string name, int health, int attack);
	virtual ~Actor();

	std::string getName() const;
	int getHealth() const;
	int gettAttack() const;

	virtual void takeDamage(int damage);
};

