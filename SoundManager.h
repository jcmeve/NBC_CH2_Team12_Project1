#pragma once
class SoundManager {
private:
    SoundManager();
    ~SoundManager();
    SoundManager& operator=(const SoundManager& other) = delete;
    SoundManager(const SoundManager& other) = delete;
    SoundManager& operator=(const SoundManager&& other) = delete;
    SoundManager(const SoundManager&& other) = delete;
    friend class GameManager;

};

