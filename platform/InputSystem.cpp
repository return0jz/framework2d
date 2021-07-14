#include "InputSystem.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <cstdint>

struct jzj::InputSystem::implementation {
    jzj::GLContextDisplay *display;
    const std::uint8_t *currKeyboardState;
    std::uint8_t *prevKeyboardState;
    std::uint32_t currMouseState;
    std::uint32_t prevMouseState;
    int noKeys;
    int mouseX;
    int mouseY;
    int mouseWheel;
    bool quit;
    SDL_Event e;
};

jzj::InputSystem::InputSystem(jzj::GLContextDisplay *display) : impl(new jzj::InputSystem::implementation) {
    impl->display = display;
    impl->currKeyboardState = SDL_GetKeyboardState(&impl->noKeys);
    impl->prevKeyboardState = new std::uint8_t[impl->noKeys];
    for (int i = 0; i < impl->noKeys;i++) {
        impl->prevKeyboardState[i] = impl->currKeyboardState[i];
    }
    impl->mouseX = 0;
    impl->mouseY=0;
    impl->quit = false;
}

jzj::InputSystem::~InputSystem() {
    delete[] impl->prevKeyboardState;
}

void jzj::InputSystem::update() {
    for (int i = 0; i < impl->noKeys;i++) {
        impl->prevKeyboardState[i] = impl->currKeyboardState[i];
    }
    impl->prevMouseState = impl->currMouseState;
    impl->mouseWheel = 0;
    while (SDL_PollEvent(&impl->e)) {
        switch (impl->e.type) {
            case SDL_QUIT: impl->quit = true;
                break;
            case SDL_MOUSEWHEEL:
                if (impl->e.wheel.direction==SDL_MOUSEWHEEL_NORMAL) {
                    impl->mouseWheel+=impl->e.wheel.y;
                } else {
                    impl->mouseWheel-=impl->e.wheel.y;
                }
                break;
            default:
                break;
        }
    }
    impl->currMouseState = SDL_GetMouseState(&impl->mouseX, &impl->mouseY);
};

bool jzj::InputSystem::getKey(SDL_Scancode scancode) {
    return impl->currKeyboardState[scancode];
}

bool jzj::InputSystem::getKeyDown(SDL_Scancode scancode) {
    return !impl->prevKeyboardState[scancode] && impl->currKeyboardState[scancode];
}

bool jzj::InputSystem::getKeyUp(SDL_Scancode scancode) {
    return impl->prevKeyboardState[scancode] && !impl->currKeyboardState[scancode];
}

bool jzj::InputSystem::getKey(SDL_Keycode keycode) {
    return impl->currKeyboardState[SDL_GetScancodeFromKey(keycode)];
}

bool jzj::InputSystem::getKeyDown(SDL_Keycode keycode) {
    return !impl->prevKeyboardState[SDL_GetScancodeFromKey(keycode)] && impl->currKeyboardState[SDL_GetScancodeFromKey(keycode)];
}
bool jzj::InputSystem::getKeyUp(SDL_Keycode keycode) {
    return impl->prevKeyboardState[SDL_GetScancodeFromKey(keycode)] && !impl->currKeyboardState[SDL_GetScancodeFromKey(keycode)];
}

bool jzj::InputSystem::getMouseButton(int button) {
    return impl->currMouseState & SDL_BUTTON(button);
}

bool jzj::InputSystem::getMouseButtonDown(int button) {
    return !(impl->prevMouseState & SDL_BUTTON(button)) && (impl->currMouseState & SDL_BUTTON(button));
}

bool jzj::InputSystem::getMouseButtonUp(int button) {
    return (impl->prevMouseState & SDL_BUTTON(button)) && !(impl->currMouseState & SDL_BUTTON(button));
}

int jzj::InputSystem::getMouseX() {
    return impl->mouseX;
}

int jzj::InputSystem::getMouseY() {
    return impl->mouseY;
}

int jzj::InputSystem::getMouseWheelDelta() {
    return impl->mouseWheel;
}

bool jzj::InputSystem::getQuit() {
    return impl->quit;
}
