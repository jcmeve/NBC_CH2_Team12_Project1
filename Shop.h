#pragma once
class VectorWidget;
class Character;
class Shop {
    enum class MODE{
        BUY,SELL
    };
private:
    MODE mode = MODE::BUY;
    Character* player;
    int idx = 0;
public:
    void Enter(Character* _player);

    void Tick(float deltatTime);
    void IdxUpdate(int _idx);
    void SwitchWidget();
    void Exit();
    VectorWidget* widget;
};

