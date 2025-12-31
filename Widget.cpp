#include "Widget.h"
#include "GameManager.h"
#include<string>
void Widget::Tick(float deltaTime) {
    //GM::GetDisplay()
    static int cnt = 0;

    std::wstring s = L"DeltaTime: " + std::to_wstring(deltaTime);;
    GM::GetDisplay().DrawWidget(posX, posY, width, height, name, s, FOREGROUND_BLUE, FOREGROUND_GREEN, FOREGROUND_RED);
    

}

void Widget::Init(short _posX, short _posY, short _width, short _height) {
    width = _width;
    height = _height;
    posX = _posX;
    posY = _posY;
}

Widget::Widget(std::wstring name) :Actor(name){
}
