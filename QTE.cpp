#include "QTE.h"
#include "GameManager.h"
void QTE::Tick(float deltaTime) {
    currTime += deltaTime;
    if (fail) {
        //실패한 경우 시각적인 효과를 위해 바로 없어지지 않음

    }
    if (currTime >= limitTime) {
        //QTE FAIL
        fail = true;
    }
    if (GM::GetInput().IsKeyDown(VK_SPACE)) {
        //QTE SUCCESS
    }
}

void QTE::Init(Character* target, float time) {
    qteTarget = target;
    limitTime = time;
    currTime = 0;
    fail = false;
}
