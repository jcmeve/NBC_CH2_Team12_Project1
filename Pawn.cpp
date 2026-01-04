#include "Pawn.h"
#include "GameManager.h"
#include "Buff.h"
Pawn::Pawn(std::wstring name, int health, int dmg, int def, float attackSpeed) :
	Actor(name), maxHealth(health), health(health), originDmg(dmg), dmg(dmg), originDef(def), def(def), attackSpeed(attackSpeed), isDead(false) {
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

void Pawn::UseItem(std::wstring _name, int _turn, std::vector<std::pair<STATS, int>>& _effects) {
	//GM::GetLogger().Log(name + L"을 사용했습니다");
	if (_turn == 0) {
		int hp = 0, dmg = 0, def = 0;
		for (const auto& pair : _effects) {
			switch (pair.first)
			{
			case STATS::HP:
				hp = pair.second;
				break;
			case STATS::ATK:
				dmg = pair.second;
				break;
			case STATS::DEF:
				def = pair.second;
				break;
			default:
				break;
			}
		}
		Heal(hp);
		dmg += dmg;
		def += def;
	}
	else {//buff
		AddBuff(_name, _turn, _effects);
	}

}

void Pawn::AddBuff(std::wstring _name, int _duration, std::vector<std::pair<STATS, int>>& _effects) {
	buffs.push_back(new Buff(this, _name, _duration, _effects));
}

void Pawn::RemoveBuff(Buff* buff) {
	for (int i = 0; i < buffs.size(); ++i) {
		if (buffs[i] == buff) {
			buffs.erase(std::remove(buffs.begin(), buffs.end(), buff), buffs.end());
			break;
		}
	}
}

void Pawn::IncreaseStats(int _maxHp, int _dmg, int _def) {
	maxHealth += _maxHp;
	dmg += _dmg;
	def += _def;
}

void Pawn::Heal(int amount) {
}

void Pawn::ReCalc() {
	dmg = originDmg;
	//TODO
	//for (auto buff : buffes) {
	//	buff.ReCalc();
	//}
}


void Pawn::SetPos(short x, short y, bool reverse) {
	posX = x;
	posY = y;
	isReverse = reverse;
}

void Pawn::Tick(float deltaTime) {
	//애니메이션 재생 필요
	//GM::GetDisplay().DrawActor()
	GM::GetDisplay().DrawAscii(ascii[0], posX, posY);
}
