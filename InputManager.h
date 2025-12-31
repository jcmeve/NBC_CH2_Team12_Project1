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
    bool prevBuffer[255];//누른 후 Tick 에서만 유효한 KeyDown을 감지하기 위해 존재함
    std::mutex bufferMutex;
    unsigned char writeIdx = 0;
    unsigned char readIdx = 1;

    std::thread inputThread;
public:
    bool IsPressed(unsigned char key);
    bool IsKeyDown(unsigned char key);
    void Tick(float deltaTime);
};

