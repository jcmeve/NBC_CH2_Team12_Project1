#include "Pawn.h"
#include "GameManager.h"
Pawn::Pawn(std::wstring name, int health, int dmg, int def, float attackSpeed) :
	Actor(name), health(health), dmg(dmg), def(def), attackSpeed(attackSpeed), isDead(false) {
}

Pawn::~Pawn() {

}

void Pawn::Init()
{
	ascii.resize(3);
	LoadAscii(L"");
	isDead = false;
}

bool Pawn::LoadAscii(std::wstring fileName) {
	return GM::GetSave().LoadAscii(L"001", ascii[0]);
}

int Pawn::GetHealth() const {
	return health;
}

int Pawn::GetDamage() const {
	return dmg;
}

float Pawn::GetAttackSpeed() const
{
	return attackSpeed;
}

void Pawn::Attack(Pawn& target) {

	target.TakeDamage(GetDamage());
	GM::GetDisplay().WriteString(GetName() + L" -> " + target.GetName());
}

bool Pawn::IsDead() const {
	return isDead;
}

bool Pawn::CanAttack(Pawn* target)
{
	if (!target || target->IsDead())
	{
		return false;
	}

	return true;
}

void Pawn::TakeDamage(int damage) {
	if (isDead)
	{
		return;
	}

	float damageMultiplier = 100.0f / (100.0f + (float)def);
	int finalDamage = (int)(damage * damageMultiplier);

	if (finalDamage < 1) // 최소 데미지 1
	{
		finalDamage = 1;
	}

	health -= finalDamage;

	if (health <= 0)
	{
		health = 0;
		isDead = true;
	}
}

void Pawn::UseItem(std::wstring _name, int _turn, int _hp, int _dmg, int _def) {
	//GM::GetLogger().Log(name + L"을 사용했습니다");
	if (_turn == 1) {
		health += _hp;
		if (health > maxHealth) {
			health = maxHealth;
		}
		dmg += _dmg;
		//def+=_def;
	}
	else {//buff

	}

}

void Pawn::ReCalc() {
	dmg = originDmg;
	//TODO
	//for (auto buff : buffes) {
	//	
	//}
}

void Pawn::Tick(float deltaTime) {
	//애니메이션 재생 필요
	//GM::GetDisplay().DrawActor()
	GM::GetDisplay().DrawAscii(ascii[0]);
}
