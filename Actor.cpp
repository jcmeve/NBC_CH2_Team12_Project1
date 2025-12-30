#include "Actor.h"
#include "GameManager.h"
//HP system, attack, stats

Actor::Actor(std::string name) {
}

Actor::~Actor() {
}

const std::string& Actor::GetName() const {
	return name;
}