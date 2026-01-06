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
	for (EAction action : {EAction::IDLE1, EAction::IDLE2, EAction::ATTACK, EAction::DIE }) {
		std::wstring buf;
		GM::GetSave().LoadAscii(L"Monster\\" + fileName + L"_" + EActionToString(action), buf);
		ascii[action].push_back(buf);
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
		GM::GetDisplay().DrawAscii(ascii[EAction::DIE][0], posX, posY);
		return;
	}
	if (isAttacking) {
		GM::GetDisplay().DrawAscii(ascii[EAction::ATTACK][0], posX, posY);
		return;
	}
	
	if (idleMotionIdx == 0) {
		GM::GetDisplay().DrawAscii(ascii[EAction::IDLE1][0], posX, posY);
	}
	else if (idleMotionIdx == 1) {
		GM::GetDisplay().DrawAscii(ascii[EAction::IDLE2][0], posX, posY);
	}
	

}

void Monster::PlayAudio(EAction action) {
	if (action == EAction::ATTACK || action == EAction::HIT) {
		GM::GetSound().PlayAudio(GetName() + L"_" + EActionToString(action) + std::to_wstring(Utilities::GenerateRandomValue(1, 2)));
	}
	else if(action == EAction::DIE){
		GM::GetSound().PlayAudio(GetName() + L"_" + EActionToString(action));
	}
}