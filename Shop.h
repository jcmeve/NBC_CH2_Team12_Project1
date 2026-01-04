#pragma once
class Widget;
class Character;
class Shop {
    enum class MODE{
        BUY,SELL
    };
private:
    MODE mode = MODE::BUY;
    Character* player;
public:
    void Enter(Character* _player);

    void Tick(float deltatTime);
    
    void SwitchWidget();
    void Exit();
    Widget* widget;
};

