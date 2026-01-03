#include "Item.h"
#include "Pawn.h"
Item::Item(std::wstring _name, int _gold, std::wstring _desc, int _turn, std::vector<std::pair<STATS, int>> _effects) :
    name(_name),gold(_gold), description(_desc), turn(_turn), effects(_effects)
{

}

Item::~Item() {
}

void Item::Use(Pawn& pawn) {
    int hp, atk, def;
    for (auto pair : effects) {
        switch (pair.first)
        {
        case STATS::HP:
            hp = pair.second;
            break;
        case STATS::ATK:
            atk = pair.second;
            break;
        case STATS::DEF:
            def = pair.second;
            break;
        default:
            break;
        }
    }
    pawn.UseItem(name, turn, hp, atk, def);
}

std::wstring Item::GetName() {
    return std::wstring();
}

