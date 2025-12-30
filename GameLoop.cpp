#include <iostream>
#include <string>
#include<windows.h>
#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include <chrono>

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

    GameManager& gm = GM::GetInstance();
    //gm.CreateActor()
    auto prev = std::chrono::high_resolution_clock::now();
    while (!gm.IsEnd()) {
        auto curr = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = curr - prev;
        prev = curr;
        float deltaTIme = elapsed.count();
        gm.Tick(deltaTIme);

        gm.GetDisplay().Render();
        Sleep(33);
    }
    return 0;
}
