#pragma once
#include "Widget.h"
#include <string>
#include <memory>

class Pawn;
class StatWidget : public Widget {
private:
    const Pawn* target; //절대 widget이 player보다 오래 존속하면 안됨
public:
    void Tick(float deltaTime) override;
    void SetTarget(const Pawn* pawn);
    StatWidget(std::wstring name);
};

