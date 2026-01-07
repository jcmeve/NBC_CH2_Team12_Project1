#include "Equipment.h"
#include "Character.h"
#include "Enums.h"

Equipment::Equipment(std::wstring _name, int _gold, std::wstring _desc, std::vector<std::pair<STATS, int>> _effects) :Item(_name, _gold, _desc, _effects) {
}
void Equipment::ReCalc(Character& character) const {
    int hp = 0, dmg = 0, def = 0;
    for (const auto& pair : effects) {
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

    character.IncreaseStats(hp, dmg, def);
}
