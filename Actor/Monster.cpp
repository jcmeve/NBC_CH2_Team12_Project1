#include "Monster.h"
#include "GameManager.h"
#include "Utilities.h"

Monster::Monster(std::wstring name) : Pawn(name, 0, 0, 0, 1.0f) {}
Monster::~Monster() {}

void Monster::Init(int playerLevel)
{
	Pawn::Init();

	int minHP = playerLevel * 20;
	int maxHP = playerLevel * 30;
	this->maxHealth = Utilities::GenerateRandomValue(minHP, maxHP);
	this->health = maxHealth;


	int minDmg = playerLevel * 5;
	int maxDmg = playerLevel * 10;
	this->originDmg = Utilities::GenerateRandomValue(minDmg, maxDmg);
	dmg = originDmg;

	int minDef = playerLevel * 2;
	int maxDef = playerLevel * 5;
	this->originDef = Utilities::GenerateRandomValue(minDef, maxDef);
	def = originDef;

	this->attackSpeed = 0.4f; //나중에 매개변수로 수정
	qteTimer = (float)Utilities::GenerateRandomValue(0, 9);
	qteTime = 10.0f;
}

bool Monster::LoadAscii(std::wstring fileName) {
	for (EMotion motion : {EMotion::IDLE1, EMotion::IDLE2, EMotion::ATTACK, EMotion::DIE }) {
		std::wstring buf;
		GM::GetSave().LoadAscii(L"Monster\\" + fileName + L"_" + EmotionToString(motion), buf);
		ascii[motion].push_back(buf);
	}
	return true;
}

int Monster::dropGold()
{
	return Utilities::GenerateRandomValue(10, 20);
}

void Monster::TakeDamage(int damage)
{
	Pawn::TakeDamage(damage);
}

bool Monster::CanQTE() const {
	return qteTimer>qteTime;
}

void Monster::ResetQTETimer() {
	qteTimer = 0.0f;
}

void Monster::Tick(float deltaTime) {
	Pawn::Tick(deltaTime);
	qteTimer += deltaTime;

	if (!isVisible) {
		return;
	}

	if (IsDead()) {
		GM::GetDisplay().DrawAscii(ascii[EMotion::DIE][0], posX, posY);
		return;
	}
	if (isAttacking) {
		GM::GetDisplay().DrawAscii(ascii[EMotion::ATTACK][0], posX, posY);
		return;
	}
	
	if (idleMotionIdx == 0) {
		GM::GetDisplay().DrawAscii(ascii[EMotion::IDLE1][0], posX, posY);
	}
	else if (idleMotionIdx == 1) {
		GM::GetDisplay().DrawAscii(ascii[EMotion::IDLE2][0], posX, posY);
	}
	

}