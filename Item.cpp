#include "Item.h"
#include "Character.h"
Item::Item() {
}

Item::~Item() {
}

void Item::Use(Actor& actor) {
}

std::wstring Item::GetName() {
    return std::wstring();
}

HealingPotion::HealingPotion(int _amount) 
{
    amount = _amount;
}

void HealingPotion::Use(Actor& actor) 
{
    Character* character = dynamic_cast <Character*>(&actor);
        if (character) {
            character->heal(amount);
        }
}

DamageIncreasePotion::DamageIncreasePotion(int _amount) 
{
    amount = _amount;
}

void DamageIncreasePotion::Use(Actor& actor) 
{
    Character* character = dynamic_cast <Character*>(&actor);
    if (character) {
        character->IncreaseDamagePotion(amount);
    }
}
