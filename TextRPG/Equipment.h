#pragma once
#include "Item.h"
class Character;
class Equipment : public Item {
public:
    Equipment(std::wstring _name, int _gold, std::wstring _desc, std::vector<std::pair<STATS, int>> _effects);
    void ReCalc(Character& pawn) const;

};

