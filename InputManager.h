#pragma once
#include <mutex>
class InputManager {
private:
    InputManager();
    ~InputManager();
    InputManager& operator=(const InputManager& other) = delete;
    InputManager(const InputManager& other) = delete;
    InputManager& operator=(const InputManager&& other) = delete;
    InputManager(const InputManager&& other) = delete;
    friend class GameManager;
    bool pressedBuffer[2][255];
    std::mutex bufferMutex;
    unsigned char writingIdx = 0;
    std::thread inputThread;
public:
    bool IsPressed(unsigned char key);
};

