#pragma once
//ascii manage
#include <string>
class Actor;
class Character;
class Monster;
class Shop;
class DisplayManager {
private:
    static constexpr unsigned char nr_buffer = 2;
    std::wstring drawBuffer[nr_buffer];
    unsigned char currBufferIdx = 0;//그리고 있는 버퍼 idx
    short width;
    short height;
    short borderline;
    static constexpr short textAreaHeight = 10;
public:
    void Render();
    DisplayManager(short _width, short _height);
    void DrawSectors() ;
    void DrawTester();
    void DrawLobby() ;
    void DrawBattle(const Actor& l_actor, const Actor& r_actor);
    void DrawActor(const Actor& actor, short x_target, short y_target);
    void DrawShop(const Character& player, const Shop& shop) ;
    void DrawShoplist(const Character& player, const Shop& shop);
    void ClearBuffer(unsigned char bufferIdx);
    void WriteString(std::wstring s);
};

