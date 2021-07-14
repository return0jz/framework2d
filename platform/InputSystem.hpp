#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include "GLContextDisplay.hpp"

namespace jzj {

class InputSystem {
public:
    InputSystem(jzj::GLContextDisplay *display);
    ~InputSystem();
    void update();
    
    bool getMouseButton(int button);
    bool getMouseButtonDown(int button);
    bool getMouseButtonUp(int button);
    int getMouseX();
    int getMouseY();
    int getMouseWheelDelta();

    bool getKey(SDL_Scancode scancode);
    bool getKeyDown(SDL_Scancode scancode);
    bool getKeyUp(SDL_Scancode scancode);

    bool getKey(SDL_Keycode scancode);
    bool getKeyDown(SDL_Keycode scancode);
    bool getKeyUp(SDL_Keycode scancode);
    
    bool getQuit();
private:
    struct implementation;
    std::unique_ptr<implementation> impl;
};

}
