#include "InputManager.h"
#include "GameManager.h"
InputManager::InputManager() :pressedBuffer{ false, }, prevBuffer{false,} ,readIdx(0),writeIdx(1){
    inputThread = std::thread([&]() {
        while (!GM::IsEnd()) {
            bool cache[255] = { false, };

            for (unsigned char i = 0; i < 255; ++i) {
                if (GetAsyncKeyState(i)&0x8000) {
                    cache[i] = true;
                }
            }

            {
                std::lock_guard<std::mutex> lock(bufferMutex);
                for (unsigned char i = 0; i < 255; ++i) {

                    pressedBuffer[writeIdx][i] |= cache[i];
                }
            }
            Sleep(1);

        }
    });
}

InputManager::~InputManager() {
    inputThread.join();
}

bool InputManager::IsPressed(unsigned char key) {
    return pressedBuffer[readIdx][key];
}

bool InputManager::IsKeyDown(unsigned char key) {
    return !prevBuffer[key] && pressedBuffer[readIdx][key];
}

void InputManager::Tick(float deltaTime) {
    std::lock_guard<std::mutex> lock(bufferMutex);
    std::copy(pressedBuffer[readIdx], pressedBuffer[readIdx] + 255, prevBuffer);
    memset(pressedBuffer[readIdx], 0, sizeof(bool) * 255);
    std::swap(readIdx, writeIdx);


}