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
void DisplayManager::Render() {

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(handle, { 0,0 });
  
    DWORD Written;
//  WriteConsoleW(handle, drawBuffer[currBufferIdx].c_str(), (DWORD)drawBuffer[currBufferIdx].size(), &Written, nullptr);
    WriteConsoleW(handle, drawBuffer[currBufferIdx].c_str(), (DWORD)(width+1)*(borderline+1), &Written, nullptr);

    currBufferIdx = (currBufferIdx + 1) % nr_buffer;
    ClearBuffer(currBufferIdx);

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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    for (int i = 0; i < nr_buffer; ++i) {
        ClearBuffer(i);
    }
        
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

void DisplayManager::DrawLobby() {
    DrawSectors();

}

void DisplayManager::DrawBattle(const Actor& player, const Actor& monster) {


    Render();

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

void DisplayManager::ClearBuffer(unsigned char bufferIdx) {

    drawBuffer[bufferIdx].assign((width + 1) * height, L' ');
    for (int y = 0; y < height; ++y) {
        drawBuffer[bufferIdx][y * (width + 1) + width] = L'\n';
    }
    
}

void DisplayManager::WriteString(std::wstring s) {
    if (drawBuffer[currBufferIdx].empty()) {
        exit(-1);
    }
    /*
    for (int i = 0; i < s.size(); ++i) {
        drawBuffer[currBufferIdx][(borderline + 2) * (width+1) + i] = s[i];
    }
    */
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    //PCONSOLE_SCREEN_BUFFER_INFO ret;
    //GetConsoleScreenBufferInfo(handle, ret);
    //COORD cursorPosition = ret->dwCursorPosition;

    short cursorY = borderline + 2;
    SetConsoleCursorPosition(handle, { 0,cursorY });
    for (int i = 0; i < s.size(); ++i) {
        
        if (s[i] == L'\n') {
            SetConsoleCursorPosition(handle, { 0,++cursorY });
            continue;
        }
        //putwchar(s[i]);

        DWORD Written;
        //WriteConsoleW(handle, drawBuffer[currBufferIdx].c_str(), (DWORD)drawBuffer[currBufferIdx].size(), &Written, nullptr);
        //WriteConsoleW(handle, s.c_str(), (DWORD)s.size(), &Written, nullptr);
        WriteConsoleW(handle, &s[i], (DWORD)1, &Written, nullptr);

    }


}

