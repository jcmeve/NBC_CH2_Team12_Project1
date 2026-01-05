#include "Actor.h"
#include "GameManager.h"
//HP system, attack, stats

Actor::Actor(std::wstring name) :name(name){
}

Actor::~Actor() {
}


const std::wstring& Actor::GetName() const {
	return name;
}

void Actor::SetName(const std::wstring& _name) {
	name = _name;
}
