#pragma once
#include "Actor.h"
#include <string>
class Character;
class QTE : public Actor {
private:
    float limitTime;
    float currTime;
    Character* qteTarget;
    bool fail = false;
    bool isEnd = false;
    
    const short posX = 100;
    const short posY = 30;
    const short circleWidth = 15;
    const short circleHeight = 10;
    
public:
    QTE(const std::wstring& name);
    // Actor을(를) 통해 상속됨
    void Tick(float deltaTime) override;
    void DrawQTE();
    void Init(Character* target, float time);
    //Character포인터 직접 가지고 있는데 이벤트로 변경해야함
};

