#pragma once
//ascii manage
#include <string>

class Actor;
class Character;
class Monster;
class Shop;
//TODO 그림 우선순위 체크 할 필요가 생길 수도 있음
class DisplayManager {
private:
    static constexpr unsigned char nr_buffer = 2;
    std::wstring drawBuffer[nr_buffer];
    unsigned char currBufferIdx = 0;//그리고 있는 버퍼 idx
    short width;
    short height;
    short borderline;
    static constexpr short textAreaHeight = 10;

    float totalTimeSlowWrite = 0.0f;
    float currTimeSlowWrite = 0.0f;
    std::wstring stringSlowWrite;
    size_t idxSlowWrite = 0;
    void* handle = nullptr;

    std::wstring pendedString;

    //for TextArea
    short cursorY ;
    short cursorX;

    bool clearFullScreen = false;


public:
    void Render(float deltaTime);
    DisplayManager(short _width, short _height);
    void DrawSectors() ;
    void DrawTester();
    void DrawWcharAtPosition(short x,short y);
    void DrawLobby() ;
    void DrawBattle(const Actor& l_actor, const Actor& r_actor);
    void DrawActor(const Actor& actor, short x_target, short y_target);
    void DrawShop(const Character& player, const Shop& shop) ;
    void DrawShoplist(const Character& player, const Shop& shop);
    void ClearTextArea();
    void ClearBuffer(unsigned char bufferIdx);
    void WriteString(std::wstring s);
    void WriteStringSlow(std::wstring s, float time);
};

