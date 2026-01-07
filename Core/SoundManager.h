#pragma once
#include <string>
#include <unordered_set>

//멈췄던거 다시 재생 추가도 가능은 함
class SoundManager {
private:
    SoundManager();
    ~SoundManager();
    SoundManager& operator=(const SoundManager& other) = delete;
    SoundManager(const SoundManager& other) = delete;
    SoundManager& operator=(const SoundManager&& other) = delete;
    SoundManager(const SoundManager&& other) = delete;
    friend class GameManager;

    std::unordered_set<std::wstring> audioFiles;
public:
    void Init();
    void LoadAudio(const std::wstring& filePath, const std::wstring& name);
    void PlayAudio(const std::wstring& name, bool loop = false);
    void StopAudio(const std::wstring& name);
    void StopAllAudio();
    void CloseAudio(const std::wstring& name);
    void SetVolume(const std::wstring& name, int volume);


};

