#pragma once
#include <string>
class Actor;
class Item {
public:
    Item();
    virtual ~Item();
    virtual void Use(Actor& actor)=0;
    std::wstring GetName();
protected:
    std::wstring name;
};

class HealingPotion : public Item {
public:
    HealingPotion(int _amount = 50);
    void Use(Actor& actor) override;

private:
    int amount;
};

class DamageIncreasePotion : public Item {
public:
    DamageIncreasePotion(int _amount = 10);
    void Use(Actor& actor) override;
private:
    int amount;
};

