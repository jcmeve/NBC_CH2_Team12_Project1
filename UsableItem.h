#pragma once
#include "Item.h"
class UsableItem : public Item {
private:
    int turn;
public:
    UsableItem(std::wstring _name, int _gold, std::wstring _desc, int _turn, std::vector<std::pair<STATS, int>> _effects);

    void Use(Pawn& pawn) const;
};

