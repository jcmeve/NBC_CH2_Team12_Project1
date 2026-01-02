#pragma once
#include <string>
#include <vector>
class Actor;
class Item {
public:
    Item();
    virtual ~Item();
    virtual void Use(Actor& actor)=0;
    std::wstring GetName();
protected:
    std::wstring name;
    int gold;
    std::wstring description;
    int turn;//buff 필요
    std::vector<std::pair<std::wstring, int>> effects;//target stat, ammound 
    //이름, 골드, 설명, 턴, HP 숫자, ATK 숫자, DEF 숫자

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

