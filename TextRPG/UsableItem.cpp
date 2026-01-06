#include "UsableItem.h"
#include "Pawn.h"
UsableItem::UsableItem(std::wstring _name, int _gold, std::wstring _desc, int _duration, std::vector<std::pair<STATS, int>> _effects) :Item(_name,_gold,_desc,_effects),duration(_duration){
}
int UsableItem::GetDuration() const {
    return duration;
}
void UsableItem::Use(Pawn& pawn) const{
    pawn.UseItem(name, duration, effects);
}
