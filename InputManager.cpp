#include "InputManager.h"
#include "GameManager.h"
InputManager::InputManager() :pressedBuffer{false,} {
    inputThread = std::thread([&]() {
        while (!GM::IsEnd()) {
            

        }

        });
}

InputManager::~InputManager() {
    inputThread.join();
}

bool InputManager::IsPressed(unsigned char key) {
    return false;
}
