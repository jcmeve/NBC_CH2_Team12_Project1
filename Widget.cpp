#include "Widget.h"
#include "GameManager.h"
#include<string>
#include "LifeTimeWidget.h"


void Widget::Tick(float deltaTime) {

    GM::GetDisplay().DrawWidget(posX, posY, width, height, name, text, titleColor, textColor, borderColor);
    

}

void Widget::Init(short _posX, short _posY, short _width, short _height, WORD _titleColor, WORD _textColor, WORD _borderColor) {
    width = _width;
    height = _height;
    posX = _posX;
    posY = _posY;

    titleColor = _titleColor;
    textColor = _textColor;
    borderColor = _borderColor;

}


void Widget::SetText(const std::wstring& _text) {
    text = _text;
}


Widget::Widget(std::wstring name) :Actor(name){
}
