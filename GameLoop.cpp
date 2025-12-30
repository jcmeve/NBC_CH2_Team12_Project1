#include <iostream>
#include <string>
#include<windows.h>
#include "GameManager.h"
#include "Character.h"
#include "Monster.h"

using namespace std;
int main() {

//    system("cls");
  //  Sleep(100);
    /*
    for (int i = 0; i < 5; ++i) {
        GM::GetDisplay().DrawTester();
        GM::GetDisplay().Render();
        Sleep(1000);
        Actor("kim",4,3);
        Monster("kim", 5);
    }
    */
    std::thread gameThread(GM::Loop);
    
    return 0;
}
