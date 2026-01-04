#pragma once
#include "Actor.h"
#include<string>
class Widget : public Actor {
    // Actor을(를) 통해 상속됨
private:
    std::wstring text;
    short posX;
    short posY;
    short width;
    short height;
public:
    void Tick(float deltaTime) override;
    void Init(short posX, short posY, short _width, short _height);
    void SetText(const std::wstring& _text);
    Widget(std::wstring name);
};
