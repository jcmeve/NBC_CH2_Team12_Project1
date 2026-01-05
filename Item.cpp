#include "Item.h"
#include "Pawn.h"
Item::Item(std::wstring _name, int _gold, std::wstring _desc, std::vector<std::pair<STATS, int>> _effects) :
    name(_name), gold(_gold), description(_desc), effects(_effects) {

}

Item::~Item() {
}



std::wstring Item::GetName()const {
    return name;
}

int Item::GetPrice() const {
    return gold;
}

