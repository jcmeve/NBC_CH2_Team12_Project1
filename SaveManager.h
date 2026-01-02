#pragma once
#include<string>
#include <vector>
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
    bool LoadItems(const std::wstring& name, std::vector<std::vector<std::wstring>>& out);
    bool SaveGame(Character* player);
    bool LoadGame(Character* player);


};

