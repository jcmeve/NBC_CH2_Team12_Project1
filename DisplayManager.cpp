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

//Render Main display exclude textarea
void DisplayManager::Render(float deltaTime) {


    SetConsoleCursorPosition(handle, { 0,0 });
    DrawSectors();
    DWORD Written;
    //when clear display + textarea
    if (clearFullScreen) {
        WriteConsoleW(handle, drawBuffer[currBufferIdx].c_str(), (DWORD)(width + 1) * (height), &Written, nullptr);
        clearFullScreen = false;
        cursorX = 0;
        cursorY = borderline+1;
        
    }//just clear display
    else {
        WriteConsoleW(handle, drawBuffer[currBufferIdx].c_str(), (DWORD)(width + 1) * (borderline + 1), &Written, nullptr);
    }
    currBufferIdx = (currBufferIdx + 1) % nr_buffer;
    ClearBuffer(currBufferIdx);

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
    for (int x = 0; x < width; ++x) {
        drawBuffer[currBufferIdx][(width+1) * (borderline) + x] = L'-';
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

        if (line_length > 0) {
            std::copy(aaaa.begin() + curr_pos,
                aaaa.begin() + curr_pos + line_length,
                drawBuffer[currBufferIdx].begin() + (y_target + current_y_offset) * (width + 1) + x_target);
        }

        if (next_newline == std::wstring::npos) break;
        curr_pos = next_newline + 1;
        current_y_offset++;
    }

    WriteString(L"ABCDEFGHIGKLMNOPQRSTUVWXTZ\n123456789");
    

}

void DisplayManager::DrawWcharAtPosition(short x, short y) {
    if (drawBuffer[currBufferIdx].empty()) {
        exit(-1);
    }

    //Write Ac Display
    SetConsoleCursorPosition(handle, { x,y });
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            drawBuffer[currBufferIdx][(y+i) * (width + 1) + (x+j)] = L'ㅁ';
        }
    }
    


}

void DisplayManager::DrawLobby() {
    DrawSectors();
}

void DisplayManager::DrawBattle(const Actor& player, const Actor& monster) {

}
void DisplayManager::DrawActor(const Actor& actor, short x_target, short y_target) {
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
            line_length =  width - x_target;
        }

        if (line_length > 0) {
            std::copy(aaaa.begin() + curr_pos,
                aaaa.begin() + curr_pos + line_length,
                drawBuffer[currBufferIdx].begin() + (y_target + current_y_offset) * (width + 1) + x_target);
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

    drawBuffer[bufferIdx].assign((width + 1) * height, L' ');
    for (int y = 0; y < height; ++y) {
        drawBuffer[bufferIdx][y * (width + 1) + width] = L'\n';
    }
    
}



//천천히 출력중에 WriteString 무시함
void DisplayManager::WriteString(std::wstring s) {
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
void DisplayManager::WriteStringSlow(std::wstring s, float time) {   
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

