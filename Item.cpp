#include "Item.h"
#include "Pawn.h"
Item::Item(std::wstring _name, int _gold, std::wstring _desc, int _turn, std::vector<std::pair<STATS, int>> _effects) :
    name(_name), gold(_gold), description(_desc), turn(_turn), effects(_effects) {

}

Item::~Item() {
}

void Item::Use(Pawn& pawn) {
    pawn.UseItem(name, turn, effects);
}

std::wstring Item::GetName()const {
    return name;
}

int Item::GetPrice() const {
    return gold;
}

