#include "Boss.h"
#include "Utilities.h"
Boss::Boss(std::wstring name) :Monster(name){

}
Boss::~Boss() {}

void Boss::Init(int playerLevel) {
    Pawn::Init();
	int minHP = playerLevel * 30;
	int maxHP = playerLevel * 45;
	this->maxHealth = Utilities::GenerateRandomValue(minHP, maxHP);
	this->health = maxHealth;


	int minDmg = playerLevel * 8;
	int maxDmg = playerLevel * 15;
	this->originDmg = Utilities::GenerateRandomValue(minDmg, maxDmg);
	dmg = originDmg;

	int minDef = playerLevel * 3;
	int maxDef = playerLevel * 8;
	this->originDef = Utilities::GenerateRandomValue(minDef, maxDef);
	def = originDef;

	this->attackSpeed = 0.7f; //나중에 매개변수로 수정
	
	qteTimer = (float)Utilities::GenerateRandomValue(0, 9);
	qteTime = 10.0f;
}
