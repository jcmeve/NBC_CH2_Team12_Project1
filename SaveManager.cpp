#include "SaveManager.h"
#include<fstream>
#include<sstream>
#include <codecvt>
#include <locale>
SaveManager::SaveManager() {
}

SaveManager::~SaveManager() {
}

bool SaveManager::LoadAscii(const std::wstring& name, std::wstring& buf) {
    std::wifstream file(L"Assets\\Ascii\\" + name + L".txt");
    if (file.is_open()) {
        file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
        std::wstringstream wss;
        wss << file.rdbuf();
        buf.assign(wss.str());
        return true;
    }
    else {
        return false;
    }
    return false;
}

bool SaveManager::SaveGame(Character* player) {
    return false;
}

bool SaveManager::LoadGame(Character* player) {
    return false;
}
