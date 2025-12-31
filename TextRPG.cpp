#include <Windows.h>
#include "TextRPG.h"
#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include<string>
void TextRPG::Tick(float deltaTime) {
    
    Character* player = GM::CreateActor<Character>(L"플레이어");
    Pawn* monster = GM::CreateActor<Monster>(L"트롤");

    static float attackSpeed = 1;
    static float timer = 0;
    timer += deltaTime;
    static int turn = 0;

    if (timer > attackSpeed) {
        timer = 0;
        if (turn == 0) {
            player->Attack(*monster);
        }
        else {
            monster->Attack(*player);
        }

        turn = (turn + 1) % 2;
    }
    
//    TickTest(deltaTime);
}

void TextRPG::TickTest(float deltaTime) {
    static short x = 30;
    static short y = 30;

    if (GetAsyncKeyState(VK_LEFT)) {
        --x;
    }
    if (GetAsyncKeyState(VK_RIGHT)) {
        ++x;
    }
    if (GetAsyncKeyState(VK_UP)) {
        --y;
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        ++y;
    }
    if (GetAsyncKeyState(VK_ESCAPE)) {
        GM::ShutDown();
    }
    x = x < 0 ? 0 : x;
    y = y < 0 ? 0 : y;
    x = x > 120 ? 120 : x;
    y = y > 55 ? 55 : y;
    GM::GetDisplay().DrawSectors();
    GM::GetDisplay().DrawWcharAtPosition(x, y);
    static float timer = 0.0f;
    timer += deltaTime;
    if (timer > 0.6) {
        GM::GetDisplay().WriteStringSlow(L"나는빡빡이다.나는빡빡이다.나는빡빡이다.", 0.5);
        timer = 0;
    }
}


TextRPG::TextRPG(std::wstring name):Actor(name) {

}
