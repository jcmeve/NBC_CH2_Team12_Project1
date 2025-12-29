#pragma once
//ascii manage
#include <string>

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
    static constexpr size_t textAreaHeight = 10;
    void Render();
public:
    DisplayManager(size_t _width, size_t _height);
    void DrawSectors() ;
    void DrawLobby() ;
    void DrawBattle(const Character& player, const Monster& monster);
    void DrawShop(const Character& player, const Shop& shop) ;
    void ClearBuffer(unsigned char bufferIdx);
    void WriteString(std::wstring s);
};

