#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "GameManager.h"

using namespace std;

int main() {
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);


//    system("cls");
  //  Sleep(100);
    for (int i = 0; i < 5; ++i) {
        GameManager::GetDisplay().DrawSectors();
        Sleep(1000);
    }
    return 0;
}
