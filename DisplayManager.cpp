#include "DisplayManager.h"
#include "GameManager.h"
#include<iostream>
#include<Windows.h>

std::wstring aaaa = LR"(                                                                                                    
                            +====*+                            :...-                     :...       
                        @**+-:.:::.::           ::....   -..        :               :..  .:..       
                     *****=       :..:   ::....             .        =          -.                  
                  *++*+           =:..:=.    ... ... .........:...   .       -..           -        
              =**++=                ...-...  ....:::::::--.  ....:         -.   . ......:           
          *+++++                  =.. ...:::.-----===---::       .. ....... ..:=:.:-                
         *++*                      :--:-::-=:=+++=--:..----. ..     .....::                         
        +**                        -::::-::-........  .      ....::::=                              
        **           .:..........   -*+    .         ..:-....-                                      
        **+          -:-...::...   ..+*-.    ......:::::......-                                     
        @-:::--     =-::-:.:.   .....   ...:::::--    -........-                                    
         --:::::..   .  .:.::..........:-----          -........-                                   
          --===-:.:-*+-==--.:.........=:.::. :          -........-                                  
                  +=%#-::..: .:.....: +-..::.:       +-:::.....::-                                  
                  =-+:....-          @=:.:-::-     +=--::::::::::-                                  
                   :-:... .  @        =-..:..:=---==--::::::::.::=                                  
                   :::... .:-=+*#*@@**=--:. .::::::---::::::                                        
                   -::::::..::-***++==---=-:---==::---:::::                                         
                   +=--:::.::::=+*+===-:-==--=--+*+=-::.::                                          
                    +-:::..::::-=*+===-:-===-=+=-=*+-:::                                            
                     ---::----::-+*+==-::==+=-+**-::::::                                            
                                 +#*==-:.-==**+=+=:::::                                             
                                   #+=-:.:---++=:..::::                                             
                                    *=--:..:::::::.::--+                                            
                                     +--:...:----::.:-:-:                                           
                                     =::..:------::.:::::                                           
                                     =--:.:----:::........                                          
                                     =-:::::::::..........                                          
                                     =:..::..............:.                                         
                                     *=::::::::::::.....:.:.                                        
                                     +=:::::---:::::::::::..-                                       
                                    +=-::::::::::::::::::::..:                                      
                                  **+--:::::::::::::::::::::..:                                     
                                 *+=-::::::::::::::::::::::::...                                    
                                *=-:::::::::::::::::::::::::::..:                                   
                                +=-:::::::::..::----=-::::::::..:                                   
                               ++=-::::::::          +++-::::::..:                                  
                               *+-::::.::              @+-:::::...-                                 
                                -::::.:                 =-:.......                                  
                                --:...                  =-:......:                                  
                              -:......                   -::.....-                                  
                            =::....:                       -:....=                                  
                            ==-:::.                        -:....=                                  
                                                             -:.:                                   
                                                             -.:=--                                 
                                                            =:...--::::                             
                                                               -::..:-::-                           
                                                                 --::----                           
                                                                                                    
)";


int clamp(int val, int lo, int hi) {
    if (val < lo) return lo;
    if (val > hi) return hi;
    return val;
}

short DisplayManager::CoordToIdx(short x, short y) {
    return y * width + x;
}

//Render Main display exclude textarea
void DisplayManager::Render(float deltaTime) {


    SetConsoleCursorPosition(handle, { 0,0 });
    DrawSectors();
    DWORD Written;
    //when clear display + textarea
    if (clearFullScreen) {
        COORD bufferSize = { (SHORT)width, (SHORT)height };
        COORD bufferCoord = { 0, 0 };
        SMALL_RECT writeRegion = { 0, 0, (SHORT)(width - 1), (SHORT)(height - 1) };
        WriteConsoleOutputW(handle, &drawBuffer[currBufferIdx][0], bufferSize, bufferCoord, &writeRegion);
        clearFullScreen = false;
        cursorX = 0;
        cursorY = borderline+1;
        
    }//just clear display
    else {
        COORD bufferSize = { (SHORT)width, (SHORT)height };
        COORD bufferCoord = { 0, 0 };
        SMALL_RECT writeRegion = { 0, 0, (SHORT)(width - 1), (SHORT)(borderline - 1) };
        WriteConsoleOutputW(handle, &drawBuffer[currBufferIdx][0], bufferSize, bufferCoord, &writeRegion);
    }
    currBufferIdx = (currBufferIdx + 1) % nr_buffer;
    ClearBuffer(currBufferIdx);
    //CHAR_INFO와 나중에 통합해야 할 수도 있음
    if (!stringSlowWrite.empty()) {
        ///for slow writing
        currTimeSlowWrite += deltaTime;
        size_t targetIdx = min(currTimeSlowWrite / totalTimeSlowWrite * stringSlowWrite.size(), stringSlowWrite.size());

        SetConsoleCursorPosition(handle, { cursorX,cursorY });
        for (int i = idxSlowWrite; i < targetIdx; ++i) {
            SetConsoleCursorPosition(handle, { cursorX,cursorY });

            if (stringSlowWrite[i] == L'\n') {
                cursorX = 0;
                SetConsoleCursorPosition(handle, { cursorX,++cursorY });
                continue;
            }
            if (stringSlowWrite[i] > 0x7F) {
                cursorX += 2; //multibyte char use 2
            }
            else {
                cursorX += 1; //
            }
            DWORD Written;
            WriteConsoleW(handle, &stringSlowWrite[i], (DWORD)1, &Written, nullptr);
        }
        idxSlowWrite = targetIdx;
        if (idxSlowWrite == stringSlowWrite.size()) {
            ++cursorY;
            stringSlowWrite = L"";
            idxSlowWrite = 0;
            totalTimeSlowWrite = 0;
            currTimeSlowWrite = 0;
        }
    }
    if (!pendedString.empty()) {
        WriteString(pendedString);
        pendedString.clear();
    }

}

DisplayManager::DisplayManager(short _width, short _height):width(_width),height(_height),currBufferIdx(1) {
    if (width < 50 || width>200 || height < 50 || height>100){
        width = clamp(width, 50, 200);
        height = clamp(height, 50, 100);
    }

    borderline = height - textAreaHeight;

    //fullscreen
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);


    //hide cursor
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(handle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &cursorInfo);


    for (int i = 0; i < nr_buffer; ++i) {
        ClearBuffer(i);
    }
    cursorY = borderline +1;
    cursorX = 0;
        
}

void DisplayManager::DrawSectors() {
  for (int x = 0; x < width; x += 2) {

        
    drawBuffer[currBufferIdx][width * borderline+x].Char.UnicodeChar = L'─';
    drawBuffer[currBufferIdx][width * borderline + x].Attributes = FOREGROUND_WHITE | COMMON_LVB_LEADING_BYTE;
    if (x + 1 < width) {
        drawBuffer[currBufferIdx][width * borderline + x + 1].Char.UnicodeChar = L' ';
        drawBuffer[currBufferIdx][width * borderline + x + 1].Attributes = FOREGROUND_WHITE | COMMON_LVB_TRAILING_BYTE;
    }
    }
}

void DisplayManager::DrawTester() {

    DrawSectors();
    short x_target = 50;
    short y_target = 5;
    if (x_target > width || y_target > borderline)
        WriteString(L"Draw Actor Fail!");
    short curr_pos = 0;
    short current_y_offset = 0;
    while (curr_pos < aaaa.size()) {
        //calculate current line length
        short next_newline = aaaa.find(L'\n', curr_pos);

        short line_end = (next_newline == std::wstring::npos) ? aaaa.size() : next_newline;
        short line_length = line_end - curr_pos;

        //if edge of the display stop draw
        if (y_target + current_y_offset >= height) break;
        if (x_target + line_length > width) {
            line_length = width - x_target;
        }

        for (int i = 0; i < line_length; ++i) {
            int bufferIdx = (y_target + current_y_offset) * width + (x_target + i);
            drawBuffer[currBufferIdx][bufferIdx].Char.UnicodeChar = aaaa[curr_pos + i];
            drawBuffer[currBufferIdx][bufferIdx].Attributes = FOREGROUND_WHITE;
        }

        if (next_newline == std::wstring::npos) break;
        curr_pos = next_newline + 1;
        current_y_offset++;
    }

    WriteString(L"ABCDEFGHIGKLMNOPQRSTUVWXTZ");
    

}

void DisplayManager::DrawWcharAtPosition(short x, short y, wchar_t c, WORD color) {
    if (drawBuffer[currBufferIdx].empty()) {
        exit(-1);
    }
    if (x < 0 || x >= width || y < 0 || y >= height) return;
    short idx = CoordToIdx(x, y);
    if (drawBuffer[currBufferIdx][idx].Attributes & COMMON_LVB_TRAILING_BYTE) {//앞이 전각인 경우 뒤에 새로 그리려면 앞 문자까지 지워야함
        if (x > 0) {
            drawBuffer[currBufferIdx][idx-1].Char.UnicodeChar = L' ';
            drawBuffer[currBufferIdx][idx-1].Attributes = color;
        }
    }
    if (!(c >= 0x2500 && c <= 0x257F) && c > 0x7F) { // 전각검사
        if (x + 1 < width) {//2칸씀
            drawBuffer[currBufferIdx][idx].Char.UnicodeChar = c;
            drawBuffer[currBufferIdx][idx].Attributes = color | COMMON_LVB_LEADING_BYTE;

            drawBuffer[currBufferIdx][idx + 1].Char.UnicodeChar = L' ';
            drawBuffer[currBufferIdx][idx + 1].Attributes = color | COMMON_LVB_TRAILING_BYTE;
        }
    }
    else {
        drawBuffer[currBufferIdx][idx].Char.UnicodeChar = c;
        drawBuffer[currBufferIdx][idx].Attributes = color;
    }
}

void DisplayManager::DrawLobby() {
    DrawSectors();
}

void DisplayManager::DrawBattle(const Actor& player, const Actor& monster) {

}
//void DisplayManager::DrawActor(const Actor& actor, short x_target, short y_target) {
//    if (x_target > width || y_target > borderline)
//        WriteString(L"Draw Actor Fail!");
//    short curr_pos = 0;
//    short current_y_offset = 0;
//    while (curr_pos < aaaa.size()) {
//        //calculate current line length
//        short next_newline = aaaa.find(L'\n', curr_pos);
//
//        short line_end = (next_newline == std::wstring::npos) ? aaaa.size() : next_newline;
//        short line_length = line_end - curr_pos;
//
//        //if edge of the display stop draw
//        if (y_target + current_y_offset >= height) break;
//        if (x_target + line_length > width) {
//            line_length =  width - x_target;
//        }
//
//        for (int i = 0; i < line_length; ++i) {
//            int bufferIdx = (y_target + current_y_offset) * width + (x_target + i);
//            drawBuffer[currBufferIdx][bufferIdx].Char.UnicodeChar = aaaa[curr_pos + i];
//            drawBuffer[currBufferIdx][bufferIdx].Attributes = 0x0007; 
//        }
//
//        if (next_newline == std::wstring::npos) break;
//        curr_pos = next_newline + 1; 
//        current_y_offset++;
//    }
//}

void DisplayManager::DrawAscii(const std::wstring ascii, short x_target, short y_target) {
    if (x_target > width || y_target > borderline)
        WriteString(L"Draw Actor Fail!");
    short curr_pos = 0;
    short current_y_offset = 0;
    while (curr_pos < ascii.size()) {
        //calculate current line length
        short next_newline = ascii.find(L'\n', curr_pos);

        short line_end = (next_newline == std::wstring::npos) ? ascii.size() : next_newline;
        short line_length = line_end - curr_pos;

        //if edge of the display stop draw
        if (y_target + current_y_offset >= height) break;
        if (x_target + line_length > width) {
            line_length = width - x_target;
        }

        for (int i = 0; i < line_length; ++i) {
            int bufferIdx = (y_target + current_y_offset) * width + (x_target + i);
            drawBuffer[currBufferIdx][bufferIdx].Char.UnicodeChar = ascii[curr_pos + i];
            drawBuffer[currBufferIdx][bufferIdx].Attributes = 0x0007;
        }

        if (next_newline == std::wstring::npos) break;
        curr_pos = next_newline + 1;
        current_y_offset++;
    }
}


void DisplayManager::DrawShop(const Character& player, const Shop& shop) {
}

void DisplayManager::DrawShoplist(const Character& player, const Shop& shop) {
}

void DisplayManager::ClearTextArea() {
    clearFullScreen = true;

}

void DisplayManager::ClearBuffer(unsigned char bufferIdx) {
    drawBuffer[bufferIdx].assign(width * height, { L' ' , });
}



//천천히 출력중에 WriteString 무시함
void DisplayManager::WriteString(const std::wstring& s) {
    if (drawBuffer[currBufferIdx].empty()) {
        exit(-1);
    }
    if (!stringSlowWrite.empty())
        return;
    
    cursorX = 0;
    if (cursorY >= height) {
        ClearTextArea();
        pendedString = s;
        return;
    }

    SetConsoleCursorPosition(handle, { 0,cursorY });
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == L'\n') {
            SetConsoleCursorPosition(handle, { 0,++cursorY });
            continue;
        }
        DWORD Written;
        WriteConsoleW(handle, &s[i], (DWORD)1, &Written, nullptr);
    }
    ++cursorY;
}

//천천히 출력중에 WriteString 무시함
void DisplayManager::WriteStringSlow(const std::wstring& s, float time) {   
    if (!stringSlowWrite.empty())
        return;

    cursorX = 0;
    if (cursorY >= height) {
        ClearTextArea();
    }

    totalTimeSlowWrite = time;
    stringSlowWrite = s;
    currTimeSlowWrite = 0.0f;
    idxSlowWrite = 0;
    SetConsoleCursorPosition(handle, { 0,cursorY });

}

void DisplayManager::DrawBox(short posX, short posY, short _width, short _height, WORD color) {

     if (posX > width || posY > borderline) {
        WriteString(L"Draw Box Fail!");
        return;
    }

    for (short y = 0; y < _height; ++y) {
        if (posY + y >= borderline) break;
        DrawWcharAtPosition(posX, posY + y, L'│', color);
        DrawWcharAtPosition(posX + _width, posY + y, L'│', color);
    }

    for (short i = 1; i < _width; ++i) {
        short targetX = posX + i;
        DrawWcharAtPosition(targetX, posY, L'─', color);
        DrawWcharAtPosition(targetX, posY + _height, L'─', color);
    }
    DrawWcharAtPosition(posX, posY, L'┌', color);
    DrawWcharAtPosition(posX + _width, posY, L'┐', color);
    DrawWcharAtPosition(posX, posY + _height, L'└', color);
    DrawWcharAtPosition(posX + _width, posY + _height, L'┘', color);
}

void DisplayManager::DrawWidget(short posX, short posY, short _width, short _height, const std::wstring& title, const std::wstring& text, WORD  titleColor, WORD textColor, WORD borderColor ) {
    DrawBox(posX, posY, _width, _height, borderColor);


    if (posX > width || posY > borderline) {
        WriteString(L"Draw Widget Fail!");
        return;
    }
    //on the top line of widget
    if (!title.empty()) {
        short titleX = posX + 2;
        for (wchar_t c : title) {
            DrawWcharAtPosition(titleX, posY, c, titleColor | FOREGROUND_INTENSITY);
            titleX += (c > 0x7F) ? 2 : 1; //끔찍한 전각처리
        }
    }

    short x_offset = 1; 
    short y_offset = 1;

    for (int i = 0; i < text.size(); ++i) {

        if (y_offset >= _height) break;

        if (text[i] == L'\n') {
            ++y_offset;
            x_offset = 1;
            continue;
        }
        if (text[i] > 0x7F && x_offset == _width-1) { //오른쪽 테두리 직전에 전각문자를 넣으면 덮어버리므로 예외처리
            x_offset = 1;
            ++y_offset;
            continue;
        }

        if (x_offset >= _width) {
            x_offset = 1;
            ++y_offset;
        }

        DrawWcharAtPosition(posX + x_offset, posY + y_offset, text[i], textColor);

        // 다음 칸 위치 계산
        short charWidth = (text[i] > 0x7F) ? 2 : 1;
        x_offset += charWidth;

        // 박스 너비를 넘어가면 자동 줄바꿈 (테두리 1칸 전까지)
        if (x_offset >= _width) {
            x_offset = 1;
            ++y_offset;
        }
    }

}


