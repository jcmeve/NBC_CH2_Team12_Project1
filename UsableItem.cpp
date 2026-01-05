#include "UsableItem.h"
#include "Pawn.h"
UsableItem::UsableItem(std::wstring _name, int _gold, std::wstring _desc, int _turn, std::vector<std::pair<STATS, int>> _effects) :Item(_name,_gold,_desc,_effects),turn(_turn){
}
void UsableItem::Use(Pawn& pawn) const{
    pawn.UseItem(name, turn, effects);
}
