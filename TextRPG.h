#pragma once
#include "Actor.h"
class TextRPG : public Actor {
public:
    // Actor을(를) 통해 상속됨
    void Tick(float deltaTime) override;
    TextRPG();
};

