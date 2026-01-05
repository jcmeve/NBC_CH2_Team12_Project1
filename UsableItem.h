#pragma once
#include "Item.h"
class UsableItem : public Item {
private:
    int duration;
public:
    UsableItem(std::wstring _name, int _gold, std::wstring _desc, int _duration, std::vector<std::pair<STATS, int>> _effects);
    int GetDuration()const;
    void Use(Pawn& pawn) const;
};

