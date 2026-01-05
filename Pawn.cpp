#include "Pawn.h"
#include "GameManager.h"
#include "Buff.h"
std::wstring Pawn::EmotionToString(EMotion motion) {
	switch (motion)
	{
	case Pawn::EMotion::IDLE1:
		return L"Idle1";
	case Pawn::EMotion::IDLE2:
		return L"Idle2";
	case Pawn::EMotion::ATTACK:
		return L"Attack";
	case Pawn::EMotion::DIE:
		return L"Die";
	case Pawn::EMotion::DEFENSE:
		return L"Defense";
	default:
		break;
	}
	return std::wstring();
}
Pawn::Pawn(std::wstring name, int health, int dmg, int def, float attackSpeed) :
	Actor(name), maxHealth(health), health(health), originDmg(dmg), dmg(dmg), originDef(def), def(def), attackSpeed(attackSpeed), isDead(false) {
}

Pawn::~Pawn() {

}

void Pawn::Init()
{
	LoadAscii(name);
	isDead = false;
}


int Pawn::GetHealth() const {
	return health;
}

int Pawn::GetDamage() const {
	return dmg;
}

int Pawn::GetDefence() const {
	return def;
}

int Pawn::GetMaxHealth() const {
	return maxHealth;
}

int Pawn::GetOriginDamage() const {
	return originDmg;
}

int Pawn::GetOriginDefence() const {
	return originDef;
}

float Pawn::GetAttackSpeed() const
{
	return attackSpeed;
}

void Pawn::InitAttackTimer() {
	attackTimer = 0.0f;
}

void Pawn::Attack(Pawn& target) {
	isAttacking = true;
	target.TakeDamage(GetDamage());
	GM::GetDisplay().WriteString(GetName() + L" -> " + target.GetName());
	attackTimer = 0.0f;
}

bool Pawn::IsDead() const {
	return isDead;
}

bool Pawn::CanAttack(Pawn* target)
{
	if (!target || target->IsDead() || IsDead())
	{
		return false;
	}
	if (attackTimer > 1.0f) {
		return true;
	}
	return false;
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

void Pawn::UseItem(std::wstring _name, int _turn, const std::vector<std::pair<STATS, int>>& _effects) {
	//GM::GetLogger().Log(name + L"을 사용했습니다");
	if (_turn == 0) {
		int hp = 0, dmg = 0, def = 0;
		std::vector<std::pair<STATS, int>> effects{ _effects };
		//아이템 설계 이슈로 쩔수 없이 값복사함
		for (auto& pair : effects) {
			switch (pair.first)
			{
			case STATS::HP:
				hp = pair.second;
				pair.second = 0;
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
		AddBuff(_name, MAXINT, effects);
	}
	else {//buff
		AddBuff(_name, _turn, _effects);
	}

}

void Pawn::AddBuff(std::wstring _name, int _duration, const std::vector<std::pair<STATS, int>>& _effects) {
	buffs.push_back(new Buff(this, _name, _duration, _effects));
	ReCalc();
}

void Pawn::ClearBuff() {
	for (int i = 0; i < buffs.size(); ++i) {
		buffs[i]->Exit();
	}
	buffs.clear();
	ReCalc();
}

void Pawn::RemoveBuff(Buff* buff) {
	for (int i = 0; i < buffs.size(); ++i) {
		if (buffs[i] == buff) {
			buffs.erase(std::remove(buffs.begin(), buffs.end(), buff), buffs.end());
			break;
		}
	}
	ReCalc();
}

void Pawn::IncreaseStats(int _maxHp, int _dmg, int _def) {
	maxHealth += _maxHp;
	dmg += _dmg;
	def += _def;
}

void Pawn::Heal(int amount) {
	health += amount;
	if (health > maxHealth)
	{
		health = maxHealth;
	}
}

void Pawn::ReCalc() {
	dmg = originDmg;
	def = originDef;

	for (Buff* buff : buffs) {
		buff->ReCalc();
	}

}


void Pawn::SetPos(short x, short y, bool reverse) {
	posX = x;
	posY = y;
	isReverse = reverse;
}

void Pawn::Tick(float deltaTime) {
	//버프 업데이트
	for (int i = buffs.size() - 1; i >= 0; i--)
	{
		buffs[i]->Update(deltaTime); //Update에서 버프를 지우므로 뒤에서부터 순회
	}

	attackTimer += deltaTime*attackSpeed;
	if (attackTimer > 1.0 / attackSpeed * 0.1) {
		isAttacking = false;
	}

	idleMotionTimer += deltaTime;
	if (idleMotionTimer > idleMotionPeriod) {
		idleMotionTimer = 0.0f;
		idleMotionIdx = (idleMotionIdx + 1) % 2;

	}

	//ATTACK,DIE
}
