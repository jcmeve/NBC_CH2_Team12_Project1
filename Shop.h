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
    VectorWidget* widget;

public:
    void Enter(Character* _player);
    void Exit();
    void Tick(float deltatTime);

    void Trade();
    void IdxUpdate(int _idx);
    void SwitchWidget();
    void ReloadItems();
};

