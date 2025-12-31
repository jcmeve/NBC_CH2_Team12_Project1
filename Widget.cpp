#include "Widget.h"
#include "GameManager.h"
void Widget::Tick(float deltaTime) {
    //GM::GetDisplay()

    GM::GetDisplay().DrawWidget(posX, posY, width, height,name, L"ASDFASF테스트위젯ㄴㅇㅁㄹ131231315435윷ㅌ퓸처asdasdfasfadsasdfasfd@$%^#$&ㅇㅁㄹ12312312313",FOREGROUND_BLUE,FOREGROUND_GREEN,FOREGROUND_RED);
}

void Widget::Init(short _posX, short _posY, short _width, short _height) {
    width = _width;
    height = _height;
    posX = _posX;
    posY = _posY;
}

Widget::Widget(std::wstring name) :Actor(name){
}
