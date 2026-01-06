#pragma once
#include <windows.h>
#include "Actor.h"
#include<string>

typedef unsigned short WORD;
#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

class Widget : public Actor {
    // Actor을(를) 통해 상속됨
private:
    std::wstring text;
    short posX;
    short posY;
    short width;
    short height;
    WORD titleColor;
    WORD textColor;
    WORD borderColor;
public:
    void Tick(float deltaTime) override;
    void Init(short posX, short posY, short _width, short _height, WORD _titleColor = FOREGROUND_WHITE, WORD _textColor = FOREGROUND_WHITE, WORD _borderColor = FOREGROUND_WHITE);
    void SetText(const std::wstring& _text);
    Widget(std::wstring name);
};
