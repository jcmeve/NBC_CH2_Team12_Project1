#pragma once
#include<string>
class Character;
class SaveManager {
private:
    SaveManager();
    ~SaveManager();
    SaveManager& operator=(const SaveManager& other) = delete;
    SaveManager(const SaveManager& other) = delete;
    SaveManager& operator=(const SaveManager&& other) = delete;
    SaveManager(const SaveManager&& other) = delete;
    friend class GameManager;
public:
    bool LoadAscii(const std::wstring& name, std::wstring& buf);
    bool SaveGame(Character* player);
    bool LoadGame(Character* player);

};

