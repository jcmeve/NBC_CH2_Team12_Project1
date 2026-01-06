#pragma once
class VectorWidget;
class Widget;
class Character;
class PrepareBattle {
    enum class MODE {
        EQUIP, UNEQUIP
    };
private:
    MODE mode = MODE::EQUIP;
    Character* player;
    int idx = 0;
    VectorWidget* EquipmentsWidget;
    VectorWidget* InventoryEquipmentsWidget;
    Widget* manualWidget;
public:
    void Enter(Character* _player);
    void Exit();
    void Tick(float deltatTime);

    void TryEquip();
    void IdxUpdate(int _idx);
    void SwitchWidget();
    void ReloadItems();
};

