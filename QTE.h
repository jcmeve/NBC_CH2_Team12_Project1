#pragma once
#include "Actor.h"
class Character;
class QTE : public Actor {
private:
    float limitTime;
    float currTime;
    Character* qteTarget;
    bool fail = false;
public:

    // Actor을(를) 통해 상속됨
    void Tick(float deltaTime) override;
    void Init(Character* target, float time);
    //Character포인터 직접 가지고 있는데 이벤트로 변경해야함
};

