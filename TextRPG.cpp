#include <Windows.h>
#include "TextRPG.h"
#include "GameManager.h"
#include<string>
void TextRPG::Tick(float deltaTime) {
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
    
    GM::GetDisplay().DrawWcharAtPosition(x, y);
    static float timer = 0.0f;
    static int cnt = 0;
    timer += deltaTime;
    if (timer > 3) {
        if (cnt == 0) {
            GM::GetDisplay().WriteStringSlow(L"나는빡빡이다.나는빡빡이다.나는빡빡이다.", 1);
        }
        else if (cnt == 1) {
            GM::GetDisplay().WriteStringSlow(L"ASDADSADADGAGASDWQECXZQRWQAXFSF", 1);
        }
        timer = 0;
        ++cnt;
    }

}

TextRPG::TextRPG():Actor("TextRPG") {

}
