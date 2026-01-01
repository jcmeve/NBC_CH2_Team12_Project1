#include <Windows.h>
#include "TextRPG.h"
#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include<string>
#include "Widget.h"
void TextRPG::Tick(float deltaTime) {
    TickTest(deltaTime);

    /*
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
    
    */
}

void TextRPG::TickTest(float deltaTime) {
    static short x = 30;
    static short y = 30;

    if (GM::GetInput().IsKeyDown(VK_LEFT)) {
    //if (GetAsyncKeyState(VK_LEFT)) {
            --x;
    }
    if (GM::GetInput().IsPressed(VK_RIGHT)) {
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
    GM::GetDisplay().DrawWcharAtPosition(x, y, L'a',BACKGROUND_RED);
    GM::GetDisplay().DrawTester();
    static float timer = 0.0f;
    timer += deltaTime;
    if (timer > 0.6) {
        GM::GetDisplay().WriteStringSlow(L"나는빡빡이다.나는빡빡이다.나는빡빡이다.", 0.5);
        timer = 0;
    }
}


TextRPG::TextRPG(std::wstring name):Actor(name) {
    Widget* widget = GM::CreateActor<Widget>(L"한글쓰지말자");
    widget->Init(0, 0, 40, 10);
    
}
