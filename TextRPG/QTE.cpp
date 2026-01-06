#include "QTE.h"
#define _USE_MATH_DEFINES
#include "GameManager.h"
#include "Character.h"
#include <vector>

#include <cmath>
#include "Enums.h"
QTE::QTE(const std::wstring& name) : Actor(name), limitTime(0), currTime(0), isEnd(true) {
}
void QTE::Tick(float deltaTime) {
    DrawQTE();
    currTime += deltaTime;
    if (isEnd) {//판정이 끝난 상황
        if (currTime >= limitTime) {
            //if (fail) {
            //    //실패시 최종 처리 및 객체 소멸
            //    GM::GetLogger().Log(L"실패 후 처리완료..");
            //}
            //else {
            //    //성공시 최종 처리 및 객체 소멸
            //    GM::GetLogger().Log(L"성공 후 처리완료..");
            //}
            //GM::GetLogger().Log(L"Destroy QTE Actor");
            GM::DestroyActor(this);
        }
        //else {
            //판정 완료 후 객체 소멸 전까지 돌아가는 부분
            //if (fail) {
            //    GM::GetLogger().Log(L"실패 후 처리중..");
            //}
            //else {
            //    GM::GetLogger().Log(L"성공 후 처리중..");
            //}
        //}
        return;
    }
    if (currTime >= limitTime) {
        //QTE FAIL
        fail = true;
        isEnd = true;
        currTime = 0;
        limitTime = 1.0f; // QTE 후처리 시간 
        return;
    }
    if (GM::GetInput().IsKeyDown(VK_SPACE)) {//다른 키를 누른다고 실패하지는 않음
        //QTE SUCCESS
        qteTarget->AddBuff(L"QTE FAIL", 1, { {STATS::DEF,50 } });
        isEnd = true;
        currTime = 0;
        limitTime = 1.0f; // QTE 후처리 시간
        return;
    }

    GM::GetDisplay().DrawWidget(100, 20, 10, 10, L"QTE CHECKING", L"QTE 체크중!", FOREGROUND_RED, FOREGROUND_GREEN, FOREGROUND_BLUE);
}

void QTE::DrawQTE() {

    /*
        여기부터 그림
        |
        ㅁㅁㅁㅁㅁㅁㅁ
        ㅁㅁㅁㅁㅁㅁㅁ
        ㅁㅁㅁㅁㅁㅁㅁ
        ㅁㅁㅁㅁㅁㅁㅁ
        ㅁㅁㅁㅁㅁㅁㅁ
        ㅁㅁㅁㅁㅁㅁㅁ
        ㅁㅁㅁㅁㅁㅁㅁ

    */
    float centerX = circleWidth / 2.0f;
    float centerY = circleHeight / 2.0f;
    float angle = -0.1f;
    WORD color = FOREGROUND_RED;
    if (isEnd) {
        if (fail) {
            //
        }
        else {
            color = FOREGROUND_BLUE | FOREGROUND_GREEN;
        }
    }
    else {
        color = FOREGROUND_WHITE;
        float ratio = currTime / limitTime;
        angle = ratio * 2 * M_PI;
    }
    

    for (short y = 0; y < circleHeight; ++y){
        for (short x = 0; x < circleWidth; ++x) {
            float _y = -(y - centerY);
            float _x = x - centerX;
            float _angle = atan2f(_y, _x);
            if (_angle < 0) _angle += 2.0 * M_PI;
            if (_angle > angle) {
                GM::GetDisplay().DrawWcharAtPosition(posX + x, posY + y, L'■', color);
            }
        }
    }
}

void QTE::Init(Character* target, float time) {
    qteTarget = target;
    limitTime = time;
    currTime = 0;
    fail = false;
    isEnd = false;
}
