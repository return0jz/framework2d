#pragma once

#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "../Base.hpp"

namespace jzj {
class GLPlatformLayer : public Base { // Class that represents multimedia layer with an OpenGL Context
public:
    GLPlatformLayer(std::string title, int width, int height, int glMajorVersion, int glMinorVersion) noexcept(false);
    ~GLPlatformLayer();
    
    void* getWindow(); // Underlying SDL_Window pointer
    void* getContext(); // Underlying SDL_Context
    
    int getWidth();
    int getHeight();
    bool isFullscreen();
    bool isWindowedFullscreen();
    bool isWindowed();
    
    // Todo: Add window setters (setVisible, resize, etc.)
    void swap();

    void setWidth(int width);
    void setHeight(int height);
    void setWidthAndHeight(int width, int height);
    void setVisible(bool makeVisible);
    void setFullscreen();
    void setWindowedFullscreen();
    void setWindowed();
    
    class InputSystem : public Base {
    public:
        InputSystem(jzj::GLPlatformLayer *display);
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
private:
    struct implementation;
    std::unique_ptr<implementation> impl;
};
}
