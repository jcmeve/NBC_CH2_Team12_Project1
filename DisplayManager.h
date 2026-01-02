#pragma once
#include <windows.h>
#include <string>
#include <vector>
class Actor;
class Character;
class Monster;
class Shop;
//TODO 그림 우선순위 체크 할 필요가 생길 수도 있음

#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

class DisplayManager {
private:
    static constexpr unsigned char nr_buffer = 2;
    
    std::vector<CHAR_INFO> NNNNdrawBuffer[nr_buffer];
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
    short CoordToIdx(short x, short y);

public:
    void Render(float deltaTime);
    DisplayManager(short _width, short _height);
    void DrawSectors() ;
    void DrawTester();
    void DrawWcharAtPosition(short x, short y, wchar_t c, WORD color);
    void DrawLobby() ;
    void DrawBattle(const Actor& l_actor, const Actor& r_actor);
    void DrawActor(const Actor& actor, short x_target, short y_target);
    void DrawShop(const Character& player, const Shop& shop) ;
    void DrawShoplist(const Character& player, const Shop& shop);
    void ClearTextArea();
    void ClearBuffer(unsigned char bufferIdx);
    void WriteString(const std::wstring& s);
    void WriteStringSlow(const std::wstring& s, float time);

    //위젯으로 옮기는게 깔끔함 but 아직 사용처가 하나이므로 냅둠
    void DrawBox(short posX, short posY, short width, short height,WORD color);
    void DrawWidget(short posX, short posY, short width, short height, const std::wstring& title, const std::wstring& text, WORD  titleColor = FOREGROUND_WHITE, WORD textColor = FOREGROUND_WHITE, WORD borderColoe = FOREGROUND_WHITE);
};

