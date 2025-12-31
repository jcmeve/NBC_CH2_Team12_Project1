
#include <Windows.h>
#include <mmsystem.h>
#include "SoundManager.h"

#pragma comment(lib,"winmm.lib")
    SoundManager::SoundManager() {
        mciSendStringW(L"open \"Assets\\Audio\\test.wav\" type mpegvideo alias MediaFile ", nullptr, 0, nullptr);
        mciSendStringW(L"play MediaFile", nullptr, 0, nullptr);


    }

    SoundManager::~SoundManager() {
        mciSendStringW(L"stop MediaFile", nullptr, 0, nullptr);
        mciSendStringW(L"close MediaFile", nullptr, 0, nullptr);
    }
