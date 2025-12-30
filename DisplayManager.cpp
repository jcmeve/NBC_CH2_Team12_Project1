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

void DisplayManager::Render() {

    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(ConsoleHandle, { 0,0 });
  
    DWORD Written;
    WriteConsoleW(ConsoleHandle, drawBuffer[currBufferIdx].c_str(), (DWORD)drawBuffer[currBufferIdx].size(), &Written, nullptr);
    
    currBufferIdx = (currBufferIdx + 1) % nr_buffer;
    ClearBuffer(currBufferIdx);

}

DisplayManager::DisplayManager(size_t _width, size_t _height):width(_width),height(_height),currBufferIdx(1) {
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
    size_t x_target = 50;
    size_t y_target = 5;
    if (x_target > width || y_target > borderline)
        WriteString(L"Draw Actor Fail!");
    size_t curr_pos = 0;
    size_t current_y_offset = 0;
    while (curr_pos < aaaa.size()) {
        //calculate current line length
        size_t next_newline = aaaa.find(L'\n', curr_pos);

        size_t line_end = (next_newline == std::wstring::npos) ? aaaa.size() : next_newline;
        size_t line_length = line_end - curr_pos;

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

    WriteString(L"TETETSTSTSTSETESTET\nRERSERRER");
    

}

void DisplayManager::DrawLobby() {
    DrawSectors();

}

void DisplayManager::DrawBattle(const Actor& player, const Actor& monster) {


    Render();

}
void DisplayManager::DrawActor(const Actor& actor, size_t x_target, size_t y_target) {
    if (x_target > width || y_target > borderline)
        WriteString(L"Draw Actor Fail!");
    size_t curr_pos = 0;
    size_t current_y_offset = 0;
    while (curr_pos < aaaa.size()) {
        //calculate current line length
        size_t next_newline = aaaa.find(L'\n', curr_pos);

        size_t line_end = (next_newline == std::wstring::npos) ? aaaa.size() : next_newline;
        size_t line_length = line_end - curr_pos;

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
    for (int i = 0; i < s.size(); ++i) {
        drawBuffer[currBufferIdx][(borderline + 2) * (width)+1 + i] = s[i];
    }
    Render();
}

