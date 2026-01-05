#include "QTE.h"
#include "GameManager.h"

QTE::QTE(const std::wstring& name) : Actor(name), limitTime(0), currTime(0), isEnd(true) {
}
void QTE::Tick(float deltaTime) {

    currTime += deltaTime;
    if (isEnd) {//판정이 끝난 상황
        if (currTime >= limitTime) {
            if (fail) {
                //실패시 최종 처리 및 객체 소멸
                GM::GetDisplay().DrawWidget(100, 20, 10, 10, L"QTE FAIL", L"QTE 실패 처리 완료!", FOREGROUND_RED, FOREGROUND_GREEN, FOREGROUND_BLUE);
                GM::GetLogger().Log(L"실패 후 처리완료..");
            }
            else {
                //성공시 최종 처리 및 객체 소멸
                GM::GetDisplay().DrawWidget(100, 20, 10, 10, L"QTE SUCCESS", L"QTE 성공 처리 완료!", FOREGROUND_RED, FOREGROUND_GREEN, FOREGROUND_BLUE);
                GM::GetLogger().Log(L"성공 후 처리완료..");
            }
            GM::GetLogger().Log(L"Destroy QTE Actor");
            GM::DestroyActor(this);
        }
        else {
            //판정 완료 후 객체 소멸 전까지 돌아가는 부분
            if (fail) {
                GM::GetDisplay().DrawWidget(100, 20, 10, 10, L"QTE FAIL", L"QTE 실패 처리 중!", FOREGROUND_RED, FOREGROUND_GREEN, FOREGROUND_BLUE);
                GM::GetLogger().Log(L"실패 후 처리중..");
            }
            else {
                GM::GetDisplay().DrawWidget(100, 20, 10, 10, L"QTE SUCCESS", L"QTE 성공 처리 중!", FOREGROUND_RED, FOREGROUND_GREEN, FOREGROUND_BLUE);
                GM::GetLogger().Log(L"성공 후 처리중..");

            }
        }
        return;
    }
    if (currTime >= limitTime) {
        GM::GetDisplay().DrawWidget(100, 20, 10, 10, L"QTE FAIL", L"QTE 실패!", FOREGROUND_RED, FOREGROUND_GREEN, FOREGROUND_BLUE);
        //QTE FAIL
        fail = true;
        isEnd = true;
        currTime = 0;
        limitTime = 1.0f; // QTE 실패 후 
    }
    if (GM::GetInput().IsKeyDown(VK_SPACE)) {//다른 키를 누른다고 실패하지는 않음
        GM::GetDisplay().DrawWidget(100, 20, 10, 10, L"QTE SUCCESS", L"QTE 성공!", FOREGROUND_RED, FOREGROUND_GREEN, FOREGROUND_BLUE);
        //QTE SUCCESS
        isEnd = true;
        currTime = 0;
        limitTime = 1.0f; // QTE 실패 후 
    }

    GM::GetDisplay().DrawWidget(100, 20, 10, 10, L"QTE CHECKING", L"QTE 체크중!", FOREGROUND_RED, FOREGROUND_GREEN, FOREGROUND_BLUE);
}

void QTE::Init(Character* target, float time) {
    qteTarget = target;
    limitTime = time;
    currTime = 0;
    fail = false;
    isEnd = false;
}
