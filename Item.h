#pragma once
#include <string>
#include <vector>
#include "Enums.h"
class Pawn;

class Item {
public:
    //name, gold, desc, turn, effects
    Item(std::wstring _name, int _gold, std::wstring _desc, std::vector<std::pair<STATS, int>> _effects);
    virtual ~Item();
    std::wstring GetName() const ;
    int GetPrice()const;
protected:
    std::wstring name;
    int gold;
    std::wstring description;
    std::vector<std::pair<STATS, int>> effects;//stat, amount

        
    //이름, 골드, 설명, 턴, HP 숫자, ATK 숫자, DEF 숫자
};

struct ItemPointerCompare {
    bool operator()(const Item* a, const Item* b) const {
        return a->GetName() < b->GetName();
    }
};