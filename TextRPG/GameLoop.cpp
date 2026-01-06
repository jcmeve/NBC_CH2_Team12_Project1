#include<windows.h>
#include <timeapi.h>
#include "GameManager.h"

#include "TextRPG.h"
#include <chrono>
#pragma comment(lib, "winmm.lib")


using namespace std;
int main() {

	timeBeginPeriod(1);

	// Windows 10 호환성을 위한 콘솔 설정
	SetConsoleOutputCP(CP_UTF8);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// 콘솔 모드 설정 - Windows 10에서 한글 출력 개선
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT;
	// DISABLE_NEWLINE_AUTO_RETURN 비활성화로 한글 출력 안정화
	dwMode &= ~DISABLE_NEWLINE_AUTO_RETURN;
	SetConsoleMode(hOut, dwMode);

	// 콘솔 폰트를 명시적으로 설정 (한글 지원 폰트)
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 16;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // 또는 "MS Gothic", "Malgun Gothic"
	SetCurrentConsoleFontEx(hOut, FALSE, &cfi);

	GameManager& gm = GM::GetInstance();
	gm.Init();
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
