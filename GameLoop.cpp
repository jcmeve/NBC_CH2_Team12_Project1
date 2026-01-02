#include<windows.h>
#include <timeapi.h>
#include <iostream>
#include <string>
#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "TextRPG.h"
#include <chrono>
#pragma comment(lib, "winmm.lib")


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
    timeBeginPeriod(1);
    SetConsoleOutputCP(CP_UTF8);
    GameManager& gm = GM::GetInstance();
    gm.CreateActor<TextRPG>();
    auto prev = std::chrono::high_resolution_clock::now();
    int sleepTime; 
    while (!gm.IsEnd()) {
        auto curr = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = curr - prev;
        prev = curr;
        float deltaTime = elapsed.count();
        auto t1 = chrono::high_resolution_clock::now();
        gm.GetInput().Tick(deltaTime);
        auto t2 = chrono::high_resolution_clock::now();
        gm.Tick(deltaTime);
        auto t3 = chrono::high_resolution_clock::now();
        gm.GetDisplay().Render(deltaTime);
        auto t4 = chrono::high_resolution_clock::now();
        auto tickEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> tickTime = tickEnd - curr;

		sleepTime = 16 - (int)(tickTime.count() * 1000.0f);
		if (sleepTime > 0) {
			Sleep(sleepTime);
		}

        float inputT = chrono::duration<float>(t2 - t1).count();
        float logicT = chrono::duration<float>(t3 - t2).count();
        float renderT = chrono::duration<float>(t4 - t3).count();
        /*
        static int frameCount = 0;
        frameCount++;
        if (frameCount % 100 == 0) {
            gm.GetDisplay().WriteString(L"Input:" + std::to_wstring(inputT) + L"| Logic: " + std::to_wstring(logicT) + L" | Render: " + std::to_wstring(renderT) + L"\n");// , inputT, logicT, renderT);
        }
        */
        //gm.GetDisplay().WriteString( L"DeltaTime: " + std::to_wstring(deltaTime) + L" | Sleep: " + std::to_wstring(sleepTime) + L"\n");
    }
    return 0;
}
