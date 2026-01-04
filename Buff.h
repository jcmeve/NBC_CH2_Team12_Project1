#pragma once
#include <string>
#include <vector>
#include "Enums.h"
class Pawn;
class Buff {
private:
    float duration;
    float timer = 0.0f;

    Pawn* target;
    std::wstring name;
    std::vector<std::pair<STATS, int>> effects;//stat, amount

public:
    Buff(Pawn* pawn, std::wstring _name, int _duration, std::vector<std::pair<STATS, int>>& _effects);
    void Enter();
    void ReCalc();
    void Update(float deltaTime);//Time
    void Exit();

};

