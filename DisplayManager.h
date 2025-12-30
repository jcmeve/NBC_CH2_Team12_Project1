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
    size_t width;
    size_t height;
    size_t borderline;
    static constexpr size_t textAreaHeight = 10;
public:
    void Render();
    DisplayManager(size_t _width, size_t _height);
    void DrawSectors() ;
    void DrawTester();
    void DrawLobby() ;
    void DrawBattle(const Actor& l_actor, const Actor& r_actor);
    void DrawActor(const Actor& actor, size_t x_target, size_t y_target);
    void DrawShop(const Character& player, const Shop& shop) ;
    void DrawShoplist(const Character& player, const Shop& shop);
    void ClearBuffer(unsigned char bufferIdx);
    void WriteString(std::wstring s);
};

