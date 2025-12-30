#pragma once
#include <string>
//DO NOT MAKE ON HEAP OR NEW
//USE GM::CreateActor()
class Actor
{
protected:
	std::string name;
	int health;
	int dmg;
	std::wstring ascii;
	bool isDead;

	//이름, 초기 체력, 공격력
public:
	Actor(std::string name, int health, int dmg);
	virtual ~Actor();

public:

	const std::string& GetName() const;
	int GetHealth() const;
	int GetDamage() const;
	void Attack(Actor& target);
	bool IsDead() const;
	virtual void Tick(float deltaTime) = 0;

	virtual void TakeDamage(int damage);
};