#pragma once
#include "Widget.h"
class LifeTimeWidget : public Widget {
private:
    float lifeTime;
    float lifeTimer;
public:
    void Tick(float deltaTime) override;
    void Init(short posX, short posY, short _width, short _height, float _lifeTime, WORD _titleColor = FOREGROUND_WHITE, WORD _textColor = FOREGROUND_WHITE, WORD _borderColor = FOREGROUND_WHITE);
    LifeTimeWidget(std::wstring name);
};

