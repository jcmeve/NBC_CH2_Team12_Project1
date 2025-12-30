#include "Item.h"
Item::Item() {
}

Item::~Item() {
}

void Item::Use(Actor& actor) {
}

std::wstring Item::GetName() {
    return std::wstring();
}

HealingPotion::HealingPotion(int _amount) {
}

void HealingPotion::Use(Actor& actor) {
}

DamageIncreasePotion::DamageIncreasePotion(int _amount) {
}

void DamageIncreasePotion::Use(Actor& actor) {
}
