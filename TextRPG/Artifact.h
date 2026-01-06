#pragma once
#include "Item.h"
class Character;
class Artifact : public Item{
public:
    Artifact(std::wstring _name, int _gold, std::wstring _desc, std::vector<std::pair<STATS, int>> _effects);
    void ReCalc(Character& pawn) const ;
    

};

