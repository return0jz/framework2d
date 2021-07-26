#pragma once

#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "Base.hpp"

namespace jzj {
class GLPlatformLayer : public Base { // represents multimedia layer with OpenGL Context
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
    
    void swap();

    void setWidth(int width);
    void setHeight(int height);
    void setWidthAndHeight(int width, int height);
    void setVisible(bool makeVisible);
    void setFullscreen();
    void setWindowedFullscreen();
    void setWindowed();
private:
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
    
    class Audio {
    public:
        Audio(jzj::GLPlatformLayer *display);
        ~Audio();
        void playMusic(std::string path, int loops=0); // Only one music at a time | repeats infinitely when loops=-1
        void playSound(std::string path, int loops=0, int channel=-1); // Multiple sounds at a time | repeats infinitely when loops=-1
        void stopMusic();
        void stopChannel(int channel);
        bool isPlayingChannel(int channel);
        bool isPlayingMusic();
        int setMusicVolume(int volume); // 0 - 128 | returns previous volume
        int setSoundVolume(std::string path, int volume); // 0 - 128 (if < 0 nothing happens) | returns previous volume or -1 if chunk doesn't exist
    private:
        struct implementation;
        jzj::GLPlatformLayer::Audio::implementation *impl;
    };
private:
    struct implementation;
    jzj::GLPlatformLayer::implementation *impl;
public:
    jzj::GLPlatformLayer::InputSystem *input;
    jzj::GLPlatformLayer::Audio *audio;
};
}
