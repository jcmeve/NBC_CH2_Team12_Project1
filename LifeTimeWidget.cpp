#include "LifeTimeWidget.h"
#include "GameManager.h"
LifeTimeWidget::LifeTimeWidget(std::wstring name) :Widget(name) {
}

void LifeTimeWidget::Tick(float deltaTime) {
    Widget::Tick(deltaTime);
    lifeTimer += deltaTime;
    if (lifeTimer >= lifeTime) {
        GM::DestroyActor(this);
        return;
    }

}

void LifeTimeWidget::Init(short posX, short posY, short _width, short _height, float _lifeTime, WORD _titleColor, WORD _textColor, WORD _borderColor) {
    Widget::Init(posX, posY, _width, _height, _titleColor, _textColor, _borderColor);
    lifeTime = _lifeTime;
    lifeTimer = 0.0f;
}


