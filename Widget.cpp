#include "Widget.h"
#include "GameManager.h"
#include<string>
void Widget::Tick(float deltaTime) {

    GM::GetDisplay().DrawWidget(posX, posY, width, height, name, text, FOREGROUND_BLUE, FOREGROUND_GREEN, FOREGROUND_RED);
    

}

void Widget::Init(short _posX, short _posY, short _width, short _height) {
    width = _width;
    height = _height;
    posX = _posX;
    posY = _posY;
}

void Widget::SetText(const std::wstring& _text) {
    text = _text;
}

Widget::Widget(std::wstring name) :Actor(name){
}
