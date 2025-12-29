#include "DisplayManager.h"
#include "GameManager.h"
#include<iostream>
#include<Windows.h>
std::string aaaa = R"(                                                                                                                        
                                        ▒                                                                               
                               ▒▒▒░    ░░░                              ░░                              ░  ░   ░        
                             ▓▓▒▒       ░░ ░            ░       ░▒░░░             ░                █░                   
                        ▓▒▒▒▒             ▒ ░   ░░                                ░            ░                        
                     ▒▒▒▒▒               ░░  ▒ ▒                    ░  ░  ░▒       ░         ░                          
                  ▓▓▒▒▒                    ░   ░            ░░░  ░░ ░         ░█          ░░              ░             
              ▓▒▒▒▒▒                      ▒░      ░   ░░░░░░░▒▒░░░░ ░░                ▒       ░░░  ░░░                  
            ▒▒▒█                            ░░░░ ░░░░░░▒▒▒▒░▒▒░░  ░░░▒     ░░            ░░                             
           ▒▒                             ░░░░ ░░░░▒▒░▒▒░░░      ░░░░░              ░░░                                 
          ▓▒                               ░░█    ░     ░░  ░                  ▒                                        
          ▓▒              ░                ░▓       ░              ▒░    ▒                                              
          ▓▒             ░░░░   ░▒ ░        ▓▓▒▓░             ░░▒░        ░                                             
           ░░▒           ░░░░░   ░░                  ░░░░▒▒░     ░░        ░                                            
             ░   ░░░░        ░░  ░             ░░░                ▒         ░                                           
           ░░░░░▒░░░            ░            ░ ░░░░░ ░░            ░         ▒                                          
                  ▒░   ░▓▓▒▒▓▓▒░ ░░         ░ ▒       ░           █▒░         ░                                         
                      ▒▒▓▓░░░   ░             ▒░  ░░  ░         ▒░░░░░     ░░░▒                                         
                      ▒░▒░     ░             ▒░░  ░░░░░      █▒▒░░░░░░░░░░░░░░░                                         
                       ░░░                   ▒░░  ░░  ░  ▒░░▒▒░░░░░░░░░░░   ░░░                                         
                       ░░░      ░░▒▒▒           ░     ░░░░░░░░░░░░░░░░░░░▒                                              
                       ░         ░░░▒▒▓▓▓ ▓▓▒▒░░░░   ░░░░░░░░░░░░░░░░░░                                                 
                       ░░░░░░░░    ░░▒▓▓▒▒▒▒▒▒░░▒▒░░░░░░░▒░░░░░░░░  ░                                                   
                       ▒░░░░░░     ░░░▒▒▒▒▒▒░░░░░░░░░░░░░░▒▓▒▒░░░  ░                                                    
                        ▒░░░      ░░░░░▒▒▒▒▒▒░░░░░░░░░░▒░░░▒▓▒░░░ ░                                                     
                          ░░░░░░░▒░░░░░░▒▓▒░░░░ ░░▒▒▒░░▒▓▒▒░░░░  ░                                                      
                                       ▒▒▓▒▒░░░  ░░░▒▓▒▒▒▒▒░ ░░░ ▒                                                      
                                         ▓▓▒░░░  ░░░░▒▓▒▒░░░  ░░░                                                       
                                           ▒▒░░░  ░░░░░▒▒░    ░░░                                                       
                                            ▒░░░    ░░░░░░░░  ░░░░                                                      
                                            ▒▒░░░    ░░░░░░░  ░░░░░                                                     
                                            ▒░░░   ░░░░░░░░░░  ░░░░░                                                    
                                            ▒░░░░  ░░░░░░░░░    ░░ ░                                                    
                                            ▒░░░░  ░░░░░░░░ ░                                                           
                                             ░░░░░░                 ░                                                   
                                             ░░  ░░                  ░                                                  
                                             ▒░░░░   ░░░░░░░       ░  ░                                                 
                                            ▓▒░░░░░░░░░░░░░░░░   ░░░░  ░                                                
                                            ▒░░░░░░░░░░░░░░░░░░░░░░░░░                                                  
                                           ▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░   ░                                             
                                         ▓▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░   ░                                            
                                        ▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░   ░                                           
                                       ▒▒░░░░░░░░░░░░░░░░░░░  ░░░░░░░░░░░                                               
                                       ▒░░░░░░░░░░░░    ░░░░░░░░░░░░░░░░░                                               
                                     ░▒▒░░░░░░░░░░░░█          ▒▒░░░░░░░░                                               
                                     ▒▒▒░░░░░   ░░░              █▒▒░░░░      ░                                         
                                       ░░░░░   ░                    ▒░         ░                                        
                                       ░░░░  ░░                    ▒░░        ░                                         
                                       ▒░░                         ▒░░        ░                                         
                                     ░░                             █░░       ░                                         
                                   ░░     ░                            ░      ▒                                         
                                  ▒░    ░                              ▒░     ░                                         
                                   █▒░▒█                                ░░   ░                                          
                                                                         ░░  ░                                          
                                                                         ▒░ ░▒░░                                        
                                                                        ░░    ░░ ░█                                     
                                                                          ▒▒░  ░░   ░░                                  
                                                                             ░░░  ░▒░ ░                                 
                                                                                █▒░▒░░░                                 
                                                                                                                        
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


    //fullscreen

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
        drawBuffer[currBufferIdx][(width+1) * (height - textAreaHeight) + x] = L'-';
    }
    Render();
}

void DisplayManager::DrawLobby() {
}

void DisplayManager::DrawBattle(const Character& player, const Monster& monster) {
}

void DisplayManager::DrawShop(const Character& player, const Shop& shop) {
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
        drawBuffer[currBufferIdx][(height-textAreaHeight+2) * (width)+1 + i] = s[i];
    }
    Render();
}

