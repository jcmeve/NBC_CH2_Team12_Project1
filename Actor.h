#pragma once
#include <string>

class Actor
{
protected:
	std::string name;
	int health;
	int dmg;
	std::wstring ascii;
	bool isDead;
	
public:
	//이름, 초기 체력, 공격력
	Actor(std::string name, int health, int dmg);
	virtual ~Actor();

	const std::string& getName() const;
	int getHealth() const;
	int gettAttack() const;
	void Attack(Actor& target);
	bool isDead() const;

	virtual void takeDamage(int damage);
};