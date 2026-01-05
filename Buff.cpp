#include "Buff.h"
#include "Pawn.h"
Buff::Buff(Pawn* pawn, std::wstring _name, int _duration, std::vector<std::pair<STATS, int>>& _effects) :target(pawn), name(_name), duration(_duration), effects(_effects) {
}

void Buff::Enter() {
	timer = 0.0f;
	ReCalc();
}

void Buff::ReCalc() {
	int hp = 0, dmg = 0, def = 0;
	for (auto pair : effects) {
		switch (pair.first)
		{
		case STATS::HP:
			hp = pair.second;
			hpGen = pair.second;
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
	target->IncreaseStats(hp, dmg, def);
}



void Buff::Update(float deltaTime) {
	timer += deltaTime;
	if (timer > duration) {
		Exit();
		return;
	}
	target->Heal(deltaTime * hpGen);
}

void Buff::Exit() {
	target->RemoveBuff(this);
	delete this;
}